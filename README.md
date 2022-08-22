# Arma-3-External-Radar
Arma 3 external radar.  Built using C++, NodeJS, socket.io and Leaflet!

* Memory RPM/WPM Client (/arma_dma)
* Radar and Communication Server (/nodejs)

## Main Features

* Live radar (player coords, player side, player dead, player direction, player in vehicle)
* Arma 3 Altis map files, multi-user browser access for the radar using LAN/VPN.
* No weapon recoil (not setUnitRecoilCoefficient should bypass most script-based anti cheats)
* No weapon sway (not setCustomAimCoef should bypass most script-based anti cheats)

## How it works
<b>Linux Memory RPM/WPM Client</b><br/>
On the host machine we are able to read and write to our guest machine's memory efficiently and safely using C++ and the memflow connector, arma_dma reads the guest's memory and searches for arma 3, once found it reads all data we need from memory and stores it into a array, the array then gets converted into json format using nlohmann/json and then is sent over to our nodejs server using socket.io.

<b>Radar and Communication Server</b><br/>
The radar relies on NodeJs and socket.io to receive the json data from the Memory RPM/WPM Client (arma_dma). Once received socket.io emits a signal to the front-end containing our player data, it filters through the json and tells Leaflet to setup custom markers for each player.

## Dependencies
<b>Memory RPM/WPM Client (/arma_dma)</b>
* [memflow](https://github.com/memflow/memflow)
* [Socket.IO C++ Client](https://github.com/socketio/socket.io-client-cpp)
* [websocketpp](https://github.com/memflow/memflow)
* [asio](https://github.com/chriskohlhoff/asio)
* [Catch2](https://github.com/catchorg/Catch2/tree/9c07718b5f779bc1405f98ca6b5b693026f6eac7)
* [rapidjson](https://github.com/Tencent/rapidjson/tree/a36110e11874bcf35af854940e0ce910c19a8b49)

<b>Radar and Communication Server (/nodejs)</b>
* [Leaflet](https://github.com/Leaflet/Leaflet)
* [express](https://www.npmjs.com/package/express)
* [socket.io](https://www.npmjs.com/package/socket.io)

## Building
<b>Memory RPM/WPM Client (/arma_dma)</b>
1. Download and install the required dependencies.
2. Navigate to the arma_dma and compile the source by running the script "build.sh". You need to have Rust installed and updated:

`sudo ./build.sh`

3. Navigate to newly created /build folder and run arma_dma as root:
`cd build`
`sudo ./arma_dma`

<b>Radar and Communication Server (/nodejs)</b>

## To do
* Implement server and user authentication.
* Add other Arma 3 maps

## Credits
* [apex_dma_kvm_pub](https://github.com/MisterY52/apex_dma_kvm_pub)
* [Guided Hacking Youtube](https://www.youtube.com/c/GuidedHacking)
* [ARMA 3 Reversal, Structs and Offsets](https://www.unknowncheats.me/forum/arma-3-a/114242-arma-3-reversal-structs-offsets.html)
* [memflow](https://github.com/memflow/memflow)


## Related
[Arma-3-reverse-engineering](https://github.com/Apex-master/Arma-3-reverse-engineering)
