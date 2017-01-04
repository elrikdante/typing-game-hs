/* Authour: Dante Elrik */
#include "lib.h"
SDL_Window*    Window   = NULL;
SDL_Renderer*  Renderer = NULL;
SDL_Surface*   PrimaryS = NULL;
SDL_Texture*   LogoT    = NULL;
TTF_Font*      Font     = NULL;
SDL_Event      event;

char*          Alert    = NULL;
int            Done     = 0;
int            FrameCnt = 0;

static const int NUM_STARS=500;
static const int WINDOW_HEIGHT=500;
static const int WINDOW_WIDTH =500;

ImageTexture*
loadImageTextureFromFilename(const char* filename) {
  int req_format = STBI_rgb_alpha;
  int width, height, orig_format;
  unsigned char* data = stbi_load(
				  filename,
				  &width,
				  &height,
				  &orig_format,
				  req_format);
  SDL_Texture* texture;
  if(data == NULL) {
    fprintf(stderr,"Loading image failed: %s", stbi_failure_reason());
    ERR()
  }
  
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  int shift = (req_format == STBI_rgb) ? 8 : 0;
  rmask = 0xff000000 >> shift;
  gmask = 0x00ff0000 >> shift;
  bmask = 0x0000ff00 >> shift;
  amask = 0x000000ff >> shift;
#else // little endian, like x86
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
#endif

  int depth, pitch;
  if (req_format == STBI_rgb) {
    depth = 24;
    pitch = 3*width; // 3 bytes per pixel * pixels per row
  } else { // STBI_rgb_alpha (RGBA)
    depth = 32;
    pitch = 4*width;
  }

  SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
                                             rmask, gmask, bmask, amask);
  if (surf == NULL) {
    fprintf(stderr,"Creating surface failed: %s", SDL_GetError());
    stbi_image_free(data);
    ERR()
  }

  texture = SDL_CreateTextureFromSurface(Renderer, surf);
  if (NULL == texture) {
     fprintf(stderr, "SDL_CreateTextureFromSurface(): %s\n",SDL_GetError());
     ERR()
  }
  stbi_image_free(data);
  SDL_FreeSurface(surf);
  ImageTexture* imgT = malloc(sizeof(ImageTexture));
  imgT->filename = filename;
  imgT->texture  = texture;
  return imgT;
}

void
alert(const char* msg){
  Alert = msg;
}

void
setup(void) {
  
  if(0 > SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Could not initialise %s\n",SDL_GetError());
    ERR()
  }

  TTF_Init();

  char*     font_path = "/System/Library/Fonts/SFNSDisplay.ttf";
  Font = TTF_OpenFont(font_path, 24);
  if (NULL == Font) {
    fprintf(stderr, "error: font (%s)  not found\n ", font_path);
    ERR()
  }

  Window = SDL_CreateWindow(
			    "X",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    WINDOW_HEIGHT,
			    WINDOW_WIDTH,
			    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_FULLSCREEN);
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

  if (NULL == PrimaryS) {
        fprintf(stderr,"SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        ERR()
  }

  ImageTexture* t = loadImageTextureFromFilename("./dist/logo.png");

  LogoT = t->texture;
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
  SDL_RenderCopy(Renderer, LogoT, NULL , NULL);
  int starCount;
  for (starCount=0; starCount < NUM_STARS; starCount++) {
    SDL_SetRenderDrawColor(Renderer, WHT);
    SDL_RenderDrawPoint(Renderer, rand() % WINDOW_WIDTH , rand() % WINDOW_HEIGHT);
  }

  char*        phrase         ="put your text here";
  EVP_MD_CTX   mdctx;
  const EVP_MD* md;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int           md_len;

  OpenSSL_add_all_digests();
  md = EVP_get_digestbyname("md5");
  
  if (NULL == md) {
    fprintf(stderr, "Can't get MD5???");
    ERR()
  }

  EVP_MD_CTX_init(&mdctx);
  EVP_DigestInit_ex(&mdctx, md, NULL);
  EVP_DigestUpdate(&mdctx, phrase, strlen(phrase));
  EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
  EVP_MD_CTX_cleanup(&mdctx);

  SDL_Color    White          = {0, FrameCnt, FrameCnt, FrameCnt};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, md_value, White);
  SDL_Texture* Message        = SDL_CreateTextureFromSurface(Renderer, surfaceMessage);
  SDL_FreeSurface(surfaceMessage);
  SDL_Rect     Message_rect; //create a rect

  Message_rect.x = FrameCnt % WINDOW_WIDTH;  //controls the rect's x coordinate 
  Message_rect.y = 0; // controls the rect's y coordinte
  Message_rect.w = 100; // controls the width of the rect
  Message_rect.h = 100; // controls the height of the rect

  SDL_RenderCopy(Renderer, Message, NULL, &Message_rect);
  SDL_DestroyTexture(Message);
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

int
main(int argc, char** argv){  return 0; }

