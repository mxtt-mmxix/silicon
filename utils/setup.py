#!/usr/bin/env python3

import argparse
import os

import distro
import io
import platform
import requests
import subprocess

dependencies = [
    "sdl2[vulkan]",
    "fmt",
    "boost-pool",
    "boost-graph"
]


def setup():

    parser = argparse.ArgumentParser(
        description='Bootstrap the environment for building Silicon Engine')

    parser.add_argument(
        '--install-vulkan',
        action="store_true",
        help="Installs Vulkan, may require sudo and assumes cURL is installed",
        dest="install_vulkan")

    args = parser.parse_args()

    if args.install_vulkan:
        if platform.system() == "Windows":
            r = requests.get("https://sdk.lunarg.com/sdk/download/latest/windows/vulkan-sdk.exe")
            exe = open("vulkan-sdk.exe", mode="wb")
            exe.write(r.content)
            exe.close()

            subprocess.run(
                f"vulkan-sdk.exe \
--accept-licenses \
--default-answer \
--confirm-command install \
--root {os.path.abspath('/VulkanSDK/')} \
com.lunarg.vulkan.32bit \
com.lunarg.vulkan.thirdparty \
com.lunarg.vulkan.debug \
com.lunarg.vulkan.debug32",
                shell=True,
                check=True)

        else:
            if distro.id() == "ubuntu":
                r = requests.get("https://packages.lunarg.com/lunarg-signing-key-pub.asc")
                subprocess.run("sudo apt-key add -", input=io.BytesIO(r.content).getvalue(), shell=True, check=True)

                subprocess.run("./utils/Linux/Ubuntu/InstallVulkan.sh", check=True)
            else:
                subprocess.run("./utils/Linux/InstallVulkan.sh", check=True)

    vcpkg_bootstrap = "./libs/vcpkg/bootstrap-vcpkg.sh"
    vcpkg = "./libs/vcpkg/vcpkg"

    if platform.system() == "Windows":
        vcpkg_bootstrap = ".\\libs\\vcpkg\\bootstrap-vcpkg.bat"
        vcpkg = ".\\libs\\vcpkg\\vcpkg"

    subprocess.run([vcpkg_bootstrap], check=True)

    for dependency in dependencies:
        subprocess.run(f"{vcpkg} install {dependency}", shell=True, check=True)

    if platform.system() == "Windows":
        for dependency in dependencies:
            subprocess.run(
                f"{vcpkg} install {dependency} --triplet=x64-windows",
                shell=True,
                check=True)


if __name__ == "__main__":
    setup()
