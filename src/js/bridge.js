const DataType = Object.freeze({
    INT: 'int',
    FLOAT: 'float',
    STRING: 'string',
    BOOL: 'bool',
    ARRAY: 'array',
    OBJECT: 'object',
    NULL: 'null'
});

/*
    wrapper for bridge-compatible values
*/
class BridgeValue {
    constructor(type, value) {
        this.type = type;
        this.value = value;
    }

    toJSON() {
        return {
            type: this.type,
            value: this.value
        };
    }
}

/*
    handles type conversion between JavaScript and other languages
*/
class TypeConverter {
    constructor() {
        this.typeMap = new Map([
            ['number', DataType.FLOAT],
            ['string', DataType.STRING],
            ['boolean', DataType.BOOL],
            ['object', null] // determined by inspection
        ]);
    }

    /*
        convert JavaScript value to bridge-compatible format
    */
    toBridgeValue(value) {
        if (value === null) {
            return new BridgeValue(DataType.NULL, null);
        }

        const valueType = typeof value;

        if (valueType === 'number') {
            const type = Number.isInteger(value) ? DataType.INT : DataType.FLOAT;
            return new BridgeValue(type, value);
        } else if (valueType === 'string') {
            return new BridgeValue(DataType.STRING, value);
        } else if (valueType === 'boolean') {
            return new BridgeValue(DataType.BOOL, value);
        } else if (Array.isArray(value)) {
            const convertedArray = value.map(item => this.toBridgeValue(item));
            return new BridgeValue(DataType.ARRAY, convertedArray);
        } else if (valueType === 'object') {
            const convertedObject = {};
            for (const key in value) {
                if (value.hasOwnProperty(key)) {
                    convertedObject[key] = this.toBridgeValue(value[key]);
                }
            }
            return new BridgeValue(DataType.OBJECT, convertedObject);
        }

        return new BridgeValue(DataType.NULL, value);
    }

    /*
        convert bridge-compatible value back to JavaScript
    */
    fromBridgeValue(bridgeValue) {
        if (bridgeValue.type === DataType.ARRAY) {
            return bridgeValue.value.map(item => this.fromBridgeValue(item));
        } else if (bridgeValue.type === DataType.OBJECT) {
            const result = {};
            for (const key in bridgeValue.value) {
                result[key] = this.fromBridgeValue(bridgeValue.value[key]);
            }
            return result;
        } else {
            return bridgeValue.value;
        }
    }

    /*
        serialize bridge value to JSON string
    */
    toJSON(bridgeValue) {
        return JSON.stringify(bridgeValue);
    }

    /*
        deserialize JSON string to bridge value
    */
    fromJSON(jsonString) {
        return JSON.parse(jsonString);
    }
}

/*
    registry for callable functions exposed to other languages
*/
class FunctionRegistry {
    constructor() {
        this.functions = new Map();
        this.converter = new TypeConverter();
    }

    /*
        register a function for cross-language calling
    */
    register(name, func) {
        if (this.functions.has(name)) {
            throw new Error(`Function '${name}' is already registered`);
        }
        this.functions.set(name, func);
    }

    /*
        unregister a function
    */
    unregister(name) {
        this.functions.delete(name);
    }

    /*
        check if a function is registered
    */
    hasFunction(name) {
        return this.functions.has(name);
    }

    /*
        call a registered function
    */
    async call(name, args) {
        if (!this.functions.has(name)) {
            throw new Error(`Function '${name}' not found`);
        }

        const func = this.functions.get(name);
        return await func(...args);
    }

    /*
        get list of all registered functions
    */
    getFunctionList() {
        return Array.from(this.functions.keys());
    }
}

/*
    cpp module wrapper for calling C++ shared libraries
*/
class CppModule {
    constructor(libraryPath, converter) {
        this.libraryPath = libraryPath;
        this.converter = converter;
        // TODO: load native C++ module
    }

    /*
        allow direct function calls like cpp_module.add(5, 9)
    */
    [Symbol.get](property) {
        return this.callFunction(property);
    }

    callFunction(functionName) {
        return (...args) => {
            try {
                // TODO: call C++ function via native binding
                throw new Error('C++ interop not yet fully implemented');
            } catch (error) {
                throw new Error(`Failed to call C++ function '${functionName}': ${error.message}`);
            }
        };
    }
}

/*
    python module wrapper for calling Python functions
*/
class PythonModule {
    constructor(modulePath, converter) {
        this.modulePath = modulePath;
        this.converter = converter;
        // TODO: Load Python module
    }

    /*
        call a Python function
    */
    async call(functionName, ...args) {
        try {
            // TODO: call Python function via subprocess or similar
            throw new Error('Python interop not yet fully implemented');
        } catch (error) {
            throw new Error(`Failed to call Python function '${functionName}': ${error.message}`);
        }
    }

    /*
        allow direct function calls via proxy
    */
    get(target, property) {
        if (typeof this[property] === 'function') {
            return this[property];
        }
        return (...args) => this.call(property, ...args);
    }
}

/*
    main bridge interface for JavaScript integration
*/
class Bridge {
    constructor() {
        this.converter = new TypeConverter();
        this.registry = new FunctionRegistry();
    }

    /*
        register a JavaScript function for cross-language calls
    */
    registerFunction(name, func) {
        this.registry.register(name, func);
    }

    /*
        Load C++ shared library (.dll on Windows, .so on Linux)
    */
    cpp(libraryPath) {
        return new CppModule(libraryPath, this.converter);
    }

    /*
        Initialize Python bridge and load module
    */
    python(modulePath) {
        return new PythonModule(modulePath, this.converter);
    }

    /*
        get the function registry
    */
    getRegistry() {
        return this.registry;
    }

    /*
        get the type converter
    */
    getConverter() {
        return this.converter;
    }
}

// singleton instance
let bridgeInstance = null;

/*
    get or create the global bridge instance
*/
function getBridge() {
    if (!bridgeInstance) {
        bridgeInstance = new Bridge();
    }
    return bridgeInstance;
}

// export for Node.js
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        Bridge,
        CppModule,
        PythonModule,
        BridgeValue,
        TypeConverter,
        FunctionRegistry,
        DataType,
        getBridge
    };
}
