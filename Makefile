first: main.cpp
	g++ main.cpp -o run

.PHONY: clean
clean:
	rm -f run