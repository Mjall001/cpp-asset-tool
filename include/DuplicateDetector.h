// duplicate_detector.h
#pragma once
#include <string>
#include <filesystem>
#include <cstdint>
#include <vector>
#include "AssetScanner.h"
#include <openssl/sha.h>
#include <iomanip>

std::vector<std::vector<Asset>> findDuplicates(const std::vector<Asset>& assets);

int DuplicateDetector();

//signature function