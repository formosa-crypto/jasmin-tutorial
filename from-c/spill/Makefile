include ../Makefile.base

# `complex_sum.s` is not generated: it is the GCC output the exercise is based
# on, kept in the repository because other GCC versions generate different code.

.PHONY: all run run-solution clean

all: spillO0.s spillO3.s test_spill test_complex_sum

run: test_spill test_complex_sum
	./test_spill
	./test_complex_sum

run-solution: test_complex_sum_solution
	./test_complex_sum_solution

spillO0.s: spill.c
	$(CC) -O0 -S -o $@ $<

spillO3.s: spill.c
	$(CC) -O3 -S -o $@ $<

%_jazz.s: %.jazz
	$(JASMINC) $(JASMIN_FLAGS) -o $@ $<

test_spill: test_spill.c spill.c spill_success_jazz.s
	$(CC) $(CFLAGS) -o $@ $^

test_complex_sum: test_complex_sum.c complex_sum.c complex_sum_jazz.s
	$(CC) $(CFLAGS) -o $@ $^

test_complex_sum_solution: test_complex_sum.c complex_sum.c complex_sum_solution_jazz.s
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f spillO0.s spillO3.s *_jazz.s test_spill test_complex_sum test_complex_sum_solution
