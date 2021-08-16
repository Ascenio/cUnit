MAIN=example.c
DEBUG=example.m
OUT=example
ARGS=-Wall -Wextra

all: $(MAIN)
	gcc $(MAIN) $(ARGS) -rdynamic -ldl -o $(OUT)

debug: $(MAIN)
	gcc $(MAIN) $(ARGS) -E -dD -o $(DEBUG)

clean:
	rm -f $(OUT) $(DEBUG)
