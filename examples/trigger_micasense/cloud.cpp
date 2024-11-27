#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "cloud.hpp"

void Cloud::uploadImagesToDropbox() {
        int result = system("~/Dropbox-Uploader/dropbox_uploader.sh -s upload ~/Dropbox/custom_drone_test /");
        
        if (result != 0) {
            // Handle error
            std::cerr << "Error running dropbox_uploader command. Return code: " << result << std::endl;
        }
        else {
            std::cout << "Images synced to dropbox" << std::endl;
        }
    }


