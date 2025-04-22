CC=g++
BINARY=snake
INCLUDE_FOLDER=./include
SRC_FOLDER=./src
CPPFILES=$(wildcard $(SRC_FOLDER)/*.cpp)

compile: $(BINARY)

$(BINARY):
	$(CC) $(CPPFILES) -I $(INCLUDE_FOLDER) -static -O2 -o $(BINARY) 

# This target used specifically for Building Windows x86_64 Binaries on Linux with x86_64-w64-mingw32-g++
windows:
	x86_64-w64-mingw32-g++ $(CPPFILES) -I $(INCLUDE_FOLDER) -static -O2 -o $(BINARY).exe

clean:
	rm $(BINARY)

.PHONY: compile clean linux