cmake_minimum_required(VERSION 3.15)

 include(FetchContent)

 FetchContent_Declare(
         dr_wav
         URL https://github.com/HarryTheoBartAlexClemDev/RType/releases/download/v0.0.0/dr_wav.tar.xz
         DOWNLOAD_EXTRACT_TIMESTAMP TRUE
 )

 FetchContent_MakeAvailable(dr_wav)
