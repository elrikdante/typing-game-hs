int some_func(int, int);
void some_func_impure(int, int);
void createWindow(void);
void setup(void);
void loop(void);
void alert(char*);
#define RGB(r,g,b) RGBA((r), (g), (b), 255)
#define RGBA(r,g,b,a) (r), (g), (b), (a)
#define RED RGB(255,0,0)
#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)
#define ERR() exit(2);
