/*
 * OBridge C++ Example
 * Demonstrates how to call Python and JavaScript functions from C++
 */

#include "../src/cpp/include/bridge.hpp"
#include <iostream>

using namespace OBridge;

int main() {
    std::cout << "=== OBridge C++ Examples ===" << std::endl;

    // ============================================================
    // Example 1: Call Python function
    // ============================================================
    std::cout << "\n--- Python Example ---" << std::endl;
    
    try {
        auto py = cpp::python();  // initialize Python bridge
        
        // Optional: preload module for better performance
        py.load("src/tools/calc.py");
        
        // Call Python function with arguments
        std::any result = py.call("src/tools/calc.py", "add", 5, 9);
        
        // Convert result to int and print
        int py_result = std::any_cast<int>(result);
        std::cout << "Python result: " << py_result << std::endl;  // prints 14
    } catch (const std::exception& e) {
        std::cerr << "Error calling Python: " << e.what() << std::endl;
    }

    // ============================================================
    // Example 2: Call JavaScript function
    // ============================================================
    std::cout << "\n--- JavaScript Example ---" << std::endl;
    
    try {
        auto js = cpp::js("node");  // initialize JS bridge with Node.js engine
        
        // Call JavaScript function
        std::any result = js.call("src/tools/calc.js", "add", 5, 9);
        
        // Convert result to int and print
        int js_result = std::any_cast<int>(result);
        std::cout << "JavaScript result: " << js_result << std::endl;  // prints 14
    } catch (const std::exception& e) {
        std::cerr << "Error calling JavaScript: " << e.what() << std::endl;
    }

    // ============================================================
    // Example 3: Load and call C++ shared library
    // ============================================================
    std::cout << "\n--- C++ Library Example ---" << std::endl;
    
    try {
        #ifdef _WIN32
            auto cpp_lib = cpp::load("src/tools/calc.dll");
        #else
            auto cpp_lib = cpp::load("src/tools/calc.so");
        #endif
        
        // Call C++ function directly (syntax similar to Python)
        std::any result = cpp_lib.call("add", 5, 9);
        
        // Convert result to int and print
        int cpp_result = std::any_cast<int>(result);
        std::cout << "C++ library result: " << cpp_result << std::endl;  // prints 14
    } catch (const std::exception& e) {
        std::cerr << "Error calling C++ library: " << e.what() << std::endl;
    }

    // ============================================================
    // Example 4: Multiple calls with different arguments
    // ============================================================
    std::cout << "\n--- Multiple Calls Example ---" << std::endl;
    
    try {
        auto py = cpp::python();
        
        std::any result1 = py.call("src/tools/calc.py", "add", 1, 20);
        std::any result2 = py.call("src/tools/calc.py", "multiply", 4, 5);
        
        std::cout << "Addition: " << std::any_cast<int>(result1) << std::endl;    // 21
        std::cout << "Multiplication: " << std::any_cast<int>(result2) << std::endl;  // 20
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Examples Complete ===" << std::endl;
    return 0;
}
