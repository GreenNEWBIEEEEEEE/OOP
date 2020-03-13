#include "stdafx.h"   // necessary
#include "resource.h" // necessary
#include <mmsystem.h> // necessary
#include <ddraw.h>    // necessary
#include "gamelib.h"
#include "CCat.h"

namespace game_framework {
	// Constructor
	CCat::CCat()
	{
		is_angry = false;
		x = 300;
		y = 200;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CCat::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_TEST_CAT, RGB(255,255,255));
	}

	void CCat::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void CCat::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CCat::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void CCat::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}


	void CCat::OnMove()
	{
		const int STEP_SIZE = 2;
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void CCat::OnShow()
	{
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}

}