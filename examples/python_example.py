"""
OBridge Python Example
Demonstrates how to call C++ and JavaScript functions from Python
"""

from src.python.bridge import cpp, js

def main():
    print("=== OBridge Python Examples ===\n")

    # ============================================================
    # Example 1: Load and call C++ shared library
    # ============================================================
    print("--- C++ Library Example ---")
    try:
        # Load C++ shared library (.dll on Windows, .so on Linux)
        cpp_lib = cpp("src/tools/calc.dll")
        
        # Call C++ function directly
        result1 = cpp_lib.add(5, 9)
        result2 = cpp_lib.add(1, 20)
        
        print(f"Addition 5 + 9 = {result1}")   # 14
        print(f"Addition 1 + 20 = {result2}")  # 21
    except Exception as e:
        print(f"Error calling C++: {e}")

    # ============================================================
    # Example 2: Call JavaScript function
    # ============================================================
    print("\n--- JavaScript Example ---")
    try:
        # Initialize JS bridge with Node.js engine
        # You can choose node, V8 or quickJS
        engine = js("node", "src/tools/calc.js")
        
        # Call JavaScript function directly
        result1 = engine.add(5, 9)
        result2 = engine.add(1, 20)
        
        print(f"Addition 5 + 9 = {result1}")   # 14
        print(f"Addition 1 + 20 = {result2}")  # 21
    except Exception as e:
        print(f"Error calling JavaScript: {e}")

    # ============================================================
    # Example 3: Using different JavaScript engines
    # ============================================================
    print("\n--- Different JS Engines Example ---")
    
    engines = ["node", "v8", "quickjs"]
    for engine_name in engines:
        try:
            print(f"\nTesting with {engine_name} engine...")
            engine = js(engine_name, "src/tools/calc.js")
            result = engine.add(10, 5)
            print(f"Result: {result}")  # 15
        except NotImplementedError:
            print(f"{engine_name} engine not yet implemented")
        except Exception as e:
            print(f"Error with {engine_name}: {e}")

    # ============================================================
    # Example 4: Chain multiple operations
    # ============================================================
    print("\n--- Chain Operations Example ---")
    try:
        cpp_lib = cpp("src/tools/calc.dll")
        
        # Perform multiple operations
        a = cpp_lib.add(5, 9)        # 14
        b = cpp_lib.multiply(a, 2)   # 28
        c = cpp_lib.subtract(b, 3)   # 25
        
        print(f"Chain: add(5,9) -> multiply(14,2) -> subtract(28,3) = {c}")
    except Exception as e:
        print(f"Error: {e}")

    print("\n=== Examples Complete ===")

if __name__ == "__main__":
    main()
