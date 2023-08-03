#!/bin/bash

source /opt/ros/humble/setup.bash

build_location="/root/iugv"

cd "$build_location" && \
colcon build --symlink-install --packages-select iugv_interfaces

source $build_location/install/setup.bash
colcon build --symlink-install