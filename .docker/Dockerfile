FROM ros:humble

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get clean && rm -rf /var/lib/apt/lists/* && \
    apt-get update && apt-get upgrade -y

RUN mkdir tmp/runtime-root && chmod 0700 tmp/runtime-root
ENV XDG_RUNTIME_DIR='/tmp/runtime-root'

RUN apt-get install -y \
    python3-pip \
    ros-humble-cyclonedds \
    ros-humble-rmw-cyclonedds-cpp \
    ros-humble-hardware-interface \
    wget unzip

SHELL ["/bin/bash", "-c"]

RUN cd /root && \
    wget https://github.com/joan2937/pigpio/archive/master.zip \
    && unzip master.zip \ 
    && cd pigpio-master \
    && make \ 
    && make install

WORKDIR /root/iugv