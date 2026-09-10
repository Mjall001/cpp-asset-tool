#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

namespace fs = std::filesystem;

struct defective_assets{
    std::string format;
    std::string file_name;
    std::string status;
    std::uintmax_t size_bytes;
    std::string reason;
    
    //bool is_meta = false; //for unity assets
};
int Validator();