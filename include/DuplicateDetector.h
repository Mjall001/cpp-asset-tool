// duplicate_detector.h
#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>
#include "AssetScanner.h"
#include <openssl/sha.h>
#include <iomanip>
#include <unordered_map>

namespace fs = std::filesystem;

// std::vector<std::vector<Asset>> findDuplicates(const std::vector<Asset>& assets);
std::string hashFile(fs::path file);
std::unordered_map<std::string, std::vector<std::string>> DuplicateDetector(fs::path filePath);

// signature function