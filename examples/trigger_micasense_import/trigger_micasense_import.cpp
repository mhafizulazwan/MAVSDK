//
// Description: This demonstrates how to trigger a camera with a MicaSense RedEdge-MX
//              and import a mission from a QGroundControl plan.
//

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/mission_raw/mission_raw.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include "micasense.hpp"
#include "cloud.hpp"

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url> <mission_plan_path>\n"
              << "Connection URL format should be :\n"
              << " For TCP : tcp://[server_host][:server_port]\n"
              << " For UDP : udp://[bind_host][:bind_port]\n"
              << " For Serial : serial:///path/to/serial/dev[:baudrate]\n"
              << "For example, to connect to the simulator use URL: udp://:14540\n";
}

int main(int argc, char** argv)
{
    // Prompt the user for the number of waypoints
    int num_waypoints;
    std::cout << "Enter the total number of waypoints for data capture: ";
    std::cin >> num_waypoints;

    // Store the waypoint numbers
    std::vector<int> capture_waypoints(num_waypoints);
    for (int i = 0; i < num_waypoints; ++i) {
        std::cout << "Enter the waypoint number for data capture " << (i + 1) << ": ";
        std::cin >> capture_waypoints[i];
    }

    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};

    const ConnectionResult connection_result = mavsdk.add_any_connection(argv[1]);
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }

    auto system = mavsdk.first_autopilot(3.0);
    if (!system) {
        std::cerr << "Timed out waiting for system\n";
        return 1;
    }

    auto action = Action{system.value()};
    auto mission_raw = MissionRaw{system.value()};
    auto telemetry = Telemetry{system.value()};

    // while (!telemetry.health_all_ok()) {
    //     std::cout << "Waiting for system to be ready\n";
    //     sleep_for(seconds(1));
    // }

    std::cout << "System ready\n";

    std::cout << "Importing mission from mission plan: " << argv[2] << '\n';
    std::pair<MissionRaw::Result, MissionRaw::MissionImportData> import_res =
        mission_raw.import_qgroundcontrol_mission(argv[2]);
    if (import_res.first != MissionRaw::Result::Success) {
        std::cerr << "Failed to import mission items: " << import_res.first;
        return 1;
    }

    if (import_res.second.mission_items.size() == 0) {
        std::cerr << "No missions! Exiting...\n";
        return 1;
    }
    std::cout << "Found " << import_res.second.mission_items.size()
              << " mission items in the given QGC plan.\n";

    std::cout << "Uploading mission...";
    const MissionRaw::Result upload_result =
        mission_raw.upload_mission(import_res.second.mission_items);
    if (upload_result != MissionRaw::Result::Success) {
        std::cerr << "Failed uploading mission: " << upload_result << '\n';
        return 1;
    }
    std::cout << "Mission uploaded.\n";

    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();
    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }
    std::cout << "Armed.\n";

    auto prom = std::promise<void>{};
    auto fut = prom.get_future();

    // Create a vector of atomic booleans
    std::vector<std::atomic<bool>> capture_images(num_waypoints);
    for (auto& capture_image : capture_images) {
        capture_image = false;
    }

    // Before starting the mission subscribe to the mission progress.
    mission_raw.subscribe_mission_progress([&prom, &capture_images, capture_waypoints](MissionRaw::MissionProgress mission_progress) {
        std::cout << "Mission progress update: " << mission_progress.current << " / "
                  << mission_progress.total << '\n';

        for (size_t i = 0; i < capture_waypoints.size(); ++i) {
            if (mission_progress.current == capture_waypoints[i]) {
                capture_images[i] = true;
            }
        }

        if (mission_progress.current == mission_progress.total) {
            prom.set_value();
        }
    });

    const MissionRaw::Result start_mission_result = mission_raw.start_mission();
    if (start_mission_result != MissionRaw::Result::Success) {
        std::cerr << "Starting mission failed: " << start_mission_result << '\n';
        return 1;
    }

    Micasense micasense;
    Cloud cloud;

    for (size_t i = 0; i < capture_images.size(); ++i) {
        while (!capture_images[i]) {
            sleep_for(seconds(1));
        }
        mission_raw.pause_mission();
        micasense.captureImages();
        cloud.uploadImagesToDropbox();
        cloud.moveImagesToArchive();
        mission_raw.start_mission();
    }

    if (fut.wait_for(std::chrono::seconds(240)) != std::future_status::ready) {
        std::cerr << "Mission not finished yet, giving up.\n";
        return 1;
    }

    // Mission complete. Command RTL to go home.
    std::cout << "Commanding RTL...\n";
    const Action::Result result = action.return_to_launch();
    if (result != Action::Result::Success) {
        std::cerr << "Failed to command RTL: " << result << '\n';
        return 1;
    }
    std::cout << "Commanded RTL.\n";

    return 0;
}
