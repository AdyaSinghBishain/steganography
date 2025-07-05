# BMP LSB Steganography Tool

A minimal C++ application to hide and extract secret messages inside 24‑bit BMP files using least significant bit (LSB) steganography.  
Includes message length and a simple checksum for integrity.

## 📁 Project Layout

- `data/sample.bmp` — input image (24-bit BMP)
- `data/secret.txt` — text to hide
- `data/encoded.bmp` — output after encoding
- `data/recovered.txt` — output after decoding
- `src/` — all implementation files
- `Makefile` — to compile and test
- `README.md` — project overview

## 🚀 Build Instructions

```bash
mkdir build && cd build
make
