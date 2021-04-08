
#include "stdafx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}


BaseObject::~BaseObject()
{
	Free();
}


bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load( path.c_str() );   //doc tam anh tu duong dan
	 if( load_surface != NULL )
  { 
		 SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		 //Chuyen surface ve new_texture
		 new_texture = SDL_CreateTextureFromSurface(screen, load_surface );  //luu giu toan bo thong tin cua tam anh
		 if(new_texture != NULL )
		 {
		 //Nhan kich thuoc hinh anh
		 rect_.w = load_surface->w;
		 rect_.h = load_surface->h;
		 }

		 //Loai bo be mat da tai cu
		 SDL_FreeSurface(load_surface);
		 
	}
		p_object_ = new_texture; 
		return p_object_ != NULL;
	 

}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h};
	// day toan bo thong so cua p_object len tren des voi kich thuoc va bien nam trong renderquad
	SDL_RenderCopy(des, p_object_, clip, &renderquad);  
}

void BaseObject::Free()
{

  if(p_object_ != NULL)
  {
    SDL_DestroyTexture(p_object_);
    p_object_ = NULL;
    rect_.w = 0;
    rect_.h = 0;
  }
} 
