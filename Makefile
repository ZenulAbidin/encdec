CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2
LDFLAGS=-lfmt

all: encrypt decrypt

%.o: %.cpp
	${CXX} -c $^ ${CXXFLAGS}

encrypt: encrypt.o util.o AES.o sha256.o
	${CXX} $^ -o $@ ${LDFLAGS}

decrypt: decrypt.o util.o AES.o sha256.o
	${CXX} $^ -o $@ ${LDFLAGS}

clean:
	rm -f *.o encrypt decrypt util

