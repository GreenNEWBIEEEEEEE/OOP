#include "stdafx.h"   // necessary
#include "resource.h" // necessary
#include <mmsystem.h> // necessary
#include <ddraw.h>    // necessary
#include "gamelib.h"
#include "Player.h"
#include "CGameMap.h"

namespace game_framework {
	Player::Player() :
		aniMoveLeft(3),
		aniMoveRight(3),
		aniMoveUp(3),
		aniMoveDown(3)
	{
		width = 80; height = 120;
		x = 300; y = 200;
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}
	void Player::LoadBitmap()
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

	void Player::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		
	}

	void Player::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Player::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Player::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	// MAYBE FIXME
	void Player::OnMove(CGameMap *m)
	{
		const int STEP_SIZE = 5;
		
		if (isMovingLeft)
		{
			facingDirection->OnMove();
			facingDirection = &aniMoveLeft;
			if (m->IsEmpty(x - STEP_SIZE, y + 80) && m->IsEmpty(x - STEP_SIZE, y + 120))
			{
				x -= STEP_SIZE;
				m->SetSX(m->GetSX() - STEP_SIZE); // Change sx, sy of map
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

	void Player::OnShow(CGameMap *m)
	{
		if (facingDirection != nullptr)
		{
			facingDirection->SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			facingDirection->OnShow();
		}
	}
}