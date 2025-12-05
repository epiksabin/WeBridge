/*
    common constants and configurations for OBridge
*/

const Constants = Object.freeze({
    OBRIDGE_VERSION: '0.0.1',
    OBRIDGE_NAME: 'OBridge',

    LANG_PYTHON: 'py',
    LANG_CPP: 'c++',
    LANG_JAVASCRIPT: 'js',

    CPP_MIN_VERSION: 'c++11+',
    PYTHON_MIN_VERSION: '3.11+',

    JS_ENGINE_NODE: 'node',
    JS_ENGINE_V8: 'v8',
    JS_ENGINE_QUICKJS: 'quickjs',

    ErrorCode: Object.freeze({
        SUCCESS: 0,
        FUNCTION_NOT_FOUND: 1,
        TYPE_CONVERSION_ERROR: 2,
        RUNTIME_ERROR: 3,
        INITIALIZATION_ERROR: 4,
        UNSUPPORTED_OPERATION: 5
    }),

    DEFAULT_TIMEOUT_MS: 5000,
    ENABLE_ASYNC_BY_DEFAULT: false,

    BRIDGE_CONFIG: Object.freeze({
        enableLogging: false,
        enableCaching: true,
        maxRetries: 3,
        timeoutMs: 5000
    })
});

if (typeof module !== 'undefined' && module.exports) {
    module.exports = Constants;
}
