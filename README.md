Distributed Message Queue
===

this Distributed Message Queue consists of master and broker, master transport user's subscribe/publish request to broker.


Quick Start
---
    sh build.sh
    bin/master &
    bin/broker &
use client
---
    bin/client
    >put topic message
    >get topic

Performance Benchmark
---
    CMQ running in virtual machine ubuntu-14.04, Intel(R) Core(TM) i5-4278U CPU @ 2.60GHz, APPLE SSD SD0128F 128GB
    put 10000 messages Runtime： 470.918 ms!
    get 10000 messages Runtime： 459.562 ms!
