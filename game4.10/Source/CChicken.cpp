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
	void CChicken::OnShow(CGameMap* m)
	{
		if (m == map)
		{
			if (currentMove != nullptr)
			{
				// 畫出當前面向的方向的動畫
				// 用m計算出玩家的地圖點座標(x,y) 在 screen上的座標 因為最終是要在screen上畫
				currentMove->SetTopLeft(m->ScreenX(x), m->ScreenY(y));


				currentMove->OnShow();
			}
		}
	}

	void CChicken::LoadBitmap()
	{

	}

	void CChicken::OnMove(CGameMap* m, vector<CGameObject*>* obj)
	{
		int rnd = (rand() % 100);
		isMovingLeft = rnd < 20;
		isMovingRight = rnd >= 20 && rnd < 40;
		isMovingUp = rnd >= 40 && rnd < 60;
		isMovingDown = rnd >= 60 && rnd < 80;

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
			if (m->IsEmpty(bx - STEP_SIZE, by + 64) && m->IsEmpty(bx - STEP_SIZE, by + 80) && !DetectCollision(obj, -STEP_SIZE, 0))
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
			if (m->IsEmpty(bx + width + STEP_SIZE, by + 64) && m->IsEmpty(bx + width + STEP_SIZE, by + 80) && !DetectCollision(obj, STEP_SIZE, 0))
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
			if (m->IsEmpty(bx + 10, by + 64 - STEP_SIZE) && m->IsEmpty(bx - 10 + width, by + 64 - STEP_SIZE) && !DetectCollision(obj, 0, -STEP_SIZE))
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
			if (m->IsEmpty(bx + 10, by + 80 + STEP_SIZE) && m->IsEmpty(bx - 10 + width, by + 80 + STEP_SIZE) && !DetectCollision(obj, 0, STEP_SIZE))
			{
				y += STEP_SIZE;
				by += STEP_SIZE;
				ey += STEP_SIZE;
				m->SetSY(m->GetSY() + STEP_SIZE);
			}
		}
		
	}

}

