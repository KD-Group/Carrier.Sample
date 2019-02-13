//
// Created by 10189 on 2019/1/5.
//

#ifndef CARRIER_SAMPLE_SAMPLER_FACTORY_HPP
#define CARRIER_SAMPLE_SAMPLER_FACTORY_HPP

#include <iostream>
#include <string>
#include "sampler.hpp"

namespace Sampler {

class SamplerFactory {
public:
    static SamplerPtr get(std::string sampler_name);
};

}


#endif //CARRIER_SAMPLE_SAMPLER_FACTORY_HPP
