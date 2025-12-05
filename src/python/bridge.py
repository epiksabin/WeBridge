# py bridge

import ctypes
import json
from typing import Any, Callable, Dict, List, Optional, Union
from dataclasses import dataclass
from enum import Enum


class DataType(Enum):
    # supported data convertion
    INT = "int"
    FLOAT = "float"
    STRING = "string"
    BOOL = "bool"
    ARRAY = "array"
    OBJECT = "object"
    NULL = "null"


@dataclass
class BridgeValue:
    type: DataType
    value: Any


class TypeConverter:
    
    def __init__(self):
        self.type_map = {
            int: DataType.INT,
            float: DataType.FLOAT,
            str: DataType.STRING,
            bool: DataType.BOOL,
            list: DataType.ARRAY,
            dict: DataType.OBJECT,
            type(None): DataType.NULL,
        }
    
    def to_bridge_value(self, value: Any) -> BridgeValue:
        value_type = type(value)
        
        if value_type == list:
            converted_items = [self.to_bridge_value(item) for item in value]
            return BridgeValue(DataType.ARRAY, converted_items)
        elif value_type == dict:
            converted_dict = {k: self.to_bridge_value(v) for k, v in value.items()}
            return BridgeValue(DataType.OBJECT, converted_dict)
        else:
            data_type = self.type_map.get(value_type, DataType.NULL)
            return BridgeValue(data_type, value)
    
    def from_bridge_value(self, bridge_value: BridgeValue) -> Any:
        if bridge_value.type == DataType.ARRAY:
            return [self.from_bridge_value(item) for item in bridge_value.value]
        elif bridge_value.type == DataType.OBJECT:
            return {k: self.from_bridge_value(v) for k, v in bridge_value.value.items()}
        else:
            return bridge_value.value
    
    def to_json(self, bridge_value: BridgeValue) -> str:
        return json.dumps({
            "type": bridge_value.type.value,
            "value": self._serialize_value(bridge_value.value)
        })
    
    @staticmethod
    def _serialize_value(value: Any) -> Any:
        if isinstance(value, BridgeValue):
            return {
                "type": value.type.value,
                "value": TypeConverter._serialize_value(value.value)
            }
        elif isinstance(value, list):
            return [TypeConverter._serialize_value(v) for v in value]
        elif isinstance(value, dict):
            return {k: TypeConverter._serialize_value(v) for k, v in value.items()}
        else:
            return value


class FunctionRegistry:
    # registry calling
    
    def __init__(self):
        self.functions: Dict[str, Callable] = {}
        self.converter = TypeConverter()
    
    def register(self, name: str, func: Callable) -> None:
        if name in self.functions:
            raise ValueError(f"Function '{name}' is already registered")
        self.functions[name] = func
    
    def unregister(self, name: str) -> None:
        if name in self.functions:
            del self.functions[name]
    
    def has_function(self, name: str) -> bool:
        return name in self.functions
    
    def call(self, name: str, args: List[Any]) -> Any:
        if name not in self.functions:
            raise RuntimeError(f"Function '{name}' not found")
        
        func = self.functions[name]
        return func(*args)
    
    def get_function_list(self) -> List[str]:
        return list(self.functions.keys())


class Bridge:
    
    def __init__(self):
        self.converter = TypeConverter()
        self.registry = FunctionRegistry()
        self._cpp_bridge = None
        self._js_bridge = None
    
    def register_function(self, name: str, func: Callable) -> None:
        self.registry.register(name, func)
    
    def cpp(self, library_path: str):
        """Load C++ shared library (.dll on Windows, .so on Linux)"""
        return CppModule(library_path, self.converter)
    
    def js(self, engine: str, module_path: str):
        """Initialize JS bridge with Node.js, V8 or quickJS engine"""
        return JsModule(engine, module_path, self.converter)
    
    def get_registry(self) -> FunctionRegistry:
        return self.registry
    
    def get_converter(self) -> TypeConverter:
        return self.converter


class CppModule:
    """Wrapper for C++ shared library"""
    
    def __init__(self, library_path: str, converter: TypeConverter):
        self.library_path = library_path
        self.converter = converter
        try:
            self.lib = ctypes.CDLL(library_path)
        except Exception as e:
            raise RuntimeError(f"Failed to load C++ library: {e}")
    
    def __getattr__(self, name: str):
        """Allow direct function calls like cpp_lib.add(5, 9)"""
        if name in ['library_path', 'converter', 'lib']:
            return object.__getattribute__(self, name)
        
        def cpp_function(*args):
            try:
                func = getattr(self.lib, name)
                # Convert and call
                result = func(*args)
                return result
            except Exception as e:
                raise RuntimeError(f"Failed to call C++ function '{name}': {e}")
        
        return cpp_function


class JsModule:
    """Wrapper for JavaScript module"""
    
    def __init__(self, engine: str, module_path: str, converter: TypeConverter):
        self.engine = engine
        self.module_path = module_path
        self.converter = converter
        # TODO: Initialize JavaScript engine
    
    def __getattr__(self, name: str):
        """Allow direct function calls like engine.add(5, 9)"""
        if name in ['engine', 'module_path', 'converter']:
            return object.__getattribute__(self, name)
        
        def js_function(*args):
            try:
                # TODO: Call JavaScript function via engine
                raise NotImplementedError("JavaScript interop not yet implemented")
            except Exception as e:
                raise RuntimeError(f"Failed to call JavaScript function '{name}': {e}")
        
        return js_function


# singleton instance
_bridge_instance: Optional[Bridge] = None


def get_bridge() -> Bridge:
    global _bridge_instance
    if _bridge_instance is None:
        _bridge_instance = Bridge()
    return _bridge_instance


# Top-level API functions for easier importing
def cpp(library_path: str) -> CppModule:
    """Load C++ shared library (.dll on Windows, .so on Linux)"""
    return get_bridge().cpp(library_path)


def js(engine: str, module_path: str) -> JsModule:
    """Initialize JS bridge with Node.js, V8 or quickJS engine"""
    return get_bridge().js(engine, module_path)
