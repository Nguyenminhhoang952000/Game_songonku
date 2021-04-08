
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_


#include "CommonFunc.h"


class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) {rect_.x=x,rect_.y=y;}   //Ham xet kich thuoc cho cai rect
	SDL_Rect GetRect() const {return rect_;}  //Ham lay ra tam anh do 
	SDL_Texture* GetObject() const {return p_object_;} 

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);  // load anh 
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);  // load anh len nen nao
	void Free();   // giai phong cac doi tuong

protected:
	SDL_Texture* p_object_;   // luu tru cac hinh anh
	SDL_Rect rect_ ;  //luu kich thuoc cua tam anh do
};


#endif