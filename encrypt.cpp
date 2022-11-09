#include "AES.h"
#include "sha256.h"

#include <string>
#include <vector>
#include <iostream>

#include "util.h"

int main() {
    std::cout << "Enter data here, and you will get AES256-encrypted output as a hex string." << std::endl;
    std::cout << "Enter data to encrypt: ";
    std::string raw_data = getCleanInput(true);

    SHA256 sha256;
    std::cout << "Enter the password to encrypt the data: ";
    std::string key = sha256(getCleanInput(true));

    AES aes(AESKeyLength::AES_256);
    const unsigned char iv[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    };
    std::string result(reinterpret_cast<char* >(aes.EncryptCBC(
        reinterpret_cast<const unsigned char*>(raw_data.c_str()), raw_data.length(),
        reinterpret_cast<const unsigned char*>(key.c_str()), iv)), raw_data.length());

    std::cout << "Encrypted output:" << std::endl;
    std::cout << string_to_hex(result) << std::endl;
    return 0;
}
