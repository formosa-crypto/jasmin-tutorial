-include ../Makefile.conf

# --------------------------------------------------------------------

TEST_SOURCES := \
	main.c \
	random.c \
	test.c

TEST_HEADERS := \
	random.h \
	test.h

SOURCES := $(TEST_SOURCES) $(REF_SOURCES) $(AVX_SOURCES) $(JAZZ_SOURCES)
HEADERS := $(TEST_HEADERS) $(REF_HEADERS) $(AVX_HEADERS) $(JAZZ_HEADERS)

CC := gcc
CFLAGS := -O3 -g -Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wconversion -Wshadow
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

.PHONY:
	clean
	lint
	run
	valgrind
	all

$(OUT): $(SOURCES) $(HEADERS) $(JAZZ_ASM)
	$(CCOMPILE) $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_ASM) -o $(OUT)

$(JAZZ_ASM):
	$(MAKE) -C $(JAZZ_DIR) $(@)

$(JAZZ_ASM_AVX):
	$(MAKE) -C $(JAZZ_DIR) $(@)

all: $(OUT)

lint:
	clang-format -i $(TEST_SOURCES) $(TEST_HEADERS)

run: $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(OUT)
	./$(OUT) $(TESTN)

run_avx: $(SOURCES) $(HEADERS) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) $(TESTN)

valgrind: $(OUT)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(TESTN)

clean:
	-rm -rf *.dSYM
	-rm -rf $(OUT)
	-rm -rf $(JAZZ_ASM) $(JAZZ_ASM_AVX)
