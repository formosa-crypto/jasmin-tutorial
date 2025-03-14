-include ../Makefile.conf

# --------------------------------------------------------------------

TEST_SOURCES := \
	main.c \
	random.c \
	test.c

TEST_HEADERS := \
	random.h \
	test.h

SOURCES := $(TEST_SOURCES) $(REF_SOURCES) $(AVX_SOURCES) $(JAZZ_SOURCES) \
	$(JAZZ_SOURCES_AVX)
HEADERS := $(TEST_HEADERS) $(REF_HEADERS) $(AVX_HEADERS) $(JAZZ_HEADERS) \
	$(JAZZ_HEADERS_AVX)

CC := gcc
CFLAGS := -O3 -g -Wall -Wextra -Werror -Wpedantic -Wunreachable-code \
	-Wshadow -march=native
CINCLUDE := -I $(REF_DIR) -I $(AVX_DIR) -I $(JAZZ_REF) -I $(JAZZ_AVX)
CCOMPILE := $(CC) $(CINCLUDE) $(CFLAGS)

OUT := out.o

TESTN ?= 0

VALGRIND ?= valgrind
VALGRIND_FLAGS += \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose

# --------------------------------------------------------------------

.default: run-ref

.PHONY:
	clean
	format
	run
	valgrind
	all

$(OUT): $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(JAZZ_ASM_AVX)
	$(CCOMPILE) $(TEST_SOURCES) $(REF_SOURCES) $(AVX_SOURCES) $(JAZZ_ASM) \
	$(JAZZ_ASM_AVX) -o $(OUT)

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(MAKE) -C $(JAZZ_DIR) $(@)

$(JAZZ_ASM_AVX): $(JAZZ_SOURCES_AVX)
	$(MAKE) -C $(JAZZ_DIR) $(@)

all: $(OUT)

format:
	clang-format -i $(TEST_SOURCES) $(TEST_HEADERS)

run: $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) 0 $(TESTN)

run-ref: $(SOURCES) $(HEADERS) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) 1 $(TESTN)

run-avx: $(SOURCES) $(HEADERS) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) 2 $(TESTN)

valgrind: $(OUT)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(TESTN)

clean:
	-rm -rf *.dSYM
	-rm -rf $(OUT)
	-rm -rf $(JAZZ_ASM)
	-rm -rf $(JAZZ_ASM_AVX)
