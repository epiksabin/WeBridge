
#include "../src/cpp/include/bridge.hpp"
#include <iostream>
#include <vector>

using namespace WeBridge;

int main() {
    try {
        // initialize Python bridge
        auto py = cpp::python();
        
        // call Python function: addition(5, 9)
        std::vector<std::any> args = {std::any(5), std::any(9)};
        std::any result = py.call_impl("tests/aa.py", "addition", args);
        
        // extract int result
        int answer = std::any_cast<int>(result);
        
        std::cout << "python result: " << answer << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }
}
