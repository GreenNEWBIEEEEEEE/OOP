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
		width = 64; height = 80;
		x = lastX = 300; y = lastY = 200;
		bx = x + 64; by = y + 40; //
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;


		tool.push_back(0); // 手 
		tool.push_back(1); // 斧頭
		tool.push_back(2); // 槌子
		tool.push_back(3); // 鋤頭
		tool.push_back(4); // 種子袋
		tool.push_back(5); // 鐮刀
		toolSelector = 0;  // 一開始是手

		aniUseTool_0.SetDelayCount(3);
		
		aniUseTool_1_front.SetDelayCount(3);
		aniUseTool_1_back.SetDelayCount(3);
		aniUseTool_1_left.SetDelayCount(3);
		aniUseTool_1_right.SetDelayCount(3);
		
		aniUseTool_2_front.SetDelayCount(3);
		aniUseTool_2_back.SetDelayCount(3);
		aniUseTool_2_left.SetDelayCount(3);
		aniUseTool_2_right.SetDelayCount(3);
		
		aniUseTool_3_front.SetDelayCount(3);
		aniUseTool_3_back.SetDelayCount(3);
		aniUseTool_3_left.SetDelayCount(3);
		aniUseTool_3_right.SetDelayCount(3);
		
		aniUseTool_4.SetDelayCount(3);

		aniUseTool_5_front.SetDelayCount(3);
		aniUseTool_5_back.SetDelayCount(3);
		aniUseTool_5_left.SetDelayCount(3);
		aniUseTool_5_right.SetDelayCount(3);
	}

	CPlayer::~CPlayer() {
		facingDirection = nullptr;
	}

	void CPlayer::LoadBitmap()
	{
		///
		/// 載入上下左右移動的動畫
		/// 
		{
			aniMoveLeft.AddBitmap(IDB_People_left01, RGB(255, 255, 255));
			aniMoveLeft.AddBitmap(IDB_People_left02, RGB(255, 255, 255));
			aniMoveLeft.AddBitmap(IDB_People_left03, RGB(255, 255, 255));

			aniMoveRight.AddBitmap(IDB_People_right01, RGB(255, 255, 255));
			aniMoveRight.AddBitmap(IDB_People_right02, RGB(255, 255, 255));
			aniMoveRight.AddBitmap(IDB_People_right03, RGB(255, 255, 255));

			aniMoveUp.AddBitmap(IDB_People_back01, RGB(255, 255, 255));
			aniMoveUp.AddBitmap(IDB_People_back02, RGB(255, 255, 255));
			aniMoveUp.AddBitmap(IDB_People_back03, RGB(255, 255, 255));

			aniMoveDown.AddBitmap(IDB_People_front01, RGB(255, 255, 255));
			aniMoveDown.AddBitmap(IDB_People_front02, RGB(255, 255, 255));
			aniMoveDown.AddBitmap(IDB_People_front03, RGB(255, 255, 255));
		}
		

		///
		/// 載入切換工具的動畫
		/// 請參閱各個工具的編號
		///
		// 手
		{
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		}

		// 斧頭
		{
			aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		}

		// 槌子
		{
			aniChangeTool_2.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		}

		// 鋤頭
		{
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		}

		// 種子袋
		{
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		}

		// 鐮刀
		{
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		}

		///
		/// 載入使用工具的動畫
		///
		// 手
		{

		}
		// 斧頭
		{

		}
		// 槌子
		{

		}
		// 鋤頭
		{

		}
		// 種子袋
		{
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed01, RGB(255,255,255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed02, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed03, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed04, RGB(255, 255, 255));
		}
		// 鐮刀
		{
			
		}
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

	int CPlayer::GetDirection() const
	{
		return direction;
	}
		
	// OnMove
	// 需要傳入m 透過m回傳現在位置的屬性(EX: 是否是障礙物...等)
	void CPlayer::OnMove(CGameMap* m)
	{
		// 每一步移動量
		const int STEP_SIZE = 5;
		
		if (isMovingLeft)
		{
			// 更改方向旗標
			direction = 3;

			// 當按下方向鍵時可先切換面向的方向, 不管之後是否有真的要移動
			facingDirection->OnMove();
			facingDirection = &aniMoveLeft;
			// 偵測障礙物 或 不可踩上去的地圖格子
			// 目前設定為 玩家的圖片是64*80
			// 要偵測的是玩家下半身, 如此視覺上看起來才不會突兀
			if (m->IsEmpty(bx - STEP_SIZE, by + 64) && m->IsEmpty(bx - STEP_SIZE, by + 80))
			{
				x -= STEP_SIZE;
				bx -= STEP_SIZE;
				ex -= STEP_SIZE;
				// 移動時切換map在screen上的座標 從而達到screen或是鏡頭跟著玩家的視覺效果
				m->SetSX(m->GetSX() - STEP_SIZE); 
			}
		}
		if (isMovingRight)
		{
			// 更改方向旗標
			direction = 4;

			facingDirection->OnMove();
			facingDirection = &aniMoveRight;
			if (m->IsEmpty(bx + width +STEP_SIZE, by + 64) && m->IsEmpty(bx + width + STEP_SIZE, by + 80))
			{
				x += STEP_SIZE;
				bx += STEP_SIZE;
				ex += STEP_SIZE;
				m->SetSX(m->GetSX() + STEP_SIZE);
			}
		}
		if (isMovingUp)
		{
			// 更改方向旗標
			direction = 1;

			facingDirection->OnMove();
			facingDirection = &aniMoveUp;
			if (m->IsEmpty(bx , by + 64 - STEP_SIZE) && m->IsEmpty(bx + width , by + 64 - STEP_SIZE))
			{
				y -= STEP_SIZE;
				by -= STEP_SIZE;
				ey -= STEP_SIZE;
				m->SetSY(m->GetSY() - STEP_SIZE);
			}
		}
		if (isMovingDown)
		{
			// 更改方向旗標
			direction = 2;

			facingDirection->OnMove();
			facingDirection = &aniMoveDown;
			if (m->IsEmpty(bx, by + 80 + STEP_SIZE) && m->IsEmpty(bx + width, by + 80 + STEP_SIZE))
			{
				y += STEP_SIZE;
				by += STEP_SIZE;
				ey += STEP_SIZE;
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

			if (isUsingTool)
				facingDirection->OnMove();
			facingDirection->OnShow();
		}
	}

	void CPlayer::OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd)
	{
		const char KEY_A = 0x41;  // keyboard A鍵
		const char KEY_Q = 0x51; // keyboard Q鍵

		// 傳入事件觸發
		mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd);

		//
		// 按Q切換玩家手上拿的工具
		//
		if (key == KEY_Q)
		{
			// 切換工具選擇器
			toolSelector++;
			if (toolSelector < 0)
				toolSelector = tool.size() - 1;
			else if (toolSelector >= tool.size())
				toolSelector = 0;

			// 看看選擇了哪個 來切換玩家的圖
			switch (toolSelector)
			{
			case 0:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_0;
				break;
			case 1:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_1;
				break;
			case 2:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_2;
				break;
			case 3:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_3;
				break;
			case 4:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_4;
				break;
			case 5:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_5;
				break;
			default:
				break;
			}
		}
		
		//
		// 按A執行工具動作與執行農務事件
		//
		if (key == KEY_A)
		{
			isUsingTool = true;

			// 看看現在玩家拿甚麼工具
			switch (toolSelector)
			{
			case 0: // FIXME
				isUsingTool = false;
				facingDirection = facingDirection;
				break;
			case 1:
				lastFacingDirection = facingDirection;
				// 根據方向來決定用哪一邊的動畫
				if (direction == 1) facingDirection = &aniUseTool_1_back;
				else if (direction == 2) facingDirection = &aniUseTool_1_front;
				else if (direction == 3) facingDirection = &aniUseTool_1_left;
				else facingDirection = &aniUseTool_1_right;
				break;
			case 2:
				lastFacingDirection = facingDirection;
				// 根據方向來決定用哪一邊的動畫
				if (direction == 1) facingDirection = &aniUseTool_2_back;
				else if (direction == 2) facingDirection = &aniUseTool_2_front;
				else if (direction == 3) facingDirection = &aniUseTool_2_left;
				else facingDirection = &aniUseTool_2_right;
				break;
			case 3:
				lastFacingDirection = facingDirection;
				// 根據方向來決定用哪一邊的動畫
				if (direction == 1) facingDirection = &aniUseTool_3_back;
				else if (direction == 2) facingDirection = &aniUseTool_3_front;
				else if (direction == 3) facingDirection = &aniUseTool_3_left;
				else facingDirection = &aniUseTool_3_right;
				break;
			case 4:
				lastFacingDirection = facingDirection;
				// 播撒種子動作只有一種面向
				facingDirection = &aniUseTool_4;
				break;
			case 5:
				lastFacingDirection = facingDirection;
				// 根據方向來決定用哪一邊的動畫
				if (direction == 1) facingDirection = &aniUseTool_5_back;
				else if (direction == 2) facingDirection = &aniUseTool_5_front;
				else if (direction == 3) facingDirection = &aniUseTool_5_left;
				else facingDirection = &aniUseTool_5_right;
				break;
			default:
				break;
			}
		}
	}

	void CPlayer::OnKeyUp(UINT key, CMapManager * mm, CGameDialog * gd)
	{
		const char KEY_A = 0x41;  // keyboard A鍵
		const char KEY_Q = 0x51; // keyboard Q鍵

		// 放開Q鍵 變回原來的姿勢
		if (key == KEY_Q)
		{
			//Sleep(300);
			facingDirection = lastFacingDirection;
		}

		// 放開A鍵 
		if (key == KEY_A)
		{
			isUsingTool = false;
			facingDirection = lastFacingDirection;
		}


	}
}