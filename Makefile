CC=gcc
Cflags=-Wall -Wextra -pedantic -std=c99 -g

TEST_DIR=tests
TEST_SRC=$(wildcard $(TEST_DIR)/*.c)

TESTS=$(TEST_SRC:.c=)

all: $(TESTS)

$(TESTS): %: %.c
	$(CC) $(Cflags) -o $@ $<
	./$@
	@if [ $$? -eq 0 ]; then \
		echo "Test $@ passed"; \
	else \
		echo "Test $@ failed"; \
	fi

clean:
	rm -f $(TESTS)
