CC = gcc
CFLAGS = -Wall -Werror -g
SRCMODULES = const.c fun.c prog.c
OBJMODULES = $(SRCMODULES:.c=.o)
GENERATES = prog prog-* *~
DEPS = $(wildcard $(OBJMODULES:%=%.d))
MYLIBS = liboutput_static.a liboutput.so
TESTFILES = err1 err2 err3 testfile1 testfile2 testfile3 testfile4 testfile5 testfile6
SECONDTEST = Q
THIRDTEST = Q W E

.PHONY: clean

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -MD -MP -MF "$@.d" $< -o $@

all: prog prog-a prog-so
	

prog: const.o prog.o fun.o
	$(CC) $(CFLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@  $^

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

test: prog prog-a prog-so
	./prog 2> err1
	./prog-a 2> err2
	LD_LIBRARY_PATH=`pwd` ./prog-so 2> err3
	./prog 1> testfile1 $(SECONDTEST)
	./prog-a 1> testfile2 $(SECONDTEST)
	LD_LIBRARY_PATH=`pwd` ./prog-so 1> testfile3 $(SECONDTEST)
	@echo $(shell cmp testfile1 testfile2)
	@echo $(shell cmp testfile1 testfile3)
	@echo $(shell cmp testfile2 testfile3)
	./prog 1> testfile4 $(THIRDTEST)
	./prog-a 1> testfile5 $(THIRDTEST)
	LD_LIBRARY_PATH=`pwd` ./prog-so 1> testfile6 $(THIRDTEST)
	@echo $(shell cmp testfile4 testfile5)
	@echo $(shell cmp testfile5 testfile6)
	@echo $(shell cmp testfile4 testfile6)


ifneq (clean, $(MAKECMDGOALS))
-include $(DEPS)
endif

clean:
	rm -f $(OBJMODULES) $(DEPS) $(MYLIBS) $(TESTFILES)
	rm -rf $(GENERATES)
