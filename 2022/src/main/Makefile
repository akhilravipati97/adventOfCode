CC  = g++
CXX = g++

CFLAGS   = -g -Wall
CXXFLAGS = -g -Wall -std=c++17 -I D://Projects/adventOfCode/helpers

LDLIBS = -lstdc++fs

build:
	@if [[ -z $(day) ]]; then\
		echo "Need env day, ex: day=1, day=2 etc.";\
	fi
	$(CXX) -o day$(day).exe day$(day).cpp $(CXXFLAGS)

.PHONY: clean build
clean:
	rm -f *.exe


