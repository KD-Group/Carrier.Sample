//
// Created by 10189 on 2019/1/5.
//

#ifndef CARRIER_SAMPLE_MOCKSAMPLER_HPP
#define CARRIER_SAMPLE_MOCKSAMPLER_HPP

#include "sampler.hpp"

namespace Sampler {

    class MockSampler : public Sampler {
    public:

        bool sample(const Config::SamplingConfig &config, Result::SamplingResult &result) override ;
        std::string name() override ;

        double get_value(const std::string &key) override ;
        bool set_value(const std::string &key, const double value) override ;
    };

}


#endif //CARRIER_SAMPLE_MOCKSAMPLER_HPP
