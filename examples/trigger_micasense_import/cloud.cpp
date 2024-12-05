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
        int result = system("~/Dropbox-Uploader/dropbox_uploader.sh -s upload ~/Dropbox/custom_drone_test/tiff /custom_drone_test/tiff");
        
        if (result != 0) {
            // Handle error
            std::cerr << "Error running dropbox_uploader command. Return code: " << result << std::endl;
        }
        else {
            std::cout << "Images synced to dropbox" << std::endl;
        }
    }

void Cloud::moveImagesToArchive() {
        int result_tiff = system("mv ~/Dropbox/custom_drone_test/tiff/* ~/Dropbox/custom_drone_test/archive/tiff/");
        int result_jpeg = system("mv ~/Dropbox/custom_drone_test/jpeg/* ~/Dropbox/custom_drone_test/archive/jpeg/");

        if (result_tiff != 0) {
            // Handle error
            std::cerr << "Error running mv command. Return code: " << result_tiff << std::endl;
        }
        else {
            std::cout << "TIFF images copied to archive" << std::endl;
        }

        if (result_jpeg != 0) {
            // Handle error
            std::cerr << "Error running mv command. Return code: " << result_jpeg << std::endl;
        }
        else {
            std::cout << "JPEG images copied to archive" << std::endl;
        }
    }


