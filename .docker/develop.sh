#!/bin/bash

./base.sh

docker cp $PWD/.vscode iugv_robot:/root/iugv/.vscode

docker exec -it \
--env="DISPLAY" \
--env="QT_X11_NO_MITSHM=1" \
 iugv_robot bash
