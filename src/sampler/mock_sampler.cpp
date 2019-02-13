//
// Created by 10189 on 2019/1/5.
//

#include <cmath>
#include <ctime>
#include <iostream>
#include "../constant.hpp"
#include "mock_sampler.hpp"

namespace Sampler {

bool MockSampler::sample(const Config::SamplingConfig &config, Result::SamplingResult &result) {
    srand(unsigned(time(nullptr)));
    for (int i = 0; i < config.current_sampling_count; i++) {
        result.buffer[i] = (rand() % 1000 - 500) / 10000.0 - 0.2;
    }

    for (int i = rand() % 4000; i < (config.current_sampling_count - 2000 * 16); i += Constant::WaveformCount) {
        for (int j = 0; j < 2000 * 16; ++j) {
            double percent = j * 5.0 / (2000 * 16);
            result.buffer[i + j] += 3.3 * exp(-percent);
        }
    }
    return true;
}

std::string MockSampler::name() {
    return "mock_sampler";
}

double MockSampler::get_value(const std::string &key) {
    return 0;
}

bool MockSampler::set_value(const std::string &key, const double value) {
    return true;
}

}
// namespace Sampler