//
// Created by 10189 on 2019/1/5.
//

#ifndef CARRIER_SAMPLE_SAMPLING_RESULT_HPP
#define CARRIER_SAMPLE_SAMPLING_RESULT_HPP

#include <vector>

#include "../constant.hpp"
#include "../error/error.hpp"

namespace Result {

struct SamplingResult {
    SamplingResult()
    : success(true),
      measuring(false),
      max_voltage(0),
      min_voltage(0),
      tau(0.0),
      copy_length(0),
      error_code(Error::SUCCESS) {
        this->buffer.resize(Constant::MaxBufferSize);
        this->wave.resize(Constant::WaveformCount);
    }

    std::vector<double> buffer;
    std::vector<double> wave;
    std::vector<double> average_wave;

    bool success;
    bool measuring;
    double max_voltage;
    double min_voltage;
    double tau;
    int copy_length;
    Error::Code error_code;
};

}

#endif //CARRIER_SAMPLE_SAMPLING_RESULT_HPP
