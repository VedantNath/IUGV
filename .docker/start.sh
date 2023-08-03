#!/bin/bash

./base.sh

docker exec -it \
--env="DISPLAY" \
--env="QT_X11_NO_MITSHM=1" \
 iugv_robot bash -c /root/iugv/src/.docker/start_robot.sh
