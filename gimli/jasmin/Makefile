-include ../Makefile.conf

# --------------------------------------------------------------------

JASMINC ?= jasminc
JASMIN_FLAGS +=

.PHONY: ref avx all clean

.default: all

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN) -o $(JAZZ_ASM)

$(JAZZ_ASM_AVX): $(JAZZ_SOURCES_AVX)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN_AVX) -o $(JAZZ_ASM_AVX)

ref: $(JAZZ_ASM)

avx: $(JAZZ_ASM_AVX)

all: $(JAZZ_ASM) $(JAZZ_ASM_AVX)

clean:
	-rm -rf $(JAZZ_ASM)
	-rm -rf $(JAZZ_ASM_AVX)
