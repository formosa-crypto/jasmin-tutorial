-include ../Makefile.conf

# --------------------------------------------------------------------
JASMINC ?= jasminc
EXT_DIR := $(PROOF_DIR)/extraction
ECCONF := ec.config
CHECKS ?= gimli
ECARGS ?=

.PHONY: clean

check: gimli_x86.ec gimli_x86_ct.ec gimli_avx.ec gimli_avx_ct.ec checkec 

gimli_x86.ec: $(EXT_DIR) $(JAZZ_MAIN)
	cd $(EXT_DIR) && $(JASMINC) -arch x86-64 -ec jazz_gimli -oec $@ $(JAZZ_MAIN) 

gimli_x86_ct.ec: $(EXT_DIR) $(JAZZ_MAIN)
	cd $(EXT_DIR) && $(JASMINC) -arch x86-64 -CT -oec $@ $(JAZZ_MAIN)

gimli_avx.ec: $(EXT_DIR) $(JAZZ_MAIN_AVX)
	cd $(EXT_DIR) && $(JASMINC) -arch x86-64 $(JAZZ_MAIN_AVX) -ec jazz_gimliv -oec $@

gimli_avx_ct.ec: $(EXT_DIR) $(JAZZ_MAIN_AVX)
	cd $(EXT_DIR) && $(JASMINC) -arch x86-64 -CT $(JAZZ_MAIN_AVX) -ec jazz_gimliv -oec $@

$(EXT_DIR):
	@mkdir $@

checkec:
	easycrypt	runtest $(ECCONF) $(CHECKS)

clean:
	-rm -rf $(EXT_DIR)
