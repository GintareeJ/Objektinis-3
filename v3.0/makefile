programa:
	g++ -std=c++17 -O3 -ffast-math -Wall -Wextra main2.cpp rusiavimas.cpp pasirinkimai.cpp -o programa

testai:
	g++ -std=c++17 testai.cpp -o testai

run: programa
	./programa.exe

test: testai
	./testai.exe

clean:
	rm -f programa.exe testai.exe