#pragma once

#include <variant>
#include <string>
#include <vector>

namespace cls07::Json {
    struct JsonValue {
        typedef std::string            StringType;
        typedef std::vector<JsonValue> ListType;

        JsonValue();
        JsonValue(bool);
        JsonValue(int);
        JsonValue(char);
        JsonValue(const char*);
        JsonValue(const JsonValue&);

        bool IsInt();
        bool IsBool();
        bool IsString();
        bool IsNull();
        bool IsArray();

        int& GetInt();
        bool& GetBool();
        std::string& GetString();
        std::vector<JsonValue>& GetArray();
        std::nullptr_t& GetNull();

        void Append(const JsonValue&);

        JsonValue& operator[](std::size_t);

    private:
        std::variant<bool, std::nullptr_t, int, std::string, std::vector<JsonValue>> value;
    };
}