#pragma once

#include <string>
#include <functional>
#include <map>
#include <memory>
#include <any>
#include <vector>

namespace WeBridge {

/**
 * @brief Type conversion and data exchange interface
*/
class TypeConverter {
public:
    virtual ~TypeConverter() = default;
    
    // convert from C++ types to bridge-compatible format
    virtual std::any to_any(const int& value) const;
    virtual std::any to_any(const double& value) const;
    virtual std::any to_any(const std::string& value) const;
    virtual std::any to_any(const std::vector<std::any>& value) const;
    
    // convert from bridge-compatible format to C++ types
    virtual int to_int(const std::any& value) const;
    virtual double to_double(const std::any& value) const;
    virtual std::string to_string(const std::any& value) const;
    virtual std::vector<std::any> to_vector(const std::any& value) const;
};

/**
 * @brief Function registry for cross-language calls
 */
class FunctionRegistry {
public:
    using FunctionCallback = std::function<std::any(const std::vector<std::any>&)>;
    
    /*
        register a callable function
    */
    void register_function(const std::string& name, FunctionCallback callback);
    
    /*
        call a registered function
    */
    std::any call_function(const std::string& name, const std::vector<std::any>& args);
    
    /*
        check if function exists
    */
    bool has_function(const std::string& name) const;
    
    /*
        unregister a function
    */
    void unregister_function(const std::string& name);
    
private:
    std::map<std::string, FunctionCallback> m_functions;
};

/**
 * @brief Python bridge handle
 */
class PythonBridge {
public:
    PythonBridge();
    ~PythonBridge();
    
    /*
        load Python module for better performance (optional)
    */
    void load(const std::string& module_path);
    
    /*
        call a Python function
    */
    template<typename... Args>
    std::any call(const std::string& module_path, const std::string& function_name, Args... args) {
        std::vector<std::any> arg_list = {std::any(args)...};
        return call_impl(module_path, function_name, arg_list);
    }
    
private:
    std::any call_impl(const std::string& module_path, const std::string& function_name, 
                       const std::vector<std::any>& args);
    std::map<std::string, void*> m_loaded_modules;  // cache loaded modules
    void* m_python_interpreter = nullptr;
};

/**
 * @brief C++ shared library module wrapper
 */
class CppModule {
public:
    explicit CppModule(const std::string& library_path);
    ~CppModule();
    
    /*
        call function directly with variadic args
    */
    template<typename... Args>
    std::any call(const std::string& function_name, Args... args) {
        std::vector<std::any> arg_list = {std::any(args)...};
        return call_impl(function_name, arg_list);
    }
    
    /*
        get raw function pointer for advanced usage
    */
    void* get_function(const std::string& function_name);
    
private:
    std::any call_impl(const std::string& function_name, const std::vector<std::any>& args);
    void* m_library_handle = nullptr;
    std::string m_library_path;
};

/**
 * @brief javaScript bridge handle
 */
class JavaScriptBridge {
public:
    explicit JavaScriptBridge(const std::string& engine = "node");
    ~JavaScriptBridge();
    
    /*
        call a JavaScript function
    */
    template<typename... Args>
    std::any call(const std::string& module_path, const std::string& function_name, Args... args) {
        std::vector<std::any> arg_list = {std::any(args)...};
        return call_impl(module_path, function_name, arg_list);
    }
    
private:
    std::any call_impl(const std::string& module_path, const std::string& function_name,
                       const std::vector<std::any>& args);
    std::string m_engine;
    void* m_engine_context = nullptr;
};

/**
 * @brief main namespace for WeBridge C++ API
 */
namespace cpp {
    /*
        initialize and get Python bridge
    */
    PythonBridge python();
    
    /*
        load C++ shared library
    */
    CppModule load(const std::string& library_path);
    
    /*
        initialize and get JavaScript bridge with specified engine
    */
    JavaScriptBridge js(const std::string& engine = "node");
}

} // namespace WeBridge
