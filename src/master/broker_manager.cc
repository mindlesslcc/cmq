#include "broker_manager.h"

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>
#include <grpc++/grpc++.h>
#include <gflags/gflags.h>

#include "common.pb.h"

namespace mq {

Status BrokerManager::AddBroker(std::string ip, int32_t port) {
    //get hash for server
    uint32_t hash;
    char address[30];
    boost::crc_32_type crc32;
    
    sprintf(address, "%s:%d", ip.c_str(), port);
    crc32.process_bytes(address, strlen(address));
    hash = crc32();
 
    BrokerInfo* brokerInfo = new BrokerInfo;
    brokerInfo->set_ip(ip);
    brokerInfo->set_port(port);

    //insert hash
    _brokers[hash] = brokerInfo;
    return s_ok;
}

Status BrokerManager::DeleteBroker(std::string ip, int32_t port) {
    //find hash for server
    uint32_t hash;
    char address[30];
    boost::crc_32_type crc32;
    
    sprintf(address, "%s:%d", ip.c_str(), port);
    crc32.process_bytes(address, strlen(address));
    hash = crc32();
    if (_brokers.find(hash) == _brokers.end()) {
        return s_notfind;
    }
    //delete server
    _brokers.erase(hash);
    return s_ok;
}

}
