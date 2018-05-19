CXX=g++
CXXFLAGS= -O3
TARGET=main

SRC= sm3.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

clean:
	$(RM) *.o *.d $(TARGET)

.PHONY: all clean
