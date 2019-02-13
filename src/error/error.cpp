//
// Created by 10189 on 2019/1/5.
//

#include "error.hpp"

namespace Error {

std::string error_code_to_string(Code error_code) {
    switch (error_code) {
        case SUCCESS:
            return "success";
        case COMMAND_NOT_FOUND:
            return "command_not_found";
        case SAMPLER_NOT_FOUND:
            return "sampler_not_found";
        case IN_MEASURING:
            return "in_measuring";
        case VOLTAGE_NOT_ENOUGH:
            return "voltage_not_enough";
        case REAL_SAMPLER_ERROR:
            return "real_sampler_error";
        case WAVE_NOT_FOUND:
            return "wave_not_found";
        case APPROPRIATE_PERCENT_WAVE_NOT_FOUND:
            return "appropriate_percent_wave_not_found";
    }

    return "error_not_found";
}
}
