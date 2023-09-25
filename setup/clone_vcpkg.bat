set VCPKG_DIR="vcpkg"

if not exist %VCPKG_DIR% (
    git clone https://github.com/microsoft/vcpkg.git %VCPKG_DIR%
    cd %VCPKG_DIR%
    bootstrap-vcpkg.bat
    cd ..
)
