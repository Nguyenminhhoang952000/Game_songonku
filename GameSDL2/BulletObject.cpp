
#include "stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_=0;
	y_val_=0;
	is_move_ = false;

}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	if(bullet_dir_== DIR_RIGHT) //Huong sang phai
	{
		rect_.x += x_val_;
		if(rect_.x > x_border) //Neu vuot qua man hinh
		{
		is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_LEFT) //Huong sang trai
	{

		rect_.x -= x_val_;
		if(rect_.x < 0)
		{
			is_move_=false;
	
		}	
}
}
