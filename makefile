CC=g++
BINARY=snake
INCLUDE_FOLDER=./include
SRC_FOLDER=./src
CPPFILES=$(wildcard $(SRC_FOLDER)/*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(CPPFILES))
DEPFLAGS=-I$(INCLUDE_FOLDER)# -MP -MD

compile: $(BINARY)
	rm $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CC) $(OBJECTS) -static -O2 -o $(BINARY) -Wno-unused-result

%.o: %.cpp
	$(CC) $(DEPFLAGS) -c $^ -o $@

# This target is used specifically for building Windows x86_64 Binaries on Linux with x86_64-w64-mingw32-g++
windows:
	x86_64-w64-mingw32-g++ $(CPPFILES) -I $(INCLUDE_FOLDER) -static -O2 -o $(BINARY).exe

clean:
	rm $(BINARY) $(BINARY).exe 

.PHONY: compile clean windows