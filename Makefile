default:
	mkdir -p dist
	gcc -Wall -O3 --shared \
	-I/usr/local/include/SDL2 -lSDL2 \
	-fPIC -lc main.c -o dist/lib.o
	stack ghc Main.hs dist/lib.o -- -o dist/hs-exe
