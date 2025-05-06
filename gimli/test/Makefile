-include ../Makefile.conf

# --------------------------------------------------------------------

TEST_SOURCES := \
	main.c \
	random.c \
	test.c

TEST_HEADERS := \
	random.h \
	test.h

REF_SRC := $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_SOURCES)
REF_HDR := $(TEST_HEADERS) $(REF_HEADERS) $(JAZZ_HEADERS)

SOURCES := $(REF_SRC) $(AVX_SOURCES) $(JAZZ_SOURCES_AVX)
HEADERS := $(REF_HDR) $(AVX_HEADERS) $(JAZZ_HEADERS_AVX)

CC := gcc
CFLAGS := -O3 -g -Wall -Wextra -Werror -Wpedantic -Wunreachable-code \
	-Wshadow -march=native
CAVXFLAG := -DAVX_SUPPORT
CINCLUDE := -I $(REF_DIR) -I $(AVX_DIR) -I $(JAZZ_REF) -I $(JAZZ_AVX)
CCOMPILE := $(CC) $(CINCLUDE) $(CFLAGS)

OUT := out.o
OUT_REF := out_ref.o

TESTN ?= 0

VALGRIND ?= valgrind
VALGRIND_FLAGS += \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	-q

# --------------------------------------------------------------------

.default: run-ref

.PHONY:
	clean
	format
	run
	valgrind
	all

$(OUT_REF): $(REF_SRC) $(REF_HDR) $(JAZZ_ASM)
	$(CCOMPILE) $(TEST_SOURCES) $(REF_SOURCES) $(JAZZ_ASM) -o $(OUT_REF)

$(OUT): $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(JAZZ_ASM_AVX)
	$(CCOMPILE) $(CAVXFLAG) $(TEST_SOURCES) $(REF_SOURCES) $(AVX_SOURCES) $(JAZZ_ASM) \
	$(JAZZ_ASM_AVX) -o $(OUT)

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(MAKE) -C $(JAZZ_DIR) ref

$(JAZZ_ASM_AVX): $(JAZZ_SOURCES_AVX)
	$(MAKE) -C $(JAZZ_DIR) avx

all: $(OUT)

format:
	clang-format -i $(TEST_SOURCES) $(TEST_HEADERS)

run: $(SOURCES) $(HEADERS) $(JAZZ_ASM) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) 0

run-ref: $(OUT_REF)
	./$(OUT_REF) 1

run-avx: $(SOURCES) $(HEADERS) $(JAZZ_ASM_AVX) $(OUT)
	./$(OUT) 2

valgrind: $(OUT)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(OUT) $(TESTN)

clean:
	-rm -rf *.dSYM
	-rm -rf $(OUT)
	-rm -rf $(OUT_REF)
	-rm -rf $(JAZZ_ASM)
	-rm -rf $(JAZZ_ASM_AVX)
