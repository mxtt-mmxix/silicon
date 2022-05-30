#!/usr/bin/env sh

sudo curl -fsSLo /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
sudo apt-get update -y && sudo apt-get install libsdl2-dev vulkan-sdk