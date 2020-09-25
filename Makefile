all:
	g++ -o build/npm src/main.cpp -O2 -std=c++14

test:
	pytest tests/test.py