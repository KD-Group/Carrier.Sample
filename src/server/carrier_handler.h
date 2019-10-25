//
// Created by wangcong on 2019/10/22.
//

#ifndef CARRIER_SAMPLE_CARRIER_HANDLER_H
#define CARRIER_SAMPLE_CARRIER_HANDLER_H

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
// #include <glog/logging.h>

#include "../gen-cpp/TCarrier.h"
#include "../gen-cpp/carrier_types.h"
#include "../global/global.hpp"
#include "../sampler/sampler_factory.hpp"
#include "../processer/processer.hpp"

#ifdef _WIN32
  #include "Windows.h"
#else
  #include <thread>
  #include <chrono>
#endif

class CarrierHandler : public TCarrier::TCarrierIf {
public:
  CarrierHandler(){};
  TCarrier::TReturnCode::type set_sampler(const std::string& sampler_name) override;
  void get_sampler(std::string &_return) override;
  TCarrier::TReturnCode::type set_sampler_value(const std::string &key, const double value) override;
  void get_sampler_value(std::string &_return, const std::string &key) override;
  bool is_measuring() override;
  TCarrier::TReturnCode::type measure(const TCarrier::TSamplingConfig &config) override;
  void to_query(TCarrier::TResult &_return) override;

  static void sample();
};

//class CarrierCloneFactory : virtual public TCarrier::TCarrierIfFactory {
//public:
//  ~CarrierCloneFactory() override = default;
//  TCarrier::TCarrierIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) override {
//    boost::shared_ptr<apache::thrift::transport::TSocket> sock =
//        std::dynamic_pointer_cast<apache::thrift::transport::TSocket>(connInfo.transport);
    // LOG(INFO) << "Incoming connection";
    // LOG(INFO) << "\tSocketInfo: "  << sock->getSocketInfo();
    // LOG(INFO) << "\tPeerHost: "    << sock->getPeerHost();
    // LOG(INFO) << "\tPeerAddress: " << sock->getPeerAddress();
    // LOG(INFO) << "\tPeerPort: "    << sock->getPeerPort();
//    return new CarrierHandler;
//  }
//
//  void releaseHandler(TCarrier::TCarrierIf* handler) override {
//    delete handler;
//  }
//};

#endif // CARRIER_SAMPLE_CARRIER_HANDLER_H
