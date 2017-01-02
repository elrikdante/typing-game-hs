default:
	mkdir -p dist
	gcc -Wall -O3 --shared \
	-I/usr/local/include/SDL2 -lSDL2 \
	-Ivendor/stb \
	-fPIC -lc main.c -o dist/lib.o
	stack ghc Main.hs dist/lib.o -- -o dist/hs-exe
tidy:
	find . -name "*~" -exec rm -i {} \;

debug:
	sudo dtruss ./dist/hs-exe 2>&1 | tee debug.log

.PHONY: tidy debug
