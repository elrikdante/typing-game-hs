default:
	mkdir -p dist
	gcc -Wall -O3 --shared \
	-g \
	-v \
	-I/usr/local/include/SDL2 \
	-I/usr/local/Cellar/sdl2_ttf/2.0.14 \
	-I/usr/local/Cellar/openssl/1.0.2g/include \
	-Ivendor/stb \
	-lc \
	-lSDL2 \
	-lSDL2_ttf \
	-lcrypto \
	-Wl,-v \
	-fPIC main.c -o dist/lib.o 

	stack ghc Main.hs dist/lib.o -- -o dist/hs-exe

linker:
	gcc -Xlinker -lc main.c -lSDL2 -lSDL2_ttf -I/usr/local/include/SDL2 -Ivendor/stb -I/usr/local/Cellar/sdl2_ttf/2.0.14 -v

tidy:
	find . \( -name "*~" -o -name "Main.hi" -o -name "Main.o" -o -name "a.out" \) -exec rm -i {} \;


debug:
	sudo dtruss ./dist/hs-exe 2>&1 \| tee debug.log
panic:
	lldb ./dist/hs-exe

.PHONY: tidy debug panic linker
