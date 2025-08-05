#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace ColdTable
{
	struct JsonValue;
	using JsonObject = std::map<std::string, JsonValue>;
    struct JsonValue {
        enum Type { OBJECT, STRING, NUMBER, BOOLEAN, ARRAY } type;

        JsonObject obj{};
        std::vector<JsonValue> arr{};
        std::string str{};
        double num{};
        bool b{};

        JsonValue() : type(OBJECT) {}        // default to object
        JsonValue(const std::string& s) : type(STRING), str(s) {}
        JsonValue(double n) : type(NUMBER), num(n) {}
		JsonValue(bool b) : type(BOOLEAN), b(b) {}
        JsonValue(const std::vector<JsonValue>& v) : type(ARRAY), arr(v) {}

        // Access operator for object keys
        JsonValue& operator[](const std::string& key) {
            if (type != OBJECT) throw std::runtime_error("Not an object");
            return obj[key];
        }

        const JsonValue& operator[](const std::string& key) const {
            if (type != OBJECT) throw std::runtime_error("Not an object");
            auto it = obj.find(key);
            if (it == obj.end()) throw std::runtime_error("Key not found");
            return it->second;
        }

        JsonValue& operator[](size_t index) {
            if (type != ARRAY) throw std::runtime_error("Not an array");
            if (index >= arr.size()) throw std::out_of_range("Index out of range");
            return arr[index];
        }
        const JsonValue& operator[](size_t index) const {
            if (type != ARRAY) throw std::runtime_error("Not an array");
            if (index >= arr.size()) throw std::out_of_range("Index out of range");
            return arr[index];
        }

		std::string AsString() const {
			if (type != STRING) throw std::runtime_error("Not a string");
			return str;
		}

		double AsNumber() const {
			if (type != NUMBER) throw std::runtime_error("Not a number");
			return num;
		}

		bool AsBool() const {
			if (type != BOOLEAN) throw std::runtime_error("Not a boolean");
			return b;
		}
    };
	class JsonParser
	{
	public:
		static JsonValue ParseObject(const std::string& s, size_t& i);
        static std::string Serialize(const JsonValue& val, int indent = 0);
	private:
        static JsonValue ParseValue(const std::string& s, size_t& i);
        static void SkipWhitespace(const std::string& s, size_t& i);
        static std::string ParseString(const std::string& s, size_t& i);
        static double ParseNumber(const std::string& s, size_t& i);
        static bool ParseBool(const std::string& s, size_t& i);
		static JsonValue ParseArray(const std::string& s, size_t& i);
	};
}

