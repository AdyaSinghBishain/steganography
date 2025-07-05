#include "bmp.hpp"
#include "steg.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

void print_usage(const char *prog) {
    std::cerr << "Usage:\n"
              << "  " << prog << " encode <in.bmp> <out.bmp> <message.txt>\n"
              << "  " << prog << " decode <in.bmp> <out.txt>\n";
}

std::vector<uint8_t> read_file(const std::string &path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file: " + path);
    return {std::istreambuf_iterator<char>(in),
            std::istreambuf_iterator<char>()};
}

void write_file(const std::string &path,
                const std::vector<uint8_t> &data) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write file: " + path);
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            print_usage(argv[0]);
            return 1;
        }
        std::string cmd = argv[1];
        if (cmd == "encode") {
            if (argc != 5) { print_usage(argv[0]); return 1; }
            BMPImage bmp;
            bmp.load(argv[2]);
            auto msg = read_file(argv[4]);
            Steganography::encode(bmp, msg);
            bmp.save(argv[3]);
            std::cout << "Message hidden successfully in " << argv[3] << "\n";
        }
        else if (cmd == "decode") {
            if (argc != 4) { print_usage(argv[0]); return 1; }
            BMPImage bmp;
            bmp.load(argv[2]);
            auto msg = Steganography::decode(bmp);
            write_file(argv[3], msg);
            std::cout << "Message extracted to " << argv[3] << "\n";
        }
        else {
            print_usage(argv[0]);
            return 1;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
