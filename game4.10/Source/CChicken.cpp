#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameObject.h"
#include "CAnimal.h"
#include "CMapManager.h"
#include "CChicken.h"
#include "CPlayer.h"
namespace game_framework
{
	CChicken::CChicken()
	{
		width = 64; height = 53;
		x = lastX = 200; y = lastY = 400;
		bx = x; by = y;
		currentDirection = CAnimal::Direction::Down;
		currentMove = &moveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		STEP_SIZE = 20;
	}

	CChicken::~CChicken()
	{

	}

	void CChicken::OnShow(CGameMap* m)
	{
		//if (m == map)
		//{
			if (currentMove != nullptr)
			{
				// 畫出當前面向的方向的動畫
				// 用m計算出玩家的地圖點座標(x,y) 在 screen上的座標 因為最終是要在screen上畫
				currentMove->SetTopLeft(m->ScreenX(x), m->ScreenY(y));


				currentMove->OnShow();
			}
		//}
	}

	void CChicken::LoadBitmap()
	{
		{
			moveLeft.AddBitmap(IDB_Chicken_left01, RGB(255, 255, 255));
			moveLeft.AddBitmap(IDB_Chicken_left02, RGB(255, 255, 255));
		}

		{
			moveRight.AddBitmap(IDB_Chicken_right01, RGB(255, 255, 255));
			moveRight.AddBitmap(IDB_Chicken_right02, RGB(255, 255, 255));
		}

		{
			moveUp.AddBitmap(IDB_Chicken_back01, RGB(255, 255, 255));
			moveUp.AddBitmap(IDB_Chicken_back02, RGB(255, 255, 255));
		}

		{
			moveDown.AddBitmap(IDB_Chicken_front01, RGB(255, 255, 255));
			moveDown.AddBitmap(IDB_Chicken_front02, RGB(255, 255, 255));
		}
	}

	void CChicken::OnMove(CGameMap* m, vector<CGameObject*>* obj)
	{
		int rnd = (rand() % 100);
		isMovingLeft = rnd % 37 == 0;
		isMovingRight = rnd % 47 == 0;
		isMovingUp = rnd % 59 == 0;
		isMovingDown = rnd % 71 == 0;
		bool isStopping = rnd % 2 == 0;

		// 每一步移動量
		if (isMovingLeft)
		{
			// 更改方向旗標
			lastDirection = currentDirection;
			currentDirection = CAnimal::Direction::Left;

			// 當按下方向鍵時可先切換面向的方向, 不管之後是否有真的要移動
			currentMove->OnMove();
			currentMove = &moveLeft;
			// 偵測障礙物 或 不可踩上去的地圖格子
			// 目前設定為 玩家的圖片是64*80
			// 要偵測的是玩家下半身, 如此視覺上看起來才不會突兀
			if (m->IsEmpty(bx - STEP_SIZE, by) && m->IsEmpty(bx - STEP_SIZE, by + height) && !DetectCollision(obj, -STEP_SIZE, 0))
			{
				x -= STEP_SIZE;
				bx -= STEP_SIZE;
				ex -= STEP_SIZE;
			}
		}
		else if (isMovingRight)
		{
			// 更改方向旗標
			lastDirection = currentDirection;
			currentDirection = CAnimal::Direction::Right;

			currentMove->OnMove();
			currentMove = &moveRight;
			if (m->IsEmpty(bx + width + STEP_SIZE, by) && m->IsEmpty(bx + width + STEP_SIZE, by + height) && !DetectCollision(obj, STEP_SIZE, 0))
			{
				x += STEP_SIZE;
				bx += STEP_SIZE;
				ex += STEP_SIZE;
			}
		}
		else if (isMovingUp)
		{
			// 更改方向旗標
			lastDirection = currentDirection;
			currentDirection = CAnimal::Direction::Up;

			currentMove->OnMove();
			currentMove = &moveUp;
			if (m->IsEmpty(bx, by - STEP_SIZE) && m->IsEmpty(bx + width, by - STEP_SIZE) && !DetectCollision(obj, 0, -STEP_SIZE))
			{
				y -= STEP_SIZE;
				by -= STEP_SIZE;
				ey -= STEP_SIZE;
			}
		}
		else if (isMovingDown)
		{
			// 更改方向旗標
			lastDirection = currentDirection;
			currentDirection = CAnimal::Direction::Down;

			currentMove->OnMove();
			currentMove = &moveDown;
			// bx+/-5 寬度設小一點
			if (m->IsEmpty(bx, by + height + STEP_SIZE) && m->IsEmpty(bx + width, by + height + STEP_SIZE) && !DetectCollision(obj, 0, STEP_SIZE))
			{
				y += STEP_SIZE;
				by += STEP_SIZE;
				ey += STEP_SIZE;
			}
		}
		else if (isStopping)
		{
			// Do nothing
		}
		
	}

}

