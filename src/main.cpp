#include "AssetScanner.h"
#include "Validator.h"
#include "DuplicateDetector.h"
#include <iostream>
#include <filesystem>
#include <chrono>
void helpMenu()
{
    std::cout << "To scan files: scan asset\\path" << std::endl;
    std::cout << "To validate files: validate asset\\path" << std::endl;
    std::cout << "To check for duplicates: find_duplicates asset\\path" << std::endl;
    std::cout << "For a full analysis report: full_analysis asset\\path" << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {

        std::cout << "Invalid Argument Count" << std::endl;
        helpMenu();
        return 1;
    }
    auto command = std::string(argv[1]);
    auto filePath = std::string(argv[2]);
    if (!fs::exists(filePath))
    {
        std::cout << "Invalid file path" << std::endl;
        return 1;
    };

    if (command == "validate")
    {
        auto start = std::chrono::steady_clock::now();
        AssetScanner(filePath);
        auto end = std::chrono::steady_clock::now();
        Validator(filePath); // works
        std::chrono::duration<double> time_elapsed = end - start;
        std::cout << "time elapsed: " << time_elapsed.count() << std::endl;
        return 0;
    }
    else if (command == "scan")
    {
        auto start = std::chrono::steady_clock::now();
        AssetScanner(filePath);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_elapsed = end - start;
        std::cout << "time elapsed: " << time_elapsed.count() << std::endl;
    }
    else if (command == "find_duplicates")
    {
        auto start = std::chrono::steady_clock::now();
        DuplicateDetector(filePath);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_elapsed = end - start;
        std::cout << "time elapsed: " << time_elapsed.count() << std::endl;
    }
    else if (command == "full_analysis")
    {
        auto start = std::chrono::steady_clock::now();
        AssetScanner(filePath);
        Validator(filePath);
        DuplicateDetector(filePath);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_elapsed = end - start;
        std::cout << "time elapsed: " << time_elapsed.count() << std::endl;
    }
    else
    {
        helpMenu();
        return 1;
    }

    for (int i = 0; i < argc; i++)
    {
        std::cout << "argc[" << i << "] = ";
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
