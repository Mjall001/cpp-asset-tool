#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(){
    std::cout << "Program started...\n";

    fs::path filePath = "tests/TestAssets";
    fs::directory_iterator dirIter(filePath);
    
    std::cout << "Current working directory: " << fs::current_path() << std::endl;

    if (!fs::exists(filePath) || !fs::is_directory(filePath)){
        std:: cout << filePath <<"File Path is not a valid directory\n"<< std::endl;
    }
    std:: cout <<"File Path does Exist\n"<< filePath << std::endl;

    for(const auto& item: dirIter){
        std::cout << item.path().filename() <<"File size: " << item.file_size() <<std::endl;
    }
    //std::cout << "Hello World" << std::endl;
    return 0;
}