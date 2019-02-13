//
// Created by 10189 on 2019/1/5.
//

#ifndef CARRIER_SAMPLE_GLOBAL_HPP
#define CARRIER_SAMPLE_GLOBAL_HPP


#include "../sampler/sampler.hpp"
#include "../config/sampling_config.hpp"
#include "../result/sampling_result.hpp"

class Global {
    public:
    static Sampler::SamplerPtr sampler;
    static Config::SamplingConfig config;
    static Result::SamplingResult result;
};


#endif //CARRIER_SAMPLE_GLOBAL_HPP
