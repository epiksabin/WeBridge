# WeBridge Installation Guide

Welcome to WeBridge! This guide will help you set up WeBridge for seamless integration between Python, C++, and JavaScript.

---

## Table of Contents
1. [System Requirements](#system-requirements)
2. [Prerequisites](#prerequisites)
3. [Installation Steps](#installation-steps)
4. [Verification](#verification)
5. [Troubleshooting](#troubleshooting)
6. [Next Steps](#next-steps)

---

## System Requirements

### Supported Operating Systems
- **Windows**: Windows 10 and above
- **Linux**: Any modern Linux distribution (Ubuntu 18.04+, CentOS 7+, etc.)
- **macOS**: macOS 10.13+

### Supported Languages & Versions
- **Python**: 3.11.0 or higher
- **C++**: C++11 and above
- **JavaScript**: Node.js, V8, or quickJS

---

## Prerequisites

### For All Platforms

1. **Git** - For cloning the repository
   ```bash
   # Check if git is installed
   git --version
   ```

2. **CMake** - Version 3.16 or higher (for building from source)
   ```bash
   # Download from: https://cmake.org/download/
   # Or install via package manager:
   # Ubuntu/Debian: sudo apt-get install cmake
   # macOS (Homebrew): brew install cmake
   # Windows (Chocolatey): choco install cmake
   ```

3. **Python Development Headers**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install python3-dev

   # macOS (Homebrew)
   brew install python@3.11

   # Windows
   # Download from https://www.python.org/downloads/
   # Make sure to check "Install development headers" during installation
   ```

### For C++ Development

1. **C++ Compiler**
   - **Windows**: Visual Studio 2015 or newer (with C++ workload)
   - **Linux**: GCC 7+ or Clang 5+
   - **macOS**: Xcode Command Line Tools
   ```bash
   # macOS
   xcode-select --install
   ```

### For JavaScript Integration

1. **Node.js** (if using Node.js engine)
   ```bash
   # Download from: https://nodejs.org/
   # Or via package manager:
   # Ubuntu/Debian: sudo apt-get install nodejs npm
   # macOS (Homebrew): brew install node
   ```

---

## Installation Steps

### Step 1: Clone the Repository

```bash
git clone https://github.com/epiksabin/WeBridge.git
cd WeBridge
```

### Step 2: Create a Build Directory

```bash
mkdir build
cd build
```

### Step 3: Configure the Project with CMake

```bash
# On Linux/macOS
cmake ..

# On Windows (with Visual Studio)
cmake -G "Visual Studio 16 2019" ..

# Or on Windows (with MinGW)
cmake -G "MinGW Makefiles" ..
```

**CMake will:**
- Detect Python installation
- Verify C++ compiler
- Set up build configuration
- Display build information

### Step 4: Build the Project

```bash
# On Linux/macOS
cmake --build . --config Release

# On Windows (if using Visual Studio)
cmake --build . --config Release

# Or use the native build tool
# Linux/macOS: make
# Windows: msbuild WeBridge.sln /p:Configuration=Release
```

**Build output:**
- Static library: `lib/libobridge.a` (Linux/macOS) or `lib/WeBridge.lib` (Windows)
- Test executable: `bin/test_obridge`
- Examples: `bin/cpp_example`

### Step 5: Verify Installation

```bash
# Run tests
ctest

# Or run the test directly
./bin/test_obridge

# On Windows
.\bin\test_obridge.exe
```

---

## Verification

### Test Basic Functionality

#### For C++
Create a simple test file `test_basic.cpp`:
```cpp
#include "WeBridge/bridge.hpp"
#include <iostream>

using namespace WeBridge;

int main() {
    try {
        auto py = cpp::python();
        std::any result = py.call("examples/calc.py", "add", 5, 9);
        int answer = std::any_cast<int>(result);
        std::cout << "Result: " << answer << std::endl;  // prints 14
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
```

#### For Python
Create a simple test file `test_basic.py`:
```python
from WeBridge import cpp, js

# Test C++ library loading
try:
    cpp_lib = cpp("path/to/compiled/library.dll")
    result = cpp_lib.add(5, 9)
    print(f"C++ Result: {result}")
except Exception as e:
    print(f"Error: {e}")
```

#### For JavaScript
Create a simple test file `test_basic.js`:
```javascript
const WeBridge = require('WeBridge');

const bridge = WeBridge.getBridge();
const py_module = bridge.python('examples/calc.py');

py_module.call('add', 5, 9).then(result => {
    console.log(`Result: ${result}`);  // prints 14
}).catch(error => {
    console.error(`Error: ${error.message}`);
});
```

---

## Troubleshooting

### Common Issues

#### 1. "Python not found" error
```
CMake Error: Could not find Python3 development headers
```

**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install python3-dev

# Specify Python path manually
cmake .. -DPYTHON_EXECUTABLE=/usr/bin/python3
```

#### 2. "C++ compiler not found" error
```
CMake Error: No C++ compiler found
```

**Solution:**
- **Windows**: Install Visual Studio with C++ workload
- **Linux**: `sudo apt-get install build-essential`
- **macOS**: `xcode-select --install`

#### 3. Build fails on Windows
```
error: Microsoft Visual C++ 14.0 or greater is required
```

**Solution:**
- Download and install [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/downloads/)
- Select "Desktop development with C++" workload

#### 4. CMake configuration fails
```
CMake Error: Could not find CMake modules
```

**Solution:**
- Update CMake: Download from https://cmake.org/download/
- Or via package manager: `sudo apt-get upgrade cmake`

#### 5. Tests don't run
```
ctest: No tests found
```

**Solution:**
```bash
# Make sure tests are built
cmake --build . --config Release

# Run tests explicitly
./bin/test_obridge
```

#### 6. Module import errors in Python
```
ModuleNotFoundError: No module named 'WeBridge'
```

**Solution:**
```bash
# Add WeBridge to Python path
export PYTHONPATH="${PYTHONPATH}:/path/to/WeBridge/src/python"

# Or install in development mode
cd src/python
pip install -e .
```

---

## Installation Verification Checklist

- Git repository cloned successfully
- Build directory created
- CMake configuration successful
- Build completed without errors
- Tests pass: `ctest` returns 0
- Examples run successfully
- Python module imports without errors
- C++ headers found in include path
- JavaScript module loads in Node.js

---

## Platform-Specific Notes

### Windows

1. **Visual Studio Installation:**
   - Download from https://visualstudio.microsoft.com/
   - Select "Desktop development with C++"
   - Include C++ MFC and Windows SDK

2. **Python Installation:**
   - Download from https://www.python.org/downloads/
   - **Important**: Check "Add Python to PATH" and "Install development headers"

3. **Building:**
   ```bash
   # Use Visual Studio Generator
   cmake -G "Visual Studio 16 2019" ..
   cmake --build . --config Release
   ```

### Linux

1. **Dependencies:**
   ```bash
   sudo apt-get update
   sudo apt-get install python3-dev cmake build-essential
   ```

2. **Building:**
   ```bash
   cmake ..
   make -j$(nproc)
   ```

### macOS

1. **Dependencies:**
   ```bash
   brew install python@3.11 cmake
   xcode-select --install
   ```

2. **Building:**
   ```bash
   cmake ..
   make -j$(sysctl -n hw.ncpu)
   ```

---

## Next Steps

After successful installation:

1. **Read the Usage Guide**: See `docs/usage.md` for API details
2. **Explore Examples**: Check `examples/` directory for language-specific examples
3. **Run Tests**: Execute test suite to verify functionality
4. **Build Your App**: Start integrating WeBridge into your project

### Quick Start Examples

```cpp
// C++ - Call Python
auto py = cpp::python();
auto result = py.call("module.py", "function", arg1, arg2);
```

```python
# Python - Load C++ library
cpp_lib = cpp("library.dll")
result = cpp_lib.function(arg1, arg2)
```

```javascript
// JavaScript - Initialize Python bridge
const bridge = require('WeBridge').getBridge();
const py = bridge.python('module.py');
```

---

## Getting Help

- **Documentation**: Read `docs/` directory
- **Examples**: Check `examples/` directory for language-specific examples
- **Issues**: Report bugs on [GitHub Issues](https://github.com/epiksabin/WeBridge/issues)
- **Contributing**: See `docs/contributing.md` for contribution guidelines

---

## Support Matrix

| Language | Platform | Status | Notes |
|----------|----------|--------|-------|
| Python 3.11+ | All | ✅ Supported | Requires development headers |
| C++ | All | ✅ Supported | C++11 or higher |
| JavaScript | All | ✅ Supported | Node.js, V8, quickJS |
| Async Calls | All | 🔄 Planned | Coming soon |

<!-- thanks to https://www.tablesgenerator.com/markdown_tables -->

---

## License

WeBridge is released under the Apache 2.0 License. See [LICENSE](../LICENSE) file for details.

---

**Happy coding with WeBridge!** 🚀
