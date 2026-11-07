# Asset Lister

A C++ command-line tool that scans a folder of production assets and reports the contents: including what's there, invalid and duplicated.

## Problem

In production pipelines, redundant assets often accumulate quickly. This can be from copying and forgetting the original, adding incompatible assets or failing to remove large ones. Although this can be tracked by hand, this doesn't scale. This inflates the backup sizes, slows down system indexing and adds unnecessary I/O overhead.

This tool scans a directory and produces reports regarding file count, validated files and duplicates. The duplicates are found based on content rather than name so even if it won't raise flags to a check based on names (bicycle.png to bicycle - Copy.png) the hashes will be identical.

## How it works 

| Command | Function |
|---------|----------|
|`scan <path>`| Lists assets in directory and reports file count sorted by extension. |
|`validate <path>`| Checks filenames,size and format; reports every file that fails. |
|`find_duplicates <path>`| Does a two pass of files with matching size and hashes them. Reports duplicate groups. |
|`full_analysis <path>`| Runs all three in sequences. |

```bash
./build/Release/AssetLister.exe find_duplicates C:/asset_test_data/medium
```
All commands print the elapsed time for the operation.

## Validation

An Asset is assigned a "WARNING" status if:

- the filename contains non-alphanumeric letters or underscores
- format other than `.txt`,`.fbx`,`.png`,`.jpeg`
- larger than 16MB

## Duplicate Detection

Initially every file in a directory was hashed and compared to see if the contents matched. This was slow and didn't scale well. The solution was a two pass system where assets were grouped depending on file_size and then hashed if they were matching sizes.

Files with unique sizes are never hashed. On a test directory this sped up duplicate detection 8x faster: from **1.18 s to 0.15 s** since only 18% needed to be hashed.

This scales with the amount of duplicates a folder contains, the more duplicates the more hashing will be done. But the inverse is also true: where a folder with little duplicates skips most of the hashing.

For the hashing initially I used the legacy interface (SHA224_Init/Update/Final,from `<openssl/sha.h>`) and encountered issues due to deprecation issues. I then switched to EVP OpenSSL High-Level API in which I could interact with SHA224 through a single interface. Files are read into a 8kb buffer to optimise memory.

## First build and run 

C++23, CMake 3.21+ and [vcpkg](https://github.com/microsoft/vcpkg) for OpenSSL dependency.

```bash
# 1. Clone and bootstrap vcpkg (once per machine, outside this project)
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh        # bootstrap-vcpkg.bat on Windows
 
# 2. Configure, pointing CMake at the vcpkg toolchain
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
 
# 3. Build
cmake --build build --config Release
```
`vcpkg.json` installs OpenSSL automatically during step 2. The first build is the longest because OpenSSL is compiled from the source, all subsequent builds are read from the cached result.

Executable is written to `build/Release/AssetLister.exe`

## Example Run

(Release build, warm cache)
```bash
./build/Release/AssetLister.exe find_duplicates C:/asset_test_data/medium

"C:\\asset_test_data\\medium"

Duplicates group (2 files):
 C:/asset_test_data/medium\asset_17.txt
 C:/asset_test_data/medium\asset_17 - Copy.txt
 ...
 Duplicates group (2 files):
 C:/asset_test_data/medium\asset_98 - Copy.txt
 C:/asset_test_data/medium\asset_98.txt
All hash_files: 202
time elapsed: 0.152947
```
## Test data

`tools/GenerateAssets.cpp` builds a `GenerateTests` executable that writes
directories of random files using a fixed seed for testing. The benchmark above used the
`medium` set (1,000 files, 64 KB–512 KB) with 100 files duplicated under
new names.

## Tradeoffs and Limitations

- **Cryptographic Hash vs Non-Cryptographic Hash** A non-cryptographic hash like xxHash is benchmarked about 10x faster and in a production version would be a better choice for pure deduplication if attacks aren't a consideration. I used SHA-224 both to familiarise myself with integrating standard crypto libraries and it would be the first thing i changed.

- **Unused GCC/Clang branch** Only the MSVC branch has been exercised.

- **Single Directory Scanning** Only performs operations on one directory and subfolders are skipped. 

- **Validation lists 1 warning** The validator only gives one of the reasons a file may fail.

## Project Structure


```
include/     Headers for the scanner, validator and duplicate detector
src/         Implementations, plus main.cpp (argument parsing and dispatch)
tools/       Test-asset generator
```