
#include "../src/cpp/include/bridge.hpp"
#include <iostream>

using namespace OBridge;

int main() {
    try {
        // initialize Python bridge
        auto py = cpp::python();
        
        // call Python function: addition(5, 9)
        std::any result = py.call("aa.py", "addition", 5, 9);
        
        // extract int result
        int answer = std::any_cast<int>(result);
        
        std::cout << "python result: " << answer << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }
}
