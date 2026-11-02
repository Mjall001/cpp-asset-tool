#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <ostream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

bool createFile(const fs::path &path, std::uintmax_t size, std::mt19937 &seed)
{
    constexpr std::size_t bufferSize = 8192;
    std::array<char, bufferSize> buffer;
    std::uniform_int_distribution<> byteDist(0, 255);
    // buffer.fill('a');
    std::ofstream file(path, std::ios::binary); // creates the file (empty)
    if (!file)                                  // did it actually open?
    {
        std::cerr << "Could not create " << path << "\n";
        return false;
    }
    std::uintmax_t remaining = size;
    while (remaining > 0)
    {
        for (char &byte : buffer)
        {
            byte = static_cast<char>(byteDist(seed));
        }

        const auto bytesToWrite = std::min<std::uintmax_t>(
            buffer.size(), remaining);

        file.write(buffer.data(),
                   static_cast<std::streamsize>(bytesToWrite));

        if (!file)
        {
            std::cerr << "Failed to write " << path << '\n';
            return false;
        }

        remaining -= bytesToWrite;
    }
    file.close();
    if (file.fail())
    {
        std::cerr << "Failed to finish writing " << path << '\n';
        return false;
    }
    return true;
}
int GenerateAssets(int assetCount, int minSize, int maxSize, fs::path root)
{

    std::error_code ec;
    // save random seed start here
    std::seed_seq seed{12, 345, 6789};
    std::mt19937 mt{seed}; // created a fixed seed

    // fs::path root = "C:/asset_test_data/small"; // outside project
    fs::create_directories(root, ec);

    std::uniform_int_distribution<std::uintmax_t> sizeDist(minSize, maxSize);
    std::uintmax_t total_bytes = 0;
    // const int assetCount = 10;
    for (int i = 1; i <= assetCount; ++i)
    {

        std::uintmax_t size = sizeDist(mt);
        std::string filename = "asset_" + std::to_string(i) + ".txt";
        createFile(root / filename, size, mt);
        total_bytes += size;
    }
    std::cout << total_bytes << std::endl;
    return 0;
}

int main()
{
    GenerateAssets(5000, 1024, 64 * 1024, "C:/asset_test_data/small");
    // bytes:167224830
    GenerateAssets(1000, 64 * 1024, 512 * 1024, "C:/asset_test_data/medium");
    // bytes:292663206
    GenerateAssets(100, 5 * 1024 * 1024, 20 * 1024 * 1024, "C:/asset_test_data/large");
    // bytes:1282350368

    return 0;
}