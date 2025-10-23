COMPILER_FOR_C   = gcc
COMPILER_FOR_CPP = g++
CFLAGS = -Wall -Werror -g

.PHONY: clean

%:
	@if [ -f "$@.c" ]; then \
		echo "Compiling $@.c with $(COMPILER_FOR_C)"; \
		$(COMPILER_FOR_C) $(CFLAGS) $@.c -o $@; \
	elif [ -f "$@.cpp" ]; then \
		echo "Compiling $@.cpp with $(COMPILER_FOR_CPP)"; \
		$(COMPILER_FOR_CPP) $(CFLAGS) $@.cpp -o $@; \
	else \
		echo "Error: No source file named $@.c or $@.cpp"; \
		exit 1; \
	fi


clean:
	rm -f *.o *.out *.exe
