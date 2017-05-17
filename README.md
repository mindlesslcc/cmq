Distributed Message Queue
===

this Distributed Message Queue consists of master and broker, master transport user's subscribe/publish request to broker.


Quick Start
---
sh build.sh
bin/master &
bin/broker &
bin/client
put topic message
get topic

Benchmark
---
put 10000 messages Runtime： 470.918 ms!
get 10000 messages Runtime： 459.562 ms!
