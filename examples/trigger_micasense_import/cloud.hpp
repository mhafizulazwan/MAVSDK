#ifndef CLOUD_HPP
#define CLOUD_HPP

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

class Cloud {
public:
    void uploadImagesToDropbox();
    void moveImagesToArchive();

};

#endif // MICASENSE_HPP
