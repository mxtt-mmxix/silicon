git submodule update --init --recursive

.\libs\vcpkg\bootstrap-vcpkg.bat

.\libs\vcpkg\vcpkg install "sdl2[vulkan]"
.\libs\vcpkg\vcpkg install "fmt"
.\libs\vcpkg\vcpkg install "boost-pool"
.\libs\vcpkg\vcpkg install "boost-graph"

.\libs\vcpkg\vcpkg install "sdl2[vulkan]:x64-windows"
.\libs\vcpkg\vcpkg install "fmt:x64-windows"
.\libs\vcpkg\vcpkg install "boost-pool:x64-windows"
.\libs\vcpkg\vcpkg install "boost-graph:x64-windows"