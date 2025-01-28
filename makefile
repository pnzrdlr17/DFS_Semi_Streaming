# Compiler and flags
# CC = g++ -std=c++0x  #g++ -std=c++11
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -g -w
LDFLAGS = -Wall -O3 -g -w

# Paths
SRC_DIR = src
LIB_DIR = lib
BIN_DIR = bin
ALG_DIR = $(LIB_DIR)/algorithms
KPATH_DIR = $(ALG_DIR)/kPath
KLEV_DIR = $(ALG_DIR)/kLev
CDFS_DIR = $(ALG_DIR)/classicalDFS

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(LIB_DIR)/*.cpp) $(wildcard $(ALG_DIR)/*.cpp) $(wildcard $(KPATH_DIR)/*.cpp) $(wildcard $(KLEV_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/src/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
            $(patsubst $(LIB_DIR)/%.cpp, $(BIN_DIR)/lib/%.o, $(wildcard $(LIB_DIR)/*.cpp)) \
            $(patsubst $(ALG_DIR)/%.cpp, $(BIN_DIR)/lib/algorithms/%.o, $(wildcard $(ALG_DIR)/*.cpp)) \
            $(patsubst $(KPATH_DIR)/%.cpp, $(BIN_DIR)/lib/algorithms/kPath/%.o, $(wildcard $(KPATH_DIR)/*.cpp)) \
            $(patsubst $(KLEV_DIR)/%.cpp, $(BIN_DIR)/lib/algorithms/kLev/%.o, $(wildcard $(KLEV_DIR)/*.cpp)) \
			$(patsubst $(CDFS_DIR)/%.cpp, $(BIN_DIR)/lib/algorithms/classicalDFS/%.o, $(wildcard $(CDFS_DIR)/*.cpp))

# Targets
all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BIN_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/lib/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/lib/algorithms/%.o: $(ALG_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/lib/algorithms/kPath/%.o: $(KPATH_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/lib/algorithms/kLev/%.o: $(KLEV_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN_DIR)/src $(BIN_DIR)/lib $(BIN_DIR)/main

.PHONY: all clean