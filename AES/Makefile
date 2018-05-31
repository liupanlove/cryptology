CXX=g++
CXXFLAGS= -O3 -std=c++11
TARGET=main

SRC= AES.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

clean:
	$(RM) *.o *.d $(TARGET)

.PHONY: all clean
