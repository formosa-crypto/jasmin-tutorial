JAZZ_MAIN ::= otp.jazz
JAZZ_SOURCES ::=
JAZZ_ASM ::= otp.s

SOURCES ::= main.c
HEADERS ::=

CC ::= gcc
CFLAGS ::= \
	-Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wconversion -Wshadow \
	-Warith-conversion -g -O3
CINCLUDE ::=
CCOMPILE ::= $(CC) $(CINCLUDE) $(CFLAGS)

OUT ::= out.o

JASMINC ?= jasminc
JASMIN_FLAGS +=

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

$(OUT): $(SOURCES) $(HEADERS) $(JAZZ_ASM)
	$(CCOMPILE) $(SOURCES) $(JAZZ_ASM) -o $(OUT)

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(JASMINC) $(JAZZ_MAIN) -o $(JAZZ_ASM)

clean:
	rm -f $(OUT) $(JAZZ_ASM)

all: $(SOURCES) $(JAZZ_MAIN) $(OUT)

lint:
	clang-format -i $(SOURCES)

valgrind: $(OUT)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(MSG) $(KEY)
