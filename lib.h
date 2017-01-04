#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_ttf.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define RGB(r,g,b) RGBA((r), (g), (b), 255)
#define RGBA(r,g,b,a) (r), (g), (b), (a)
#define RED RGB(255,0,0)
#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)
#define ERR() exit(2);

typedef struct {
  const char* filename;
  SDL_Texture* texture;
} ImageTexture;

typedef struct {
  SDL_Window* Win;
  SDL_Renderer* Renderer;
  SDL_Surface* Surface;
  ImageTexture** Textures;
} RenderState;

void setup(void);
void loop(void);
void alert(const char*);
ImageTexture* loadImageTextureFromFilename(const char*);






