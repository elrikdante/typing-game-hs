/* Authour: Dante Elrik */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "SDL2/SDL.h"

SDL_Window*    Window   = NULL;
SDL_Renderer*  Renderer = NULL;
SDL_Surface*   PrimaryS = NULL;
SDL_Texture*   PrimaryT = NULL;
SDL_Event      event;
char*          Alert    = NULL;
int            Done     = 0;
int            FrameCnt = 0;

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
loop(void) {
  FrameCnt ++;
  if (Done) {
    SDL_Quit();
    return;
  }
  
  SDL_SetRenderDrawColor(Renderer, BLK);
  SDL_RenderClear(Renderer);

  int x,y;
  for(x=0; x < WINDOW_WIDTH; x++) {
    for(y=0; y < WINDOW_HEIGHT; y++) {
      SDL_SetRenderDrawColor(Renderer, RGB(0,x,y));
      SDL_RenderDrawPoint(Renderer, x, y);
    }
  }
  SDL_RenderPresent(Renderer);
  
  while (SDL_PollEvent(&event)) { 
	switch (event.type) { 
	  case SDL_WINDOWEVENT: 
            switch (event.window.event) { 
	    case SDL_WINDOWEVENT_CLOSE: 
              Done = 1; 
              break; 
          } 
          break; 
       } 
    }
  //fprintf(stderr, "Frame: %d\n", FrameCnt);
}

void
alert(char* msg){
  Alert = msg;
}

void
setup(void) {
  
  if(0 > SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Could not initialise %s\n",SDL_GetError());
    ERR()
  }
  Window = SDL_CreateWindow(
			    "X",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    WINDOW_HEIGHT,
			    WINDOW_WIDTH,
			    SDL_WINDOW_SHOWN);
  if (NULL == Window) {
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
  Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    
  PrimaryS = SDL_CreateRGBSurface(
				  0,
				  WINDOW_WIDTH,
				  WINDOW_HEIGHT,
				  32,
				  rmask,
				  gmask,
				  bmask,
				  amask
				  );

  if (PrimaryS == NULL) {
        fprintf(stderr,"SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        ERR()
  }
				  
}


int
main(int argc, char** argv){  return 0; }

  /* SDL_LockSurface(PrimaryS); */
  
  /* int x,y; */
  /* for(x=0; x < WINDOW_WIDTH; x++) { */
  /*   for(y=0; y < WINDOW_HEIGHT; y++) { */
  /*     SDL_MapRGBA( */
  /*                   PrimaryS->format, */
  /*                   255, */
  /*                   255, */
  /*                   255, */
  /*                   255 */
  /* 		  ); */
  /*   } */
  /* } */
  /* SDL_UnlockSurface(PrimaryS); */
  /* PrimaryT = SDL_CreateTextureFromSurface(Renderer, PrimaryS); */
  /* if (NULL == PrimaryT) { */
  /*    fprintf(stderr, "SDL_CreateTextureFromSurface(): %s\n",SDL_GetError()); */
  /*    ERR() */
  /* } */
  /* SDL_RenderCopy(Renderer, PrimaryT,NULL, NULL); */

