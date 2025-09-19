CC=g++
BINARY=snake
INCLUDE_FOLDER=./include
SRC_FOLDER=./src
BUILD_FOLDER=./build
CPPFILES=$(wildcard $(SRC_FOLDER)/*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(CPPFILES))
DEPFLAGS=-I$(INCLUDE_FOLDER)# -MP -MD

compile: $(BINARY)
	rm $(OBJECTS)

$(BINARY): $(OBJECTS) make_build_folder
	$(CC) $(OBJECTS) -static -O2 -o $(BUILD_FOLDER)/$(BINARY) -Wno-unused-result

%.o: %.cpp
	$(CC) $(DEPFLAGS) -c $^ -o $@

# This target is used specifically for building Windows x86_64 Binaries on Linux with x86_64-w64-mingw32-g++
windows: make_build_folder
	x86_64-w64-mingw32-g++ $(CPPFILES) -I $(INCLUDE_FOLDER) -static -O2 -o $(BUILD_FOLDER)/$(BINARY).exe

# Build for linux using wsl (you need build-essentials for that)
linux:
	wsl -d Debian -- make

make_build_folder:
	mkdir -p $(BUILD_FOLDER)

clean:
	rm -f $(BUILD_FOLDER)/$(BINARY) $(BUILD_FOLDER)/$(BINARY).exe

.PHONY: compile clean windows linux make_build_folder