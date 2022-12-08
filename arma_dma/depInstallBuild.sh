#!/bin/bash
mv -v utils/* .
pacman -S make websocketpp asio rapidjson
./build.sh
mv sio_* utils 
mv json.hpp utils