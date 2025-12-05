#pragma once

#include <string>

namespace WeBridge {
namespace Common {

constexpr const char* OBRIDGE_VERSION = "0.0.1";
constexpr const char* OBRIDGE_NAME = "WeBridge";

constexpr const char* LANG_PYTHON = "py";
constexpr const char* LANG_CPP = "c++";
constexpr const char* LANG_JAVASCRIPT = "js";

constexpr const char* CPP_MIN_VERSION = "c++11+";
constexpr const char* PYTHON_MIN_VERSION = "3.11+";

constexpr const char* JS_ENGINE_NODE = "node";
constexpr const char* JS_ENGINE_V8 = "v8";
constexpr const char* JS_ENGINE_QUICKJS = "quickjs";

enum class ErrorCode {
    SUCCESS = 0,
    FUNCTION_NOT_FOUND = 1,
    TYPE_CONVERSION_ERROR = 2,
    RUNTIME_ERROR = 3,
    INITIALIZATION_ERROR = 4,
    UNSUPPORTED_OPERATION = 5
};

constexpr int DEFAULT_TIMEOUT_MS = 5000;
constexpr bool ENABLE_ASYNC_BY_DEFAULT = false;

} // namespace Common
} // namespace WeBridge
