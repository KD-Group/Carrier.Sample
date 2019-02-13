//
// Created by 10189 on 2019/1/5.
//

#include "sampler_factory.hpp"
#include "mock_sampler.hpp"

#ifdef _WIN32
    #include "real_sampler.hpp"
#endif

namespace Sampler {

SamplerPtr SamplerFactory::get(std::string sampler_name) {
    SamplerPtr sampler;

    if (sampler_name == "mock_sampler") {
        sampler.reset(new MockSampler);
    }

#ifdef _WIN32
    if (sampler_name == "real_sampler") {
sampler.reset(new RealSampler);
}
#endif

    return sampler;
}

} // namespace Sampler