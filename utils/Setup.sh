#!/usr/bin/env sh

git submodule update --init --recursive

./libs/vcpkg/bootstrap-vcpkg.sh

./libs/vcpkg/vcpkg install "sdl2[vulkan]"
./libs/vcpkg/vcpkg install "fmt"
./libs/vcpkg/vcpkg install "boost-pool"