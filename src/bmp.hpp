#ifndef BMP_HPP
#define BMP_HPP

#include <vector>
#include <cstdint>
#include <fstream>
#include <stdexcept>

struct BMPImage {
    static constexpr std::size_t HEADER_SIZE = 54;
    std::vector<uint8_t> header;
    std::vector<uint8_t> data;

    void load(const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in) throw std::runtime_error("Cannot open BMP file: " + path);
        header.resize(HEADER_SIZE);
        in.read(reinterpret_cast<char*>(header.data()), HEADER_SIZE);
        if (in.gcount() != HEADER_SIZE)
            throw std::runtime_error("Invalid BMP header");

        uint32_t fileSize = *reinterpret_cast<uint32_t*>(&header[2]);
        std::size_t dataSize = fileSize - HEADER_SIZE;
        data.resize(dataSize);
        in.read(reinterpret_cast<char*>(data.data()), dataSize);
        if (static_cast<std::size_t>(in.gcount()) != dataSize)
            throw std::runtime_error("Unexpected EOF reading BMP data");
    }

    void save(const std::string &path) const {
        std::ofstream out(path, std::ios::binary);
        if (!out) throw std::runtime_error("Cannot write BMP file: " + path);
        out.write(reinterpret_cast<const char*>(header.data()), header.size());
        out.write(reinterpret_cast<const char*>(data.data()), data.size());
    }

    std::size_t capacity_bits() const {
        return data.size();
    }
};

#endif // BMP_HPP
