include ../Makefile.base

.PHONY: all run run-solution clean

all: matrixO0.s matrixO3.s test

run: test
	./test

run-solution: test_solution
	./test_solution

# The same C function compiled twice, with different names.
matrixO0.s: matrix.c
	$(CC) -O0 -S -DFUNC_NAME=multiply_matrices -o $@ $<

matrixO3.s: matrix.c
	$(CC) -O3 -S -DFUNC_NAME=multiply_matrices_optimized -o $@ $<

%_jazz.s: %.jazz
	$(JASMINC) $(JASMIN_FLAGS) -o $@ $<

test: test.c matrixO0.s matrixO3.s matrix_jazz.s matrix_optimized_jazz.s
	$(CC) $(CFLAGS) -o $@ $^

test_solution: test.c matrixO0.s matrixO3.s matrix_jazz.s matrix_optimized_solution_jazz.s
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f matrixO0.s matrixO3.s *_jazz.s test test_solution
