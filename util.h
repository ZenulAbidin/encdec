#ifndef UTIL_H
#define UTIL_H

std::string createSalt(size_t length);
size_t saltLength(const std::string& data);
std::string getCleanInput(bool pad16=false, bool sentinel=true);
std::string string_to_hex(const std::string& input);
int hex_value(unsigned char hex_digit);
std::string hex_to_string(const std::string& input);

#endif /* UTIL_H */
