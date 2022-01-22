#include "json_value.hpp"

using cls07::Json::JsonValue;

JsonValue::JsonValue()                     : value(nullptr) {}
JsonValue::JsonValue(bool b)               : value(b) {}
JsonValue::JsonValue(int v)                : value(v) {}
JsonValue::JsonValue(char c)               : value(std::string(1, c)) {}
JsonValue::JsonValue(const char* s)        : value(s) {}
JsonValue::JsonValue(const JsonValue& x) = default;

bool JsonValue::IsInt() {
    return std::get_if<int>(&value) != nullptr;
}

bool JsonValue::IsBool() {
    return std::get_if<bool>(&value) != nullptr;
}

bool JsonValue::IsString() {
    return std::get_if<std::string>(&value) != nullptr;
}

bool JsonValue::IsNull() {
    return std::get_if<std::nullptr_t>(&value) != nullptr;
}

bool JsonValue::IsArray() {
    return std::get_if<std::vector<JsonValue>>(&value) != nullptr;
}

int& JsonValue::GetInt() {
    if (!IsInt()) {
        value = 0;
    }
    return std::get<int>(value);
}

bool& JsonValue::GetBool() {
    if (!IsBool()) {
        value = false;
    }
    return std::get<bool>(value);
}

std::string& JsonValue::GetString() {
    if (!IsString()) {
        value = "";
    }
    return std::get<std::string>(value);
}

std::vector<JsonValue>& JsonValue::GetArray() {
    if (!IsArray()) {
        value = std::vector<JsonValue>();
    }
    return std::get<std::vector<JsonValue>>(value);
}

std::nullptr_t& JsonValue::GetNull() {
    if (!IsNull()) {
        value = nullptr;
    }
    return std::get<std::nullptr_t>(value);
}

void JsonValue::Append(const JsonValue& val) {
    GetArray().push_back(val);
}

JsonValue& JsonValue::operator[](std::size_t i) {
    return GetArray()[i];
}
