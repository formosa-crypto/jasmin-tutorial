-include ../Makefile.conf

# --------------------------------------------------------------------
JASMINEC ?= jasmin2ec
EXT_DIR = $(PROOF_DIR)/extraction
ECCONF = ec.config
CHECKS ?= gimli
ECARGS ?=

.PHONY: check checkec clean
.DEFAULT_GOAL = check

check: gimli_x86.ec gimli_x86_ct.ec gimli_avx.ec gimli_avx_ct.ec checkec

gimli_x86.ec: $(EXT_DIR) $(JAZZ_MAIN)
	cd $(EXT_DIR) && $(JASMINEC) --arch x86-64 -f jazz_gimli -o $@ $(JAZZ_MAIN)

gimli_x86_ct.ec: $(EXT_DIR) $(JAZZ_MAIN)
	cd $(EXT_DIR) && $(JASMINEC) --arch x86-64 -f jazz_gimli -m CT -o $@ $(JAZZ_MAIN)

gimli_avx.ec: $(EXT_DIR) $(JAZZ_MAIN_AVX)
	cd $(EXT_DIR) && $(JASMINEC) --arch x86-64 $(JAZZ_MAIN_AVX) -f jazz_gimliv -o $@

gimli_avx_ct.ec: $(EXT_DIR) $(JAZZ_MAIN_AVX)
	cd $(EXT_DIR) && $(JASMINEC) --arch x86-64 $(JAZZ_MAIN_AVX) -f jazz_gimliv -m CT -o $@

$(EXT_DIR):
	@mkdir $@

checkec:
	easycrypt runtest $(ECCONF) $(CHECKS)

clean:
	-rm -rf $(EXT_DIR)
