//
// Created by 10189 on 2019/1/4.
//

#include "sampling_config.hpp"
#include "../constant.hpp"

namespace Config {

void SamplingConfig::update(int number_of_waveforms, double first_percent, double second_percent) {
    this->number_of_waveforms = number_of_waveforms;
    this->first_percent = first_percent;
    this->second_percent = second_percent;
    this->sampling_interval = 1e6 / Constant::SafeSamplingFrequency;
}

void SamplingConfig::set_sampling_count(size_t count) {
    this->current_sampling_count = count;
}

}
