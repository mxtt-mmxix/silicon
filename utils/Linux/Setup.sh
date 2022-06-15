#!/usr/bin/env sh

git submodule update --init --recursive

./libs/vcpkg/bootstrap-vcpkg.sh

./libs/vcpkg/vcpkg install