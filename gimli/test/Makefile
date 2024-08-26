REF_SOURCES ::= ../c-ref/gimli.c
REF_HEADERS ::= ../c-ref/gimli.h
JAZZ_MAIN ::= ../jasmin/jazz_gimli.jazz
JAZZ_SOURCES ::= ../jasmin/gimli.jazz $(JAZZ_MAIN)
JAZZ_HEADERS ::= ../jasmin/jazz_gimli.h
JAZZ_ASM ::= jazz_gimli.s

TEST_SOURCES ::= \
	main.c \
	random.c \
	test.c

TEST_HEADERS ::= \
	random.h \
	test.h

CC ::= gcc
CFLAGS ::= -Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wconversion \
	-Wshadow -Warith-conversion -g -O0

OUT ::= out.o

TESTN ?= 0

JASMINC ?= jasminc
JASMIN_FLAGS += -g

VALGRIND ?= valgrind
VALGRIND_FLAGS += \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose

.PHONY:
	clean
	lint
	run
	valgrind

$(OUT): \
	$(TEST_SOURCES) \
	$(TEST_HEADERS) \
	$(REF_SOURCES) \
	$(REF_HEARERS) \
	$(JAZZ_SOURCES) \
	$(JAZZ_HEADERS) \
	$(JAZZ_ASM)
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_ASM) -o $(OUT)

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN) -o $(JAZZ_ASM)

clean:
	rm $(OUT) $(JAZZ_ASM)

all: $(OUT)

lint:
	clang-format -i $(TEST_SOURCES) $(TEST_HEADERS)

run: $(OUT)
	./$(OUT) $(TESTN)

valgrind:
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(TESTN)
