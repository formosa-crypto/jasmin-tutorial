REF_DIR := ../c/ref
REF_SOURCES := $(REF_DIR)/gimli.c
REF_HEADERS := $(REF_DIR)/gimli.h
JAZZ_DIR := ../jasmin/
JAZZ_MAIN := $(JAZZ_DIR)/jazz_gimli.jazz
JAZZ_SOURCES := $(JAZZ_DIR)/gimli.jazz $(JAZZ_MAIN)
JAZZ_HEADERS := $(JAZZ_DIR)/jazz_gimli.h
JAZZ_ASM := jazz_gimli.s

SOURCES := $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_SOURCES)
HEADERS := $(TEST_HEADERS) $(REF_HEADERS) $(JAZZ_HEADERS)

TEST_SOURCES := \
	main.c \
	random.c \
	test.c

TEST_HEADERS := \
	random.h \
	test.h

CC := gcc
CFLAGS := \
	-Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wconversion -Wshadow \
	-Warith-conversion -g -O3
CINCLUDE := -I $(REF_DIR) -I $(JAZZ_DIR)
CCOMPILE := $(CC) $(CINCLUDE) $(CFLAGS)

OUT := out.o

TESTN ?= 0

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
	$(CCOMPILE) $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_ASM) -o $(OUT)

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN) -o $(JAZZ_ASM)

clean:
	rm -f $(OUT) $(JAZZ_ASM)

all: $(OUT)

lint:
	clang-format -i $(TEST_SOURCES) $(TEST_HEADERS)

run: $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(OUT)
	./$(OUT) $(TESTN)

valgrind: $(OUT)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(TESTN)
