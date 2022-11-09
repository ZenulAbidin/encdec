
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>

#include "util.h"

std::string createSalt(size_t length) {
    std::string sentinel = "SALT";
    sentinel += fmt::format("{:x}", length);
    sentinel += "_";
    return sentinel;
}

size_t saltLength(const std::string& data) {
    if (data.substr(0,4) != "SALT") {
        throw std::invalid_argument("Sentinel must begin with \"SALT\"");
    }

    auto i = data.find("_");
    if (i == std::string::npos) {
        throw std::invalid_argument("Sentinel is missing an underscore");
    }
    
    std::string len_str = data.substr(4, i-1);
    std::stringstream ss;
    ss << std::hex << len_str;
    size_t length;
    ss >> length;
    return length;
}


std::string getCleanInput(bool pad16, bool sentinel) {
    std::string raw_data;
    std::string input;
    std::getline(std::cin, input);
    if (sentinel)
        raw_data = createSalt(input.length());
    raw_data += input;
    // I don't trust that there are no CRLFs at the end so get rid of them.
    raw_data.erase(std::remove(raw_data.begin(), raw_data.end(), '\r'), raw_data.cend());
    raw_data.erase(std::remove(raw_data.begin(), raw_data.end(), '\n'), raw_data.cend());
    if (pad16) {
        while (raw_data.length() % 16 != 0) {
            raw_data += '\0';
        }
    }
    return raw_data;
}

std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

int hex_value(unsigned char hex_digit)
{
    static const signed char hex_values[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    int value = hex_values[hex_digit];
    if (value == -1) throw std::invalid_argument("invalid hex digit");
    return value;
}

std::string hex_to_string(const std::string& input)
{
    const auto len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (auto it = input.begin(); it != input.end(); )
    {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        output.push_back(hi << 4 | lo);
    }
    return output;
}
