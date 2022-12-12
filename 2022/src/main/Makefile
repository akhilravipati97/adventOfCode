CC  = g++
CXX = g++

CFLAGS   = -g -Wall
CXXFLAGS = -g -Wall -std=c++17 -I D://Projects/adventOfCode/helpers

LDLIBS = -lstdc++fs

.PHONY: clean build setup

setup:
	@if [[ -z "$(day)" ]]; then\
		echo "Need env day, ex: day=1, day=2 etc.";\
	else\
		cp ../../../helpers/template.cpp day$(day).cpp ;\
		sed -i "s/<DAY>/$(day)/g" day$(day).cpp ;\
		touch ../../input/day$(day).txt ;\
	fi

build:
	@if [[ -z "$(day)" ]]; then\
		echo "Need env day, ex: day=1, day=2 etc.";\
	else\
		$(CXX) -o day$(day).exe day$(day).cpp $(CXXFLAGS) ;\
	fi

clean:
	rm -f *.exe


