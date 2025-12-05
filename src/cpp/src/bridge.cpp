#include "../include/bridge.hpp"
#include <stdexcept>
#include <typeinfo>

namespace WeBridge {

// ===============-===============-===============
/*
    TypeConverter implementation
*/

std::any TypeConverter::to_any(const int& value) const {
    return std::any(value);
}

std::any TypeConverter::to_any(const double& value) const {
    return std::any(value);
}

std::any TypeConverter::to_any(const std::string& value) const {
    return std::any(value);
}

std::any TypeConverter::to_any(const std::vector<std::any>& value) const {
    return std::any(value);
}

int TypeConverter::to_int(const std::any& value) const {
    if (value.type() == typeid(int)) {
        return std::any_cast<int>(value);
    }
    throw std::runtime_error("Cannot convert to int");
}

double TypeConverter::to_double(const std::any& value) const {
    if (value.type() == typeid(double)) {
        return std::any_cast<double>(value);
    } else if (value.type() == typeid(int)) {
        return static_cast<double>(std::any_cast<int>(value));
    }
    throw std::runtime_error("Cannot convert to double");
}

std::string TypeConverter::to_string(const std::any& value) const {
    if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    throw std::runtime_error("Cannot convert to string");
}

std::vector<std::any> TypeConverter::to_vector(const std::any& value) const {
    if (value.type() == typeid(std::vector<std::any>)) {
        return std::any_cast<std::vector<std::any>>(value);
    }
    throw std::runtime_error("Cannot convert to vector");
}

// ===============-===============-===============
/*
    FunctionRegistry implementation
*/

void FunctionRegistry::register_function(const std::string& name, FunctionCallback callback) {
    m_functions[name] = callback;
}

std::any FunctionRegistry::call_function(const std::string& name, const std::vector<std::any>& args) {
    auto it = m_functions.find(name);
    if (it == m_functions.end()) {
        throw std::runtime_error("Function '" + name + "' not found");
    }
    return it->second(args);
}

bool FunctionRegistry::has_function(const std::string& name) const {
    return m_functions.find(name) != m_functions.end();
}

void FunctionRegistry::unregister_function(const std::string& name) {
    m_functions.erase(name);
}

// ===============-===============-===============
/*
    PyBridge implementation
*/

PythonBridge::PythonBridge() {
    // TODO: Initialize Python interpreter if not already initialized
    // This would typically call Py_Initialize() from the Python C API
}

PythonBridge::~PythonBridge() = default;

void PythonBridge::load(const std::string& module_path) {
    // check if already loaded
    if (m_loaded_modules.find(module_path) != m_loaded_modules.end()) {
        return;
    }
    
    // TODO: Load Python module using Python C API
    // This would use PyImport_ImportModule(module_path.c_str())
    // and cache the result in m_loaded_modules
}

std::any PythonBridge::call_impl(const std::string& module_path, 
                                 const std::string& function_name,
                                 const std::vector<std::any>& args) {
    try {
        // TODO: Implement Python function calling via Python C API
        // 1. Load module if not already loaded
        // 2. Get function object from module
        // 3. Convert C++ args to Python objects
        // 4. Call the function
        // 5. Convert result back to C++ std::any
        
        throw std::runtime_error("Python interop implementation pending");
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to call Python function '" + function_name + "': " + e.what());
    }
}

// ===============-===============-===============
/*
    CppModule implementation
*/

CppModule::CppModule(const std::string& library_path) 
    : m_library_path(library_path) {
    // TODO: Load C++ shared library using dlopen (Linux) or LoadLibraryA (Windows)
    // On Windows: m_library_handle = LoadLibraryA(library_path.c_str())
    // On Linux: m_library_handle = dlopen(library_path.c_str(), RTLD_LAZY)
    
    if (!m_library_handle) {
        throw std::runtime_error("Failed to load library: " + library_path);
    }
}

CppModule::~CppModule() {
    // TODO: Unload the library using dlclose (Linux) or FreeLibrary (Windows)
    // if (m_library_handle) {
    //     dlclose(m_library_handle);
    //     m_library_handle = nullptr;
    // }
}

void* CppModule::get_function(const std::string& function_name) {
    // TODO: Get function pointer from loaded library using dlsym (Linux) or GetProcAddress (Windows)
    // On Windows: return GetProcAddress((HMODULE)m_library_handle, function_name.c_str())
    // On Linux: return dlsym(m_library_handle, function_name.c_str())
    
    if (!m_library_handle) {
        throw std::runtime_error("Library not loaded");
    }
    
    void* func_ptr = nullptr;
    // TODO: Platform-specific function loading
    
    if (!func_ptr) {
        throw std::runtime_error("Function '" + function_name + "' not found in library");
    }
    
    return func_ptr;
}

std::any CppModule::call_impl(const std::string& function_name, const std::vector<std::any>& args) {
    try {
        // TODO: Implement C++ function calling
        // 1. Get function pointer from loaded library
        // 2. Determine function signature (would need metadata or templates)
        // 3. Call function with arguments
        // 4. Return result as std::any
        
        throw std::runtime_error("C++ function calling implementation pending");
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to call C++ function '" + function_name + "': " + e.what());
    }
}

// ===============-===============-===============
/*
    JSbridge implementation
*/

JavaScriptBridge::JavaScriptBridge(const std::string& engine) 
    : m_engine(engine) {
    // TODO: Initialize JavaScript engine context
    // For Node.js: Create child process or load node library
    // For V8: Create V8 Isolate and Context
    // For quickJS: Create JSRuntime and JSContext
}

JavaScriptBridge::~JavaScriptBridge() {
    // TODO: Clean up JavaScript engine context
    // Free resources allocated during initialization
}

std::any JavaScriptBridge::call_impl(const std::string& module_path,
                                     const std::string& function_name,
                                     const std::vector<std::any>& args) {
    try {
        // TODO: Implement JavaScript function calling via specified engine
        // 1. Load JavaScript module
        // 2. Get function from module
        // 3. Convert C++ args to JavaScript values
        // 4. Call the function
        // 5. Convert result back to C++ std::any
        
        throw std::runtime_error("JavaScript interop implementation pending");
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to call JavaScript function '" + function_name + "': " + e.what());
    }
}

// ==================== WeBridge namespace ====================

namespace cpp {

PythonBridge python() {
    return PythonBridge();
}

CppModule load(const std::string& library_path) {
    return CppModule(library_path);
}

JavaScriptBridge js(const std::string& engine) {
    return JavaScriptBridge(engine);
}

} // namespace cpp

} // namespace WeBridge
