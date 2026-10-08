/* #include <openssl/sha.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

int main() {
    std::string sha_test = "Testing this string";
    
    // SHA224 produces a 224-bit hash, which is always 28 bytes
    unsigned char hash[SHA224_DIGEST_LENGTH];
    
    // Call the OpenSSL function correctly using C-style casts
    SHA224(reinterpret_cast<const unsigned char*>(sha_test.data()), sha_test.size(), hash);
    
    // (Optional) Print it out to verify the plumbing works
    std::cout << "Hash success! First byte: " << (int)hash[0] << "\n";
    return 0;
} */

#include "AssetScanner.h"
#include "Validator.h"
#include "DuplicateDetector.h"
#include <iostream>

int main(){
 
    //AssetScanner();
    //Validator();
    DuplicateDetector();

    
}


//save outputs using Asset struct

//seperate AssetScanner out of Main

//if it's an odd number of characters make sure it's even 
//