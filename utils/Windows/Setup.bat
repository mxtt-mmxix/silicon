git submodule update --init --recursive

.\libs\vcpkg\bootstrap-vcpkg.bat

.\libs\vcpkg\vcpkg install
.\libs\vcpkg\vcpkg install --triplet=x64-windows