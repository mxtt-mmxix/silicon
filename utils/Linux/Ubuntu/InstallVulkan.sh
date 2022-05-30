#!/usr/bin/env sh

curl -fsSL http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo curl -fsSLo /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
sudo apt-get update -y && sudo apt-get install vulkan-sdk