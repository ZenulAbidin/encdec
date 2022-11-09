#include "AES.h"
#include "sha256.h"

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "util.h"

int main() {
    std::cout << "Enter the raw data and the key to decrypt it." << std::endl;
    std::cout << "Enter encrypted data: ";
    std::string enc_data = hex_to_string(getCleanInput(false, false));

    SHA256 sha256;
    std::cout << "Enter the password for decrypting the data: ";
    std::string key = sha256(getCleanInput(true));

    AES aes(AESKeyLength::AES_256);
    const unsigned char iv[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    };
    std::string result(reinterpret_cast<char* >(aes.DecryptCBC(
        reinterpret_cast<const unsigned char*>(enc_data.c_str()), enc_data.length(),
        reinterpret_cast<const unsigned char*>(key.c_str()), iv)));

    if (result.rfind("SALT", 0) == 0) {
        size_t len = saltLength(result);
        size_t prefixlen = result.find("_", 0)+1;
        std::cout << "Decrypted output:" << std::endl;
        std::cout << result.substr(prefixlen, len+prefixlen) << std::endl;
        return 0;
    }
    else {
        std::cout << "Wrong decryption key and/or data, check your input" << std::endl;
        return 1;
    }
}

