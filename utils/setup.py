#!/usr/bin/env python3

import argparse
import platform
import subprocess
import distro

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
        if distro.id() == "ubuntu":
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
