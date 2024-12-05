//
// Description: This demonstrates how to trigger a camera with a MicaSense RedEdge-MX
//

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/mission/mission.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include "micasense.hpp"
#include "cloud.hpp"

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

Mission::MissionItem make_mission_item(
    double latitude_deg,
    double longitude_deg,
    float relative_altitude_m,
    float speed_m_s,
    bool is_fly_through,
    float gimbal_pitch_deg,
    float gimbal_yaw_deg,
    float loiter_time_s,
    Mission::MissionItem::CameraAction camera_action,
    float yaw_deg)
{
    Mission::MissionItem new_item{};
    new_item.latitude_deg = latitude_deg;
    new_item.longitude_deg = longitude_deg;
    new_item.relative_altitude_m = relative_altitude_m;
    new_item.speed_m_s = speed_m_s;
    new_item.is_fly_through = is_fly_through;
    new_item.gimbal_pitch_deg = gimbal_pitch_deg;
    new_item.gimbal_yaw_deg = gimbal_yaw_deg;
    new_item.loiter_time_s = loiter_time_s;
    new_item.camera_action = camera_action;
    new_item.yaw_deg = yaw_deg;
    return new_item;
}

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url>\n"
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
    std::cout << "Enter the number of waypoints for image capture: ";
    std::cin >> num_waypoints;

    // Store the waypoint numbers
    std::vector<int> capture_waypoints(num_waypoints);
    for (int i = 0; i < num_waypoints; ++i) {
        std::cout << "Enter the waypoint number for data capture " << (i + 1) << ": ";
        std::cin >> capture_waypoints[i];
    }

    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};
    ConnectionResult connection_result = mavsdk.add_any_connection(argv[1]);

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
    auto mission = Mission{system.value()};
    auto telemetry = Telemetry{system.value()};
    
    // while (!telemetry.health_all_ok()) {
    //     std::cout << "Waiting for system to be ready\n";
    //     std::cout << telemetry.health() << std::endl;
    //     sleep_for(seconds(1));
    // }

    std::cout << "System ready\n";

    std::cout << "Downloading mission from flight controller." << '\n';
    std::pair<Mission::Result, Mission::MissionPlan> result = mission.download_mission();

    std::cout << "Mission downloaded (MissionItems: "
        << result.second.mission_items.size()
        << ")" << '\n';
    
    std::vector<Mission::MissionItem> mission_items;

    static int mission_counter = 1;
    for (const auto& item : result.second.mission_items) {
        float loiter_time = (mission_counter == 3 || mission_counter == 4 || mission_counter == 5) ? 10.0f : item.loiter_time_s;
        std::cout << "Loiter time: " << loiter_time << "\n";
        std::cout << "Mission: " << mission_counter << "\n";
        mission_items.push_back(make_mission_item(
            item.latitude_deg,
            item.longitude_deg,
            item.relative_altitude_m,
            item.speed_m_s,
            false,
            item.gimbal_pitch_deg,
            item.gimbal_yaw_deg,
            loiter_time,
            Mission::MissionItem::CameraAction::None,
            item.yaw_deg));
        mission_counter++;
    }

    // Print downloaded mission items
    for (const auto& item : mission_items) {
        std::cout << "Mission Item: \n"
                  << "  Latitude: " << item.latitude_deg << "\n"
                  << "  Longitude: " << item.longitude_deg << "\n"
                  << "  Relative Altitude: " << item.relative_altitude_m << "\n"
                  << "  Speed: " << item.speed_m_s << "\n"
                  << "  Fly Through: " << item.is_fly_through << "\n"
                  << "  Gimbal Pitch: " << item.gimbal_pitch_deg << "\n"
                  << "  Gimbal Yaw: " << item.gimbal_yaw_deg << "\n"
                  << "  Loiter Time: " << item.loiter_time_s << "\n"
                  << "  Camera Action: " << static_cast<int>(item.camera_action) << "\n"
                  << "  Yaw: " << item.yaw_deg << "\n";
    }

    if (result.first != Mission::Result::Success) {
        std::cout << "Mission download failed (" << result.first << "), exiting." << '\n';
        return 1;
    }
    
    std::cout << "Uploading mission...\n";
    Mission::MissionPlan mission_plan{};
    mission_plan.mission_items = mission_items;
    const Mission::Result upload_result = mission.upload_mission(mission_plan);

    if (upload_result != Mission::Result::Success) {
        std::cerr << "Mission upload failed: " << upload_result << ", exiting.\n";
        return 1;
    }

    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();
    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }
    std::cout << "Armed.\n";

    // Set maximum speed.
    std::cout << "Set maximum speed to 2 m/s...\n";
    const Action::Result max_speed_result = action.set_maximum_speed(2.0f);
    if (max_speed_result != Action::Result::Success) {
        std::cout << "Failed to change maximum speed: " << max_speed_result << '\n';
        return 1;
    }
    
    // Create a vector of atomic booleans
    std::vector<std::atomic<bool>> capture_images(num_waypoints);
    for (auto& capture_image : capture_images) {
        capture_image = false;
    }

    // Before starting the mission, we want to be sure to subscribe to the mission progress.
    mission.subscribe_mission_progress([&capture_images, capture_waypoints](Mission::MissionProgress mission_progress) {
        std::cout << "Mission status update: " << mission_progress.current << " / "
                  << mission_progress.total << '\n';

        for (size_t i = 0; i < capture_waypoints.size(); ++i) {
            if (mission_progress.current == capture_waypoints[i]) {
                capture_images[i] = true;
            }
        }
    });

    Mission::Result start_mission_result = mission.start_mission();
    if (start_mission_result != Mission::Result::Success) {
        std::cerr << "Starting mission failed: " << start_mission_result << '\n';
        return 1;
    }

    Micasense micasense;
    Cloud cloud;

    for (size_t i = 0; i < capture_images.size(); ++i) {
        while (!capture_images[i]) {
            sleep_for(seconds(1));
        }
        mission.pause_mission();
        micasense.captureImages();
        cloud.uploadImagesToDropbox();
        cloud.moveImagesToArchive();
        mission.start_mission();
    }

    while (!mission.is_mission_finished().second) {
        sleep_for(seconds(1));
    }

    // Set return to launch altitude.
    std::cout << "Set return to launch altitude...\n";
    const Action::Result rtl_alt_result = action.set_return_to_launch_altitude(20.0f);
    if (rtl_alt_result != Action::Result::Success) {
        std::cout << "Failed to change return to launch altitude: " << rtl_alt_result<< '\n';
        return 1;
    }

    // We are done, and can do RTL to go home.
    std::cout << "Commanding RTL...\n";
    const Action::Result rtl_result = action.return_to_launch();
    if (rtl_result != Action::Result::Success) {
        std::cout << "Failed to command RTL: " << rtl_result << '\n';
        return 1;
    }

    // We need to wait a bit, otherwise the armed state might not be correct yet.
    sleep_for(seconds(2));

    while (telemetry.armed()) {
        // Wait until we're done.
        sleep_for(seconds(1));
    }
    std::cout << "Disarmed, exiting.\n";
}
