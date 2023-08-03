#!/bin/bash

./stop.sh

xhost +local:root

docker run -t --privileged -d --net=host \
--name iugv_robot \
-v $PWD/..:/root/iugv/src \
--env="DISPLAY" \
--env="QT_X11_NO_MITSHM=1" \
 iugv:latest 

docker exec -it \
--env="DISPLAY" \
--env="QT_X11_NO_MITSHM=1" \
 iugv_robot bash -c ./src/.docker/compile.sh ..
