Welcome to `usage.md`, the usage documentation for WeBridge

# WeBridge Usage Docs

## for C++
`#include WeBridge.h` - main import
`WeBridge::python();` - initialize Python bridge
`WeBridge::js("...");` - you initialize JS bridge with Node.js, V8 or quickJS engine
`.call("module_path", "function_name", args...)` - call function from other language

## for JavaScript
`const WeBridge = require('WeBridge');` - main import
``WeBridge.python("module_path");`` - initialize Python bridge
``WeBridge.cpp("shared_library_path");`` - load C++ shared library (.dll on Windows, .so on Linux)
`.call("function_name", args...)` - call function from other language

## for Python
`from WeBridge import cpp, js` - main import
``cpp("shared_library_path");`` - load C++ shared library (.dll on Windows, .so on Linux)
``js("engine", "module_path");`` - initialize JS bridge with Node.js, V8 or quickJS engine
`.call("function_name", args...)` - call function from other language


---
# Examples

# C++ example

```cpp
// unfortunately for C++, boilerplate is unavoidable for now

auto py = WeBridge::python(); // initialize Python bridge
py.load("src/tools/calc.py"); // load Python module for faster performance (not required)
int result = py.call("src/tools/calc.py", "add", 5, 9); // call Python code
std::cout << result << std::endl; // prints 14

// or for JS

auto js = WeBridge::js("node"); // initialize JS bridge with Node.js engine
int result2 = js.call("src/tools/calc.js", "add", 5, 9); // call JS code
std::cout << result2 << std::endl; // prints 14
```

# JS example

```javascript
const WeBridge = require('WeBridge');

const cpp_module = WeBridge.cpp('src/tools/calc.so') // loads C++ shared library (.dll on Windows, .so on Linux)
const result = cpp_module.add(5, 9); // call C++ function
console.log(result);

// or for Python

const py_module = WeBridge.python('src/example/addition.py'); // load Python
const result2 = py_module.call('add', 5, 9); // call Python function
console.log(result2); // prints 14
```

# Python example

```python
from WeBridge import cpp, js

cpp_lib = cpp("src/tools/calc.dll") # initialize C++ shared library (.dll on Windows, .so on Linux)
print(cpp_lib.add(5, 9))  # 14
print(cpp_lib.add(1, 20)) # 21

# or for JS

# you can choose node, V8 or quickJS
engine = js("node", "src/tools/calc.js")  # initialize once
print(engine.add(5, 9)) # 14
print(engine.add(1, 20)) # 21
```
