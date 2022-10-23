GENERATES=*~ result* range
SYMBOL=$

range: range.c
	gcc -g -O0 -o range range.c

test: range
	gdb --batch --quiet --command=test1.gdb ./range | grep '\$(SYMBOL)' 1> result1
	gdb --batch --quiet --command=test2.gdb ./range | grep '\$(SYMBOL)' 1> result2
	cmp target1 result1
	cmp target2 result2

clean:
	rm -rf $(GENERATES)
