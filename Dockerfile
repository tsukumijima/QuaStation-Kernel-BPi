# -----------------------------------------------------------------------
# ref: https://github.com/a13xp0p0v/kernel-build-containers
# -----------------------------------------------------------------------

FROM ubuntu:18.04

RUN set -x && echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections && \
    apt-get update && \
    apt-get install -y -q apt-utils aptitude bc bison cpio device-tree-compiler dialog exuberant-ctags file flex git \
        kmod libelf-dev libncurses5-dev libssl-dev make sudo && \
    apt-get install -y -q gcc-7 g++-7 gcc-7-plugin-dev gcc g++ \
        gcc-7-aarch64-linux-gnu g++-7-aarch64-linux-gnu gcc-aarch64-linux-gnu g++-aarch64-linux-gnu \
        gcc-7-arm-linux-gnueabi g++-7-arm-linux-gnueabi gcc-arm-linux-gnueabi g++-arm-linux-gnueabi \
        gcc-7-plugin-dev-aarch64-linux-gnu gcc-7-plugin-dev-arm-linux-gnueabi

RUN sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 100 && \
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 100 && \
    sudo update-alternatives --install /usr/bin/aarch64-linux-gnu-gcc aarch64-linux-gnu-gcc /usr/bin/aarch64-linux-gnu-gcc-7 100 && \
    sudo update-alternatives --install /usr/bin/aarch64-linux-gnu-g++ aarch64-linux-gnu-g++ /usr/bin/aarch64-linux-gnu-g++-7 100 && \
    sudo update-alternatives --install /usr/bin/arm-linux-gnueabi-gcc arm-linux-gnueabi-gcc /usr/bin/arm-linux-gnueabi-gcc-7 100 && \
    sudo update-alternatives --install /usr/bin/arm-linux-gnueabi-g++ arm-linux-gnueabi-g++ /usr/bin/arm-linux-gnueabi-g++-7 100

WORKDIR /build

CMD ["bash"]
