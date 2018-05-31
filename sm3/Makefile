CXX=g++
CXXFLAGS= -O3
TARGET=main

SRC1= sm3.cpp main.cpp
SRC2= sm3.cpp find.cpp

test: $(SRC1)
	$(CXX) $(CXXFLAGS) $(SRC1) -o $@

find: $(SRC2)
	$(CXX) $(CXXFLAGS) $(SRC2) -o $@
clean:
	$(RM) *.o *.d $(TARGET)

.PHONY: all clean
