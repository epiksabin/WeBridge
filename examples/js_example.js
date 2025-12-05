/**
 * WeBridge JavaScript Example
 * Demonstrates how to call C++ and Python functions from JavaScript
 */

const WeBridge = require('../src/js/bridge');

async function main() {
    console.log("=== WeBridge JavaScript Examples ===\n");

    // ============================================================
    // Example 1: Load and call C++ shared library
    // ============================================================
    console.log("--- C++ Library Example ---");
    try {
        // Load C++ shared library (.dll on Windows, .so on Linux)
        const cpp_module = WeBridge.getBridge().cpp('src/tools/calc.so');
        
        // Call C++ function directly
        const result = cpp_module.add(5, 9);
        console.log(`Addition: 5 + 9 = ${result}`);  // 14
    } catch (error) {
        console.error(`Error calling C++: ${error.message}`);
    }

    // ============================================================
    // Example 2: Call Python function
    // ============================================================
    console.log("\n--- Python Module Example ---");
    try {
        // Load Python module
        const py_module = WeBridge.getBridge().python('src/example/addition.py');
        
        // Call Python function
        const result = await py_module.call('add', 5, 9);
        console.log(`Python result: ${result}`);  // 14
    } catch (error) {
        console.error(`Error calling Python: ${error.message}`);
    }

    // ============================================================
    // Example 3: Register and call JavaScript function
    // ============================================================
    console.log("\n--- Register Function Example ---");
    try {
        const bridge = WeBridge.getBridge();
        
        // Register a JavaScript function for cross-language calls
        bridge.registerFunction('add', (a, b) => a + b);
        
        // Get the registered function from registry
        const registry = bridge.getRegistry();
        console.log(`Registered functions: ${registry.getFunctionList().join(', ')}`);
        
        // Call registered function
        const result = registry.call('add', [10, 5]);
        console.log(`Function result: ${result}`);  // 15
    } catch (error) {
        console.error(`Error: ${error.message}`);
    }

    // ============================================================
    // Example 4: Type conversion demonstration
    // ============================================================
    console.log("\n--- Type Conversion Example ---");
    try {
        const bridge = WeBridge.getBridge();
        const converter = bridge.getConverter();
        
        // Convert JavaScript values to bridge format
        const intValue = converter.toBridgeValue(42);
        const stringValue = converter.toBridgeValue("hello");
        const arrayValue = converter.toBridgeValue([1, 2, 3]);
        const objectValue = converter.toBridgeValue({ name: "test", value: 123 });
        
        console.log(`Int to bridge: ${JSON.stringify(intValue)}`);
        console.log(`String to bridge: ${JSON.stringify(stringValue)}`);
        console.log(`Array to bridge: ${JSON.stringify(arrayValue)}`);
        console.log(`Object to bridge: ${JSON.stringify(objectValue)}`);
        
        // Convert back to JavaScript
        const restored_int = converter.fromBridgeValue(intValue);
        const restored_array = converter.fromBridgeValue(arrayValue);
        
        console.log(`Restored int: ${restored_int}`);
        console.log(`Restored array: ${restored_array.join(', ')}`);
    } catch (error) {
        console.error(`Error: ${error.message}`);
    }

    // ============================================================
    // Example 5: Multiple language interop
    // ============================================================
    console.log("\n--- Multi-Language Interop Example ---");
    try {
        const bridge = WeBridge.getBridge();
        
        // Load modules from different languages
        const cpp_lib = bridge.cpp('src/tools/calc.so');
        const py_module = bridge.python('src/tools/calc.py');
        
        console.log("JavaScript can now call:");
        console.log("  - C++ functions via cpp_lib.functionName()");
        console.log("  - Python functions via py_module.call('functionName')");
        console.log("  - Other JS functions via registry");
    } catch (error) {
        console.error(`Error: ${error.message}`);
    }

    console.log("\n=== Examples Complete ===");
}

// Run examples
main().catch(error => console.error(error));
