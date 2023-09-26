FROM ubuntu:20.04
ENV TZ=Europe/Moscow \
    DEBIAN_FRONTEND=noninteractive

RUN apt update -y && apt install -y gcc g++ gcc-10 g++-10 git clang-format \
    cmake libpqxx-dev libspdlog-dev libboost1.71-all-dev libjsoncpp-dev libgtest-dev libgmock-dev && \
    git clone https://github.com/jbeder/yaml-cpp.git && mkdir yaml-cpp/build && cd yaml-cpp/build && \
    cmake ../ && make && make install && cd / && \
    cd /usr/src/googletest/googletest && cmake ./ && make && cp lib/*.a /usr/lib

