-include ./Makefile.conf

# --------------------------------------------------------------------

default: run

.PHONY:
	clean
	test
	check
	format
	valgrind

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

format:
	$(MAKE) -C $(TEST_DIR) format

valgrind:
	$(MAKE) -C $(TEST_DIR) valgrind

clean:
	@$(MAKE) -C $(JAZZ_DIR) clean
	@$(MAKE) -C $(PROOF_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean

