# -*- Makefile -*-

ECCONF = tests.config
ECARGS ?=
CHECKS ?= jasmin

.PHONY: check clean
.DEFAULT_GOAL = check

check:
	easycrypt runtest $(ECARGS) $(ECCONF) $(CHECKS)

# Nothing to clean (no generated files)
clean:
