cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(
        python
        URL https://www.python.org/ftp/python/3.9.6/Python-3.9.6.tgz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(python)