// GameSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"CommonFunc.h"
#include"BaseObject.h"
#include"game_map.h"
#include"MainObjet.h"
#include"ImpTimer.h"
#include"ThreatsObiect.h"
#include"TextObject.h"


BaseObject g_background;
TTF_Font* font_time = NULL;

bool InitData()  // khoi dong thong so cho moi truong cua SDL
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);  //thiet lap moi truong ban dau cho SDL
	if(ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");  // thiet lap che do ty len chat luong
	//tao cua so window cho game
	g_window = SDL_CreateWindow("Game songonku : Nguyen Minh Hoang",
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
			SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);  //truyen mau sac cho viec render do ra man hinh
			int imgFlags = IMG_INIT_PNG;   
			if(!(IMG_Init(imgFlags) && imgFlags))  // kiem tra  IMG_Init 
				success = false;
		}
		if(TTF_Init() == -1)
		{
			success = false;
			
		}
		font_time = TTF_OpenFont("font//dlxfont.ttf",15);
		if(font_time == NULL)
		{
			success = false ; 

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
	SDL_DestroyRenderer(g_screen); // giai phong g_screen
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}

std::vector<ThreatsObject*> MakeThreadList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* threats_objs = new ThreatsObject[20];

	for(int i=0;i<20;i++)
	{
		ThreatsObject* p_threat = (threats_objs +i);
		if(p_threat != NULL)
		{
			p_threat->LoadImg("img/threat_level.png",g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i*600);
			p_threat->set_y_pos(250);

			list_threats.push_back(p_threat);

		}
	}
	return list_threats;
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


	std::vector<ThreatsObject*> threats_list = MakeThreadList();


	int num_die = 0;
	//Time text
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);


	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	UINT mark_value = 0;

		
	
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

		g_background.Render(g_screen,NULL); // load anh len 


		game_map.DrawMap(g_screen); 
		Map map_data = game_map.getMap(); //Lay Map trong game_map_



		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_,map_data.start_y_); 
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);


		game_map.SetMap(map_data);  //Ban do cap nhap vi tri moi cho start_x_ va start_y_
		game_map.DrawMap(g_screen); //Ve lai

		for(int i=0;i<threats_list.size();i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			if(p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x_,map_data.start_y_);
				p_threat->DoPlayer(map_data);
				p_threat->Show(g_screen);


				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
				for(int jj=0; jj < tBullet_list.size() ; ++jj)
				{
					BulletObject* pt_bullet = tBullet_list.at(jj);
					if(pt_bullet)
					{
						bCol1= SDLCommonFunc::CheckCollision(pt_bullet->GetRect(),rect_player);
						if(bCol1)
						{
							p_threat->RemoveBullet(jj);
							break;
						}
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player,rect_threat);
				if(bCol1 || bCol2)
				{

					num_die++;
					if(num_die<=3)
					{
						p_player.SetRect(0,0);
						p_player.set_comback_time(60);
						SDL_Delay(1000);
						continue;

					}
					else
					{
						if(MessageBox(NULL,L"GAME OVER",L"Info", MB_OK | MB_ICONSTOP) == IDOK)
						{
						p_threat->Free();
						close();
						SDL_Quit();
						return 0;
						}
					}
					
				}
			}
		}


		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for(int r = 0; r< bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if(p_bullet != NULL)
			{
				for(int t=0;t< threats_list.size();++t)
				{
					ThreatsObject* obj_threat = threats_list.at(t);
					if(obj_threat != NULL)
					{

						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect,tRect);

						if(bCol)
						{
							mark_value++;

							p_player.RemoveBullet(r);
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);

						}
					}
				}
			}
		}
		//Hien thi thoi gian tro choi
		std::string str_time = "Time : ";
		Uint32 time_val = SDL_GetTicks()/1000;
		Uint32 val_time = 200 - time_val;
		if(val_time <=0)
		{
			if(MessageBox(NULL,L"GAME OVER",L"Info", MB_OK | MB_ICONSTOP) == IDOK)
						{
						is_quit = true;
						break;
						}
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time,g_screen);
			time_game.RenderText(g_screen,SCREEN_WIDTH - 200,15);
		}

		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark+=val_str_mark;

		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen,SCREEN_WIDTH*0.5-50 , 15);
		

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


