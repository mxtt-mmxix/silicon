#!/usr/bin/env sh

curl -fsSL http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo curl -fsSLo /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
sudo apt-get update -y && sudo apt-get install \
libglm-dev libxcb-dri3-0 libxcb-present0 libpciaccess0 \
libpng-dev libxcb-keysyms1-dev libxcb-dri3-dev libx11-dev \
libmirclient-dev libwayland-dev libxrandr-dev libxcb-randr0-dev \
libxcb-ewmh-dev libx11-xcb-dev liblz4-dev vulkan-sdk