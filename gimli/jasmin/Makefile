-include ../Makefile.conf

# --------------------------------------------------------------------

JASMINC ?= jasminc
JASMIN_FLAGS +=

.PHONY: all clean
.DEFAULT_GOAL = all

$(JAZZ_ASM): $(JAZZ_SOURCES)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN) -o $(JAZZ_ASM)

$(JAZZ_ASM_AVX): $(JAZZ_SOURCES_AVX)
	$(JASMINC) $(JASMIN_FLAGS) $(JAZZ_MAIN_AVX) -o $(JAZZ_ASM_AVX)

all: $(JAZZ_ASM) $(JAZZ_ASM_AVX)

clean:
	-rm -r $(JAZZ_ASM)
	-rm -r $(JAZZ_ASM_AVX)
