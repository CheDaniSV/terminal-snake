CC=g++
BINARY=main

compile: $(BINARY)

$(BINARY):
	$(CC) $@.cpp -o $@

clean:
	rm $(BINARY)

.PHONY: compile clean