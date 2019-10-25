//
// Created by wangcong on 2019/10/22.
//

#include "carrier_handler.h"

void CarrierHandler::sample() {
  bool &success = Global::result.success;
  success = true;

  do {
    // Step 1: Get Maximum and Minimum Voltage
    Global::config.set_sampling_count(Constant::WaveformCount * 2);
    success = Global::sampler->sample(Global::config, Global::result);
    if (!success) break;
    success = Processer::align(Global::config, Global::result);
    if (!success) break;

    // Step 2: Adjust Value Range and Sample Full Times
    Global::config.set_sampling_count(Constant::WaveformCount * (Global::config.number_of_waveforms + 1));
    success = Global::sampler->sample(Global::config, Global::result);
    if (!success) break;

    // Step 3: Transfer States : High <----> Low
    success = Processer::summation(Global::config, Global::result);
    if (!success) break;

    // Step 4: Get a Average Wave
    success = Processer::average(Global::config, Global::result);
    if (!success) break;
  } while (false);

  Global::result.measuring = false;
}

#ifdef _WIN32
DWORD WINAPI win_measure(void *) {
CarrierHandler::sample();
return 0;
}
#endif

TCarrier::TReturnCode::type
CarrierHandler::set_sampler(const std::string &sampler_name) {
  Global::sampler = Sampler::SamplerFactory::get(sampler_name);
  if (Global::sampler.get()) {
    return TCarrier::TReturnCode::type::SUCCESS;
  } else {
    return TCarrier::TReturnCode::type::SAMPLER_NOT_FOUND;
  }
}

void CarrierHandler::get_sampler(std::string &_return) {
  if (Global::sampler) {
    _return = Global::sampler->name();
  }
}

TCarrier::TReturnCode::type CarrierHandler::set_sampler_value(const std::string &key,
                                       const double value) {
  if (Global::sampler->set_value(key, value)) {
    return TCarrier::TReturnCode::type::SUCCESS;
  } else {
    return TCarrier::TReturnCode::type::COMMAND_NOT_FOUND;
  }
}
void CarrierHandler::get_sampler_value(std::string &_return,
                                       const std::string &key) {
  _return = Global::sampler->get_value(key);
}
bool CarrierHandler::is_measuring() { return Global::result.measuring; }

TCarrier::TReturnCode::type CarrierHandler::measure(const TCarrier::TSamplingConfig &config) {
  Global::config.update(config.number_of_waveforms, config.first_percent,
                        config.second_percent);

  if (!Global::sampler.get()) {
    return TCarrier::TReturnCode::type::SAMPLER_NOT_FOUND;
  }

  bool &measuring = Global::result.measuring;
  if (measuring) {
    return TCarrier::TReturnCode::type::IN_MEASURING;
  }

  measuring = true;

#ifdef _WIN32
  DWORD handle;
  CreateThread(NULL, 0, win_measure, NULL, 0, &handle);
#else
  // start a thread to do measure
  std::thread(&CarrierHandler::sample).detach();
#endif
  return TCarrier::TReturnCode::type::SUCCESS;
}
void CarrierHandler::to_query(TCarrier::TResult &_return) {
  if (Global::result.measuring) {
    _return.error = true;
    _return.message = "in_measuring";
  }
  bool success = Global::result.success;
  if (success) {
    _return.max_voltage = Global::result.max_voltage;
    _return.min_voltage = Global::result.min_voltage;
    _return.sampling_interval = Global::config.sampling_interval;
    _return.tau = Global::result.tau;
    _return.wave = Global::result.wave;
    _return.error = false;
  } else {
    _return.error = true;
    _return.message = Error::error_code_to_string(Global::result.error_code);
  }
}
