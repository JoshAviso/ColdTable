#include "JsonParser.h"

ColdTable::JsonValue ColdTable::JsonParser::ParseValue(const std::string& s, size_t& i)
{
    SkipWhitespace(s, i);

    if (s[i] == '{') return ParseObject(s, i);
    else if (s[i] == '[') return ParseArray(s, i); 
    else if (s[i] == '"') return JsonValue(ParseString(s, i));
    else if (s[i] == '-' || isdigit(s[i])) return JsonValue(ParseNumber(s, i));
    else if (s.compare(i, 4, "true") == 0) {
        i += 4; return JsonValue(true);
    }
    else if (s.compare(i, 5, "false") == 0) {
        i += 5; return JsonValue(false);
    }
    else throw std::runtime_error("Unsupported JSON value");
}

void ColdTable::JsonParser::SkipWhitespace(const std::string& s, size_t& i)
{while (i < s.size() && isspace(s[i])) i++;}

std::string ColdTable::JsonParser::ParseString(const std::string& s, size_t& i)
{
    if (s[i] != '"') throw std::runtime_error("Expected string");
    i++; // skip initial quote

    std::string result;
    while (i < s.size()) {
        char c = s[i++];
        if (c == '"') break;
        if (c == '\\') { // escape sequences
            if (i >= s.size()) throw std::runtime_error("Invalid escape");
            char esc = s[i++];
            switch (esc) {
            case '"': result.push_back('"'); break;
            case '\\': result.push_back('\\'); break;
            case '/': result.push_back('/'); break;
            case 'b': result.push_back('\b'); break;
            case 'f': result.push_back('\f'); break;
            case 'n': result.push_back('\n'); break;
            case 'r': result.push_back('\r'); break;
            case 't': result.push_back('\t'); break;
            default: throw std::runtime_error("Invalid escape char");
            }
        }
        else {
            result.push_back(c);
        }
    }
    return result;
}

double ColdTable::JsonParser::ParseNumber(const std::string& s, size_t& i)
{
    size_t start = i;
    if (s[i] == '-') i++;
    while (i < s.size() && isdigit(s[i])) i++;
    if (i < s.size() && s[i] == '.') {
        i++;
        while (i < s.size() && isdigit(s[i])) i++;
    }
    std::string numStr = s.substr(start, i - start);
    return std::stod(numStr);
}

bool ColdTable::JsonParser::ParseBool(const std::string& s, size_t& i)
{
    if (s.substr(i, 4) == "true") {
        i += 4;
        return true;
    }
    else if (s.substr(i, 5) == "false") {
        i += 5;
        return false;
    }
    throw std::runtime_error("Expected boolean value");
}

ColdTable::JsonValue ColdTable::JsonParser::ParseArray(const std::string& s, size_t& i)
{
    if (s[i] != '[') throw std::runtime_error("Expected '[' to start array");
    i++;  // Skip '['
    SkipWhitespace(s, i);

    std::vector<JsonValue> values;

    if (s[i] == ']') {  // empty array
        i++;
        return JsonValue(values);
    }

    while (true) {
        SkipWhitespace(s, i);
        JsonValue v = ParseValue(s, i);
        values.push_back(v);
        SkipWhitespace(s, i);

        if (s[i] == ',') {
            i++;
            continue;
        }
        else if (s[i] == ']') {
            i++;
            break;
        }
        else {
            throw std::runtime_error("Expected ',' or ']' in array");
        }
    }

    return JsonValue(values);
}

ColdTable::JsonValue ColdTable::JsonParser::ParseObject(const std::string& s, size_t& i)
{
    if (s[i] != '{') throw std::runtime_error("Expected object");
    i++;
    SkipWhitespace(s, i);
    JsonValue objVal;
    objVal.type = JsonValue::OBJECT;

    if (s[i] == '}') { i++; return objVal; }

    while (true) {
        SkipWhitespace(s, i);
        std::string key = ParseString(s, i);
        SkipWhitespace(s, i);
        if (s[i] != ':') throw std::runtime_error("Expected ':'");
        i++;
        SkipWhitespace(s, i);
        JsonValue value = ParseValue(s, i);
        objVal.obj[key] = value;
        SkipWhitespace(s, i);

        if (s[i] == ',') { i++; continue; }
        else if (s[i] == '}') { i++; break; }
        else throw std::runtime_error("Expected ',' or '}'");
    }
    return objVal;
}

std::string ColdTable::JsonParser::Serialize(const JsonValue& val, int indent)
{
    std::string ind(indent, ' ');
    switch (val.type) {
    case JsonValue::STRING:
    {
        std::string escaped = "\"";
        for (char c : val.str) {
            switch (c) {
            case '\"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default: escaped += c;
            }
        }
        escaped += "\"";
        return escaped;
    }
    case JsonValue::NUMBER:
        return std::to_string(val.num);
    case JsonValue::OBJECT:
    {
        std::string res = "{\n";
        bool first = true;
        for (const auto& kv : val.obj) {
            if (!first) res += ",\n";
            res += std::string(indent + 2, ' ') + "\"" + kv.first + "\": " + Serialize(kv.second, indent + 2);
            first = false;
        }
        res += "\n" + ind + "}";
        return res;
    }
    case JsonValue::BOOLEAN:
        return val.b ? "true" : "false";
    case JsonValue::ARRAY:
    {
        std::string res = "[\n";
        bool first = true;
        for (const auto& elem : val.arr) {
            if (!first) res += ",\n";
            res += std::string(indent + 2, ' ') + Serialize(elem, indent + 2);
            first = false;
        }
        res += "\n" + ind + "]";
        return res;
    }
    default:
        return "";
    }
}
