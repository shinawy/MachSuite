KERN=mul
ALG=elemwise

CXX?=g++
CXXFLAGS?=-O3 -Wall -Wno-unused-label -std=c++11

SRCS=$(KERN).cpp local_support.cpp ../../common/support.cpp
FILES=$(SRCS) $(KERN).h ../../common/support.h

$(KERN): $(FILES) ../../common/harness.cpp
	$(CXX) $(CXXFLAGS) -I../../common -o $(KERN) $(SRCS) ../../common/harness.cpp

run: $(KERN) input.data check.data
	./$(KERN) input.data check.data

generate: $(FILES) generate.cpp
	$(CXX) $(CXXFLAGS) -I../../common -o generate $(SRCS) generate.cpp
	./generate

hls: $(KERN).cpp $(KERN).h
	vitis_hls hls.tcl

clean:
	rm -f $(KERN) generate output.data
