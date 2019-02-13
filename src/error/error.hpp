//
// Created by 10189 on 2019/1/4.
//

#ifndef CARRIER_SAMPLE_ERROR_HPP
#define CARRIER_SAMPLE_ERROR_HPP

#include <string>
#include <unordered_map>
#include <map>

namespace Error {

enum Code {
    SUCCESS,

    // error of human
    COMMAND_NOT_FOUND,
    SAMPLER_NOT_FOUND,
    IN_MEASURING,

    // error of sampling
    VOLTAGE_NOT_ENOUGH,
    REAL_SAMPLER_ERROR,
    WAVE_NOT_FOUND,
    APPROPRIATE_PERCENT_WAVE_NOT_FOUND,
};

std::string error_code_to_string(Code error_code);

}

#endif //CARRIER_SAMPLE_ERROR_HPP
