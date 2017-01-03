*) Web
*)source: http://stackoverflow.com/questions/22903466/sdl2-createrenderer-throwing-invalid-window-error
*)source: https://forums.libsdl.org/viewtopic.php?t=6694&sid=6249ace66026c9e8798690978a824512
*)source: http://wiki.libsdl.org/SDL_RenderPresent
*)source: https://forums.libsdl.org/viewtopic.php?t=9163sid=23359eedacf25591f8fe7c3423342de4SDL2
*)source: https://github.com/elrikdante/sdl-starfield/blob/master/main.c
*)(LLDB | GDB) http://lldb.llvm.org/lldb-gdb.html
*)http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/mac/index.php
*)https://www.libsdl.org/projects/SDL_ttf/
*)https://blogs.oracle.com/dipol/entry/dynamic_libraries_rpath_and_mac

*) other
man install_name_tool

*) install
brew install sdl2

*) tips 
Signing SDL Extenion framework
codesign -f -s - SDL2_ttf.framework #=> SDL2_ttf.framework: replacing existing signature

*) diagnostics
objdump -p dist/hs-exe
