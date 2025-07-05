#include "steg.hpp"
#include <stdexcept>

uint32_t Steganography::checksum(const std::vector<uint8_t> &data) {
    uint32_t sum = 0;
    for (auto b : data) sum += b;
    return sum;
}

void Steganography::write_bits(std::vector<uint8_t> &container,
                               uint32_t value, int bits, size_t &offset) {
    for (int i = 0; i < bits; ++i) {
        if (offset >= container.size())
            throw std::runtime_error("Not enough capacity in image");
        container[offset] = (container[offset] & 0xFE)
                          | ((value >> i) & 1);
        ++offset;
    }
}

uint32_t Steganography::read_bits(const std::vector<uint8_t> &container,
                                  int bits, size_t &offset) {
    uint32_t value = 0;
    for (int i = 0; i < bits; ++i) {
        if (offset >= container.size())
            throw std::runtime_error("Unexpected end of image data");
        value |= (uint32_t(container[offset] & 1) << i);
        ++offset;
    }
    return value;
}

void Steganography::encode(BMPImage &bmp,
                           const std::vector<uint8_t> &msgBytes) {
    size_t needed = 32 + 32 + msgBytes.size()*8;
    if (bmp.capacity_bits() < needed)
        throw std::runtime_error("Image too small to hold message");

    size_t offset = 0;
    uint32_t len = static_cast<uint32_t>(msgBytes.size());
    write_bits(bmp.data, len, 32, offset);
    uint32_t cs = checksum(msgBytes);
    write_bits(bmp.data, cs, 32, offset);

    for (auto byte : msgBytes)
        write_bits(bmp.data, byte, 8, offset);
}

std::vector<uint8_t> Steganography::decode(const BMPImage &bmp) {
    size_t offset = 0;
    uint32_t len = read_bits(bmp.data, 32, offset);
    uint32_t cs  = read_bits(bmp.data, 32, offset);

    std::vector<uint8_t> msg(len);
    for (uint32_t i = 0; i < len; ++i)
        msg[i] = static_cast<uint8_t>(read_bits(bmp.data, 8, offset));

    if (checksum(msg) != cs)
        throw std::runtime_error("Checksum mismatch! Data corrupted.");

    return msg;
}
