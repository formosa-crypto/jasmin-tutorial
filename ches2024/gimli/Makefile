-include ./Makefile.conf

# --------------------------------------------------------------------

default: run

.PHONY:
	clean
	test
	check

run:
	$(MAKE) -C $(TEST_DIR) run

run-ref:
	$(MAKE) -C $(TEST_DIR) run-ref

run-avx:
	$(MAKE) -C $(TEST_DIR) run-avx

check:
	$(MAKE) -C $(PROOF_DIR) check

jazz:
	$(MAKE) -C $(JAZZ_DIR) all

clean:
	@$(MAKE) -C $(JAZZ_DIR) clean
	@$(MAKE) -C $(PROOF_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean

