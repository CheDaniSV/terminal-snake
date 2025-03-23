CC=g++
BINARY=snake

compile: $(BINARY)

$(BINARY):
	$(CC) $@.cpp -o $@

clean:
	rm $(BINARY)

.PHONY: compile clean