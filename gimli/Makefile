-include ./Makefile.conf

# --------------------------------------------------------------------

default: test

.PHONY:
	clean
	test
	check

run:
	$(MAKE) -C $(TEST_DIR) run

check:
	$(MAKE) -C $(PROOF_DIR) check

clean:
	@$(MAKE) -C $(JAZZ_DIR) clean
	@$(MAKE) -C $(PROOF_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean

