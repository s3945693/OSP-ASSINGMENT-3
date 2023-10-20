all: 
	$(MAKE) clean
	$(MAKE) firstfit
	$(MAKE) bestfit


firstfit: 
	@echo making firstfit...
	g++ -Wall -Werror -std=c++20 -g -o firstfit main.cpp firstfit.cpp
	@echo "done"

bestfit:
	@echo making bestfit...
	g++ -Wall -Werror -std=c++20 -g main.cpp bestfit.cpp -o bestfit
	@echo "done"


#clean by going into each directory and running make clean
clean: 
	@echo "cleaning up..."
	@rm -rf firstfit bestfit *.dSYM
	@echo "done"

