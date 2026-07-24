# LCS Gene Sequence Similarity – Makefile
# C++17, clean, zero-warning build

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
LDFLAGS  :=

# Targets
SIM := sim
LCS := lcs

SIM_SRCS := sim.cpp itemLoader.cpp
LCS_SRCS := lcs.cpp

SIM_OBJS := $(SIM_SRCS:.cpp=.o)
LCS_OBJS := $(LCS_SRCS:.cpp=.o)

.PHONY: all clean run-sim run-lcs help

all: $(SIM) $(LCS)

$(SIM): $(SIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LCS): $(LCS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Convenience targets
run-sim: $(SIM)
	./$(SIM) seqs.txt

run-lcs: $(LCS)
	./$(LCS) AGCTCGAGCTCGACTCGAGCT AGCTCGAGCGA

clean:
	rm -f $(SIM_OBJS) $(LCS_OBJS) $(SIM) $(LCS)

help:
	@echo "Targets:"
	@echo "  make          - build both executables (sim + lcs)"
	@echo "  make run-sim  - build & run similarity analysis on seqs.txt"
	@echo "  make run-lcs  - build & run a quick LCS demo"
	@echo "  make clean    - remove object files and binaries"