
UWNETID = `cat UW_ID.txt`

EXPLOITS = $(wildcard *.txt)

test:
	@echo "performing tests for $(UWNETID)"
	@echo "run -g -u $(UWNETID) < __test.bytes >> __results.log" > __gdb.in
	@echo "quit" >> __gdb.in
	@touch __results.log
	@for e in $(EXPLOITS); do echo $$e >> __results.log; ./sendstring < $$e > __test.bytes; gdb -x __gdb.in bufbomb; echo >> __results.log; done
	@echo
	@echo == Summary ================================
	@cat __results.log
	@rm -f __gdb.in __test.bytes __results.log
