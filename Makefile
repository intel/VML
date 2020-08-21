export CKL_HOME=$(CURDIR)

.PHONY: lib clean all test bench default_target

default_target:
	@echo "|=+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=|"
	@echo "|  ------------------------- CKL ---------------------------  |"	
	@echo "|                                                             |"
	@echo "| Usage: make all              build CKL lib and test bins    |"
	@echo "|        make lib              build CKL lib                  |"
	@echo "|        make test             build CKL tests                |"
	@echo "|        make bench            build CKL perf benchmarks      |"
	@echo "|        make runtest          run test against CKL lib       |"
	@echo "|        make clean            remove all built objects       |"
	@echo "|        make cleantest        remove built tests             |"
	@echo "|        make cleanbench       remove built benchmarks        |"
	@echo "|        make cleanall         remove objs, test bins, libs   |"
	@echo "|                                                             |"
	@echo "|-------------------------------------------------------------|"

all: lib test bench


lib:
	mkdir -p lib
	$(MAKE) -C src all

test: lib
	$(MAKE) -C tests all

bench: lib
	$(MAKE) -C benchmarks all

runtest: test
	$(MAKE) -C tests runtest

clean:
	$(MAKE) -C src clean

cleantest:
	$(MAKE) -C tests clean

cleanbench:
	$(MAKE) -C benchmarks clean

cleanall:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean 
	$(MAKE) -C benchmarks clean 
	-rm -rf lib
