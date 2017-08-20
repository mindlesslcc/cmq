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

namespace cmq {

Status BrokerManager::FindBroker(const std::string &topic, BrokerInfo *brokerInfo) {
    //get hash for server
    uint32_t hash;
    char address[30];
    boost::crc_32_type crc32;
    
    sprintf(address, "%s", topic.c_str());
    crc32.process_bytes(address, strlen(address));
    hash = crc32();

    std::map<uint32_t, std::shared_ptr<BrokerInfo>>::iterator itr = _brokers.lower_bound(hash);

    if (itr != _brokers.end()) {
        std::shared_ptr<cmq::BrokerInfo> info = itr->second;
        brokerInfo->set_ip(info->ip());
        brokerInfo->set_port(info->port());
        return s_ok;
    }
    std::cout<<"not end"<<std::endl;
    return s_notfind;
}

Status BrokerManager::AddBroker(const std::string &ip, const int32_t &port) {
    //get hash for server
    uint32_t hash;
    char address[30];
    boost::crc_32_type crc32;
    
    sprintf(address, "%s:%d", ip.c_str(), port);
    crc32.process_bytes(address, strlen(address));
    hash = crc32();
 
    std::shared_ptr<BrokerInfo> brokerInfo = std::make_shared<BrokerInfo>();
    brokerInfo->set_ip(ip);
    brokerInfo->set_port(port);

    //insert hash
    _brokers[hash] = brokerInfo;
    return s_ok;
}

Status BrokerManager::DeleteBroker(const std::string &ip, const int32_t &port) {
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
