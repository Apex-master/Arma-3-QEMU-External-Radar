# Arma-3-External-Radar
Arma 3 external radar.  Built using C++, NodeJS, socket.io and Leaflet!

* Memory RPM/WPM Client (/arma_dma)
* Radar and Communication Server (/nodejs)

New to Game Hacking? Check:
* [GuidedHacking](https://guidedhacking.com/)
* [Unknowncheats](https://www.unknowncheats.me/forum/index.php)

## Features

* Live radar (player coords, player side, player dead, player direction, player in vehicle)
* No weapon recoil (not setUnitRecoilCoefficient should bypass most script-based anti cheats)
* No weapon sway (not setCustomAimCoef should bypass most script-based anti cheats)

## Applications

* [memflow](https://github.com/memflow/memflow)
* [Leaflet](https://github.com/Leaflet/Leaflet)
* [socket.io](https://github.com/socketio/socket.io-client-cpp)


## How it works
<b>Linux Memory RPM/WPM Client</b><br/>
On the host machine we are able to read and write to our guest machine's memory efficiently and safely using C++ and the memflow connector, arma_dma reads the guest's memory and searches for arma 3, once found it reads all data we need from memory and stores it into a array, the array then gets converted into json format using nlohmann/json and then is sent over to our nodejs server using socket.io.

<b>Radar and Communication Server</b><br/>
The radar relies on NodeJs and socket.io to receive the json data from the Memory RPM/WPM Client (arma_dma). Once received socket.io emits a signal to the front-end containing our player data, it filters through the json and tells Leaflet to setup custom markers for each player.

<b>Bypassing Battleye VM Detections</b><br/>
