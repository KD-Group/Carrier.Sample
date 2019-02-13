#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <string>
#include "../error/error.hpp"

namespace Commander {
namespace Base {

void line(std::string name, bool value);
void line(std::string name, std::string value);
void line(std::string name, int value);
void line(std::string name, double value);
#define variable(var) line(#var, var);

void error(Error::Code error_code);
void end();

} // namespace Base
} // namespace Commander

#endif
