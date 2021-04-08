// GameSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"CommonFunc.h"
#include"BaseObject.h"
#include"game_map.h"
#include"MainObjet.h"
#include"ImpTimer.h"


BaseObject g_background;

bool InitData()  // khoi dong thong so cho moi truong cua SDL
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);  //thiet lap moi truong ban dau cho SDL
	if(ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");  // thiet lap che do ty len chat luong
	//tao cua so window cho game
	g_window = SDL_CreateWindow("Game songonku : Hoang",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH,SCREEN_HEIGHT,
								SDL_WINDOW_OPENGL); 

	if(g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);   
		if(g_screen ==NULL)
				success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("img//back1ground.png",g_screen);  // truyen dia chi tam anh vao
	if(ret == false)
		return false;
	return true;
}	
void close()  // giai phong cac doi tuong
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}

int main(int argc, char* argv[])
{
	ImpTimer fps_timer;
	if(InitData() == false)
		return -1;
	if(LoadBackground() == false)
		return -1;


	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_right.png",g_screen);
	p_player.set_clips();




	bool is_quit = false;
	while(!is_quit)
	{
		fps_timer.start();

		while(SDL_PollEvent(&g_event)!=0)
		{
			if(g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			p_player.HandelInputAction(g_event,g_screen);
		}

		SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR); 
		SDL_RenderClear(g_screen); // xoa man hinh

		g_background.Render(g_screen,NULL);


		game_map.DrawMap(g_screen); 
		Map map_data = game_map.getMap();

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);


		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);  //update lai man hinh 
		
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000/FRAME_PER_SECOND;  //ms

		if(real_imp_time<time_one_frame)
		{
			
			int delay_time = time_one_frame- real_imp_time;
			if(delay_time>=0)
			SDL_Delay(delay_time);

		}
	}


    close(); 
	return 0;
}


