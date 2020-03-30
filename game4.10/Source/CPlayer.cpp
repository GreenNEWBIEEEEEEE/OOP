#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameDialog.h"
#include "CMapManager.h"

namespace game_framework {
	CPlayer::CPlayer() :
		aniMoveLeft(3),
		aniMoveRight(3),
		aniMoveUp(3),
		aniMoveDown(3)
	{
		width = 80; height = 120;
		x = lastX = 300; y = lastY = 200;
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	CPlayer::~CPlayer() {
		facingDirection = nullptr;
	}

	void CPlayer::LoadBitmap()
	{
		aniMoveLeft.AddBitmap(IDB_PLAYER01_LEFT1, RGB(255,255,255));
		aniMoveLeft.AddBitmap(IDB_PLAYER01_LEFT2, RGB(255, 255, 255));
		aniMoveLeft.AddBitmap(IDB_PLAYER01_LEFT3, RGB(255, 255, 255));

		aniMoveRight.AddBitmap(IDB_PLAYER01_RIGHT1, RGB(255, 255, 255));
		aniMoveRight.AddBitmap(IDB_PLAYER01_RIGHT2, RGB(255, 255, 255));
		aniMoveRight.AddBitmap(IDB_PLAYER01_RIGHT3, RGB(255, 255, 255));

		aniMoveUp.AddBitmap(IDB_PLAYER01_UP1, RGB(255, 255, 255));
		aniMoveUp.AddBitmap(IDB_PLAYER01_UP2, RGB(255, 255, 255));
		aniMoveUp.AddBitmap(IDB_PLAYER01_UP3, RGB(255, 255, 255));

		aniMoveDown.AddBitmap(IDB_PLAYER01_DOWN1, RGB(255, 255, 255));
		aniMoveDown.AddBitmap(IDB_PLAYER01_DOWN2, RGB(255, 255, 255));
		aniMoveDown.AddBitmap(IDB_PLAYER01_DOWN3, RGB(255, 255, 255));
	}

	void CPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		
	}

	void CPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CPlayer::SetX(int x)
	{
		this->lastX = this->x;
		this->x = x;
	}

	void CPlayer::SetY(int y)
	{
		this->lastY = this->y;
		this->y = y;
	}

	int CPlayer::GetWidth() const
	{
		return width;
	}

	int CPlayer::GetHeight() const
	{
		return height;
	}

	int CPlayer::GetX() const 
	{
		return x;
	}

	int CPlayer::GetY() const
	{
		return y;
	}

	int CPlayer::GetLastX() const
	{
		return lastX;
	}

	int CPlayer::GetLastY() const
	{
		return lastY;
	}
		
	// OnMove
	// 需要傳入m 透過m回傳現在位置的屬性(EX: 是否是障礙物...等)
	void CPlayer::OnMove(CGameMap* m)
	{
		// 每一步移動量
		const int STEP_SIZE = 5;
		
		if (isMovingLeft)
		{
			// 當按下方向鍵時可先切換面向的方向, 不管之後是否有真的要移動
			facingDirection->OnMove();
			facingDirection = &aniMoveLeft;
			// 偵測障礙物 或 不可踩上去的地圖格子
			// 目前設定為 玩家的圖片是兩個垂直格子(80*120), 單個格子是80*60
			// 要偵測的是玩家下半身, 如此視覺上看起來才不會突兀
			if (m->IsEmpty(x - STEP_SIZE, y + 80) && m->IsEmpty(x - STEP_SIZE, y + 120))
			{
				x -= STEP_SIZE;
				// 移動時切換map在screen上的座標 從而達到screen或是鏡頭跟著玩家的視覺效果
				m->SetSX(m->GetSX() - STEP_SIZE); 
			}
		}
		if (isMovingRight)
		{
			facingDirection->OnMove();
			facingDirection = &aniMoveRight;
			if (m->IsEmpty(x + width +STEP_SIZE, y + 80) && m->IsEmpty(x + width + STEP_SIZE, y + 120))
			{
				x += STEP_SIZE;
				m->SetSX(m->GetSX() + STEP_SIZE);
			}
		}
		if (isMovingUp)
		{
			facingDirection->OnMove();
			facingDirection = &aniMoveUp;
			if (m->IsEmpty(x , y + 80 - STEP_SIZE) && m->IsEmpty(x + width , y + 80 - STEP_SIZE))
			{
				y -= STEP_SIZE;
				m->SetSY(m->GetSY() - STEP_SIZE);
			}
		}
		if (isMovingDown)
		{
			facingDirection->OnMove();
			facingDirection = &aniMoveDown;
			if (m->IsEmpty(x, y + 120 + STEP_SIZE) && m->IsEmpty(x + width, y + 120 + STEP_SIZE))
			{
				y += STEP_SIZE;
				m->SetSY(m->GetSY() + STEP_SIZE);
			}
		}
	}

	void CPlayer::OnShow(CGameMap* m)
	{
		if (facingDirection != nullptr)
		{
			// 畫出當前面向的方向的動畫
			// 用m計算出玩家的地圖點座標(x,y) 在 screen上的座標 因為最終是要在screen上畫
			facingDirection->SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			facingDirection->OnShow();
		}
	}

	void CPlayer::OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd)
	{
		// 傳入事件觸發
		mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd);
	}
}