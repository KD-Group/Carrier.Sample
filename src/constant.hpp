//
// Created by 10189 on 2019/1/4.
//

#ifndef CARRIER_SAMPLE_CONSTANT_HPP
#define CARRIER_SAMPLE_CONSTANT_HPP

namespace Constant {

const size_t SafeSamplingFrequency = std::size_t(2e7);  //Hz Warning!!! Set to 3e7 will lost some data
const size_t SamplingInterval = 45;    //Hz
const size_t WaveformCount = SafeSamplingFrequency / SamplingInterval;
const size_t MaxBufferSize = WaveformCount * 33;

const double LowerBound = 0.2;
const double UpperBound = 0.8;

const double MinVoltageAmplitude = 0.1;

}

#endif //CARRIER_SAMPLE_CONSTANT_HPP
