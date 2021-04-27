
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<string>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h> // am thanh
#include<SDL_ttf.h>  //font chu


static SDL_Window* g_window = NULL;   // xay dung fom window cho game
static SDL_Renderer* g_screen = NULL;   
static SDL_Event g_event;   // nhan su kien tu ban phim,chuot
static SDL_Renderer* g_img_menu=NULL;

//Screen-Danh cho man hinh
const int FRAME_PER_SECOND = 30; // fps so frame trong 1s 
const int SCREEN_WIDTH = 1400;  //chieu rong cua man hinh
const int SCREEN_HEIGHT = 640;  //chieu cao
const int SCREEN_BPP = 32;		


const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180; 

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64    // dinh nghia kich thuoc cua mat luoi

#define MAX_MAP_X 400   // dinh nghia kich thuoc cua file map
#define MAX_MAP_Y 10    

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;

};

typedef struct Map
{
	int start_x_;  // vi tri bao nhieu
	int start_y_;
	
	//chi so cua o do( o thu bao nhieu )
	int max_x_; 
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];  // luu toan bo trang thai cua cac o do 
	char* file_name_;   // luu ten file
};



namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1 , const SDL_Rect& object2);

}
#endif



