#include "../include/bridge.hpp"
#include <iostream>

namespace WeBridge {

/**
 * @brief Utility functions for type conversion
 */
namespace utils {

/*
    safe type casting with error handling
*/
template<typename Target>
Target safe_cast(const std::any& value) {
    try {
        return std::any_cast<Target>(value);
    } catch (const std::bad_any_cast& e) {
        throw std::runtime_error("Type conversion failed: " + std::string(e.what()));
    }
}

/*
    check if value can be converted to target type
*/
bool can_convert_to_int(const std::any& value) {
    return value.type() == typeid(int) || 
           value.type() == typeid(double) ||
           value.type() == typeid(float);
}

bool can_convert_to_double(const std::any& value) {
    return value.type() == typeid(double) || 
           value.type() == typeid(int) ||
           value.type() == typeid(float);
}

} // namespace utils

} // namespace WeBridge
