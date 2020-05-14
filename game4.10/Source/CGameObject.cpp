#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CAnimal.h"
#include "CGameMap.h"
#include "CGameObject.h"

namespace game_framework {
	void CGameObject::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;

	}

	void CGameObject::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CGameObject::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CGameObject::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CGameObject::SetX(int x)
	{
		this->lastX = this->x;
		this->x = x;
		bx = x + 64;
	}

	void CGameObject::SetY(int y)
	{
		this->lastY = this->y;
		this->y = y;
		by = y + 40;
	}

	int CGameObject::GetHealthPoint() const
	{
		return this->healthPoint;
	}

	int CGameObject::GetWidth() const
	{
		return width;
	}

	int CGameObject::GetHeight() const
	{
		return height;
	}

	int CGameObject::GetX() const
	{
		return x;
	}

	int CGameObject::GetY() const
	{
		return y;
	}

	int CGameObject::GetBodyX() const
	{
		return bx;
	}

	int CGameObject::GetBodyY() const
	{
		return by;
	}

	int CGameObject::GetLastX() const
	{
		return lastX;
	}

	int CGameObject::GetLastY() const
	{
		return lastY;
	}

	void CGameObject::DecreaseHP(int hp)
	{
		if (healthPoint - hp < 0)
			healthPoint = 0;
		else
			healthPoint -= hp;
	}

	void CGameObject::IncreaseHP(int hp)
	{
		if (healthPoint + hp > 100)
			healthPoint = 100;
		else
			healthPoint += hp;
	}

	CAnimal* CGameObject::GetFacingAnimal() // 取得你面前最近的物件
	{
		return facingAnimal;
	}

	bool CGameObject::DetectCollision(vector<CGameObject*>* obj, int nextX, int nextY)
	{
		int x = this->bx + nextX;
		int y = this->by + nextY;

		for (unsigned int i = 0; i < obj->size(); i++) {
			if (this == (*obj)[i])
				continue;

			if (x < (*obj)[i]->bx + (*obj)[i]->width &&   //左碰撞
				x + this->width >(*obj)[i]->bx &&         //右碰撞
				y < (*obj)[i]->by + (*obj)[i]->height &&  //上碰撞
				y + this->height >(*obj)[i]->by)          //下碰撞
			{
				if (i != 0)
					facingAnimal = (CAnimal*)(*obj)[i];
				return true; //有碰撞
			}
		}
		facingAnimal = nullptr;
		return false;
	}

}
