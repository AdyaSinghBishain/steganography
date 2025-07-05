CXX := g++
CXXFLAGS := -std=c++11 -O2 -Wall

SRC := src/main.cpp src/steg.cpp
INCLUDE := src

all: steg

steg: $(SRC)
	$(CXX) $(CXXFLAGS) -Isrc $^ -o steg

.PHONY: example clean

example: steg
	./steg encode data/sample.bmp data/encoded.bmp data/secret.txt
	./steg decode data/encoded.bmp data/recovered.txt

clean:
	rm -f steg data/encoded.bmp data/recovered.txt
