#ifndef STEG_HPP
#define STEG_HPP

#include "bmp.hpp"
#include <string>
#include <vector>
#include <cstdint>

class Steganography {
public:
    static void encode(BMPImage &bmp,
                       const std::vector<uint8_t> &msgBytes);
    static std::vector<uint8_t> decode(const BMPImage &bmp);

private:
    static uint32_t checksum(const std::vector<uint8_t> &data);
    static void write_bits(std::vector<uint8_t> &container,
                           uint32_t value, int bits, size_t &offset);
    static uint32_t read_bits(const std::vector<uint8_t> &container,
                              int bits, size_t &offset);
};

#endif // STEG_HPP
