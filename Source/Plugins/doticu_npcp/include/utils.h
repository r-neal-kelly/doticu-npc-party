/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp { namespace Utils {

    inline std::vector<char> To_Binary(void* data, size_t bytes)
    {
        static const char* half_bytes[16] = {
            "0000", "0001", "0010", "0011",
            "0100", "0101", "0110", "0111",
            "1000", "1001", "1010", "1011",
            "1100", "1101", "1110", "1111"
        };

        size_t bits = bytes * 8;
        size_t spaces = bytes * 1 - 1;
        size_t null = 1;
        std::vector<char> chars;
        chars.reserve(bits + spaces + null);

        u8* it = static_cast<u8*>(data) + bytes;
        while (it != data) {
            it -= 1;
            u8 byte = *it;
            char* left = const_cast<char*>(half_bytes[(byte & 0xF0) >> 4]);
            char* right = const_cast<char*>(half_bytes[byte & 0x0F]);
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push_back(left[idx]);
            }
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push_back(right[idx]);
            }
            chars.push_back(' ');
        }
        chars.at(chars.size() - 1) = '\0';

        return chars;
    }

}}
