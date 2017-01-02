#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "SDL2/SDL.h"

SDL_Window*    Window   = NULL;
SDL_Renderer*  Renderer = NULL;
SDL_Surface*   PrimaryS =NULL;

static const int WINDOW_HEIGHT=500;
static const int WINDOW_WIDTH =500;
int
some_func(int a, int b){
  return a + b;
}

void
some_func_impure(int a, int b) {
   printf("THE ANSWER: %d \n", some_func(a,b));
}

void
setup(void) {
  SDL_Event event;
  
  if(0 > SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Could not initialise %s\n",SDL_GetError());
    ERR()
  }
  if (NULL == (Window = SDL_CreateWindow(
			       "X",
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       WINDOW_HEIGHT,
			       WINDOW_WIDTH,
			       SDL_WINDOW_SHOWN))) {
     fprintf(stderr, "Could not create window %s\n",SDL_GetError());
     ERR()
  }
  Renderer = SDL_CreateRenderer(
				Window,
				-1,
				SDL_RENDERER_ACCELERATED);
  if (NULL == Renderer) {
    fprintf(stderr, "Could not create Render %s\n",SDL_GetError());
    ERR()
  }

  int done = 0; 
  while (!done) {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_RenderClear(Renderer);
    SDL_RenderPresent(Renderer);
    
    while (SDL_PollEvent(&event)) { 
	switch (event.type) { 
	  case SDL_WINDOWEVENT: 
            switch (event.window.event) { 
	    case SDL_WINDOWEVENT_CLOSE: 
              done = 1; 
              break; 
          } 
          break; 
       } 
    }
    fprintf(stderr, "ERRR: ",SDL_GetError());
  }
  SDL_Quit();
}

void
loop(void) {
  
}
  
int
main(int argc, char** argv){

  if (2 > argc) {
    printf("WTF DUDE?");
    return 2;
  } else {
    char* arg0 = argv[1];
    //arg1 = *argv[1];
    printf("MADE IT! %s \n", arg0);//, arg1);
    some_func_impure(10,20);
    return 0;
  }
}


