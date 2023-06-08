#!/usr/bin/env bash
#
# Copyright (c) 2019-2020 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C.UTF-8

export CONTAINER_NAME=ci_native_qt5
export DOCKER_NAME_TAG=ubuntu:18.04  # Check that bionic gcc-7 can compile our c++17 and run our functional tests in python3, see doc/dependencies.md
export PACKAGES="python3-zmq qtbase5-dev qttools5-dev-tools libdbus-1-dev libharfbuzz-dev protobuf-compiler libprotobuf-dev"
export DEP_OPTS="NO_QT=1 NO_UPNP=1 NO_NATPMP=1 DEBUG=1 ALLOW_HOST_PACKAGES=1"
# Exclude --bitcoin and --coverage to prevent timeouts
export TEST_RUNNER_EXTRA="--previous-releases --extended --exclude feature_dbcrash,feature_block"  # Run extended tests so that coverage does not fail, but exclude the very slow dbcrash
#export TEST_RUNNER_BITCOIN="--bitcoin"
export RUN_UNIT_TESTS_SEQUENTIAL="true"
export RUN_UNIT_TESTS="false"
export GOAL="install"
export PREVIOUS_RELEASES_TO_DOWNLOAD="v0.18.1.7 v0.19.2.3"
export BITCOIN_CONFIG="--enable-zmq --with-libs=no --with-gui=qt5 --enable-glibc-back-compat --enable-reduce-exports
--enable-debug --disable-fuzz-binary  CFLAGS=\"-g0 -O2 -funsigned-char\" CXXFLAGS=\"-g0 -O2 -funsigned-char\" --enable-usbdevice"
