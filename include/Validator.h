#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>

namespace fs = std::filesystem;

struct defective_assets
{
    std::string format;
    std::string file_name;
    std::uintmax_t size_bytes{0};
    std::string status{"UNVALIDATED"};
    std::string reason{"Valid file"};

    // bool is_meta = false; //for unity assets
};
int Validator(fs::path filePath);