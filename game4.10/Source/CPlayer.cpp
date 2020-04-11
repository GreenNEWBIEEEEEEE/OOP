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
		bx = x + 64; by = y + 40;
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

		tool.push_back(0); // 手
		tool.push_back(1); // 斧頭
		tool.push_back(2); // 槌子
		tool.push_back(3); // 鋤頭
		tool.push_back(4); // 種子袋
		tool.push_back(5); // 鐮刀
		tool.push_back(6); // 澆水器
		toolSelector = 1;  // 一開始是手

		// 設定 使用工具動作 的動畫每幀切換時間間隔
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

		aniUseTool_6_front.SetDelayCount(10);
		aniUseTool_6_back.SetDelayCount(10);
		aniUseTool_6_left.SetDelayCount(10);
		aniUseTool_6_right.SetDelayCount(10);
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
		/// 載入上下左右移動的動畫
		/// 
		{
			aniRadishMoveLeft.AddBitmap(IDB_PeopleRadish_left01, RGB(255, 255, 255));
			aniRadishMoveLeft.AddBitmap(IDB_PeopleRadish_left02, RGB(255, 255, 255));
			aniRadishMoveLeft.AddBitmap(IDB_PeopleRadish_left03, RGB(255, 255, 255));

			aniRadishMoveRight.AddBitmap(IDB_PeopleRadish_right01, RGB(255, 255, 255));
			aniRadishMoveRight.AddBitmap(IDB_PeopleRadish_right02, RGB(255, 255, 255));
			aniRadishMoveRight.AddBitmap(IDB_PeopleRadish_right03, RGB(255, 255, 255));

			aniRadishMoveUp.AddBitmap(IDB_PeopleRadish_back01, RGB(255, 255, 255));
			aniRadishMoveUp.AddBitmap(IDB_PeopleRadish_back02, RGB(255, 255, 255));
			aniRadishMoveUp.AddBitmap(IDB_PeopleRadish_back03, RGB(255, 255, 255));

			aniRadishMoveDown.AddBitmap(IDB_PeopleRadish_front01, RGB(255, 255, 255));
			aniRadishMoveDown.AddBitmap(IDB_PeopleRadish_front02, RGB(255, 255, 255));
			aniRadishMoveDown.AddBitmap(IDB_PeopleRadish_front03, RGB(255, 255, 255));
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
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		}
		// 槌子
		{
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
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
		// 澆水器
		{
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255,255,255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
		}

		///
		/// 載入使用工具的動畫
		///
		// 手(Hand)
		{

		}
		// 斧頭(Axe)
		{
			aniUseTool_1_back.AddBitmap(IDB_UseToolAxe_Back_01, RGB(255, 255, 255));
			aniUseTool_1_back.AddBitmap(IDB_UseToolAxe_Back_02, RGB(255, 255, 255));

			aniUseTool_1_front.AddBitmap(IDB_UseToolAxe_Front_01, RGB(255, 255, 255));
			aniUseTool_1_front.AddBitmap(IDB_UseToolAxe_Front_02, RGB(255, 255, 255));
			aniUseTool_1_front.AddBitmap(IDB_UseToolAxe_Front_03, RGB(255, 255, 255));

			aniUseTool_1_left.AddBitmap(IDB_UseToolAxe_Left_01, RGB(255, 255, 255));
			aniUseTool_1_left.AddBitmap(IDB_UseToolAxe_Left_02, RGB(255, 255, 255));
			aniUseTool_1_left.AddBitmap(IDB_UseToolAxe_Left_03, RGB(255, 255, 255));

			aniUseTool_1_right.AddBitmap(IDB_UseToolAxe_Right_01, RGB(255, 255, 255));
			aniUseTool_1_right.AddBitmap(IDB_UseToolAxe_Right_02, RGB(255, 255, 255));
			aniUseTool_1_right.AddBitmap(IDB_UseToolAxe_Right_03, RGB(255, 255, 255));

		}
		// 槌子(Hammer)
		{
			aniUseTool_2_back.AddBitmap(IDB_UseToolHammer_Back_01, RGB(255, 255, 255));
			aniUseTool_2_back.AddBitmap(IDB_UseToolHammer_Back_02, RGB(255, 255, 255));

			aniUseTool_2_front.AddBitmap(IDB_UseToolHammer_Front_01, RGB(255, 255, 255));
			aniUseTool_2_front.AddBitmap(IDB_UseToolHammer_Front_02, RGB(255, 255, 255));
			aniUseTool_2_front.AddBitmap(IDB_UseToolHammer_Front_03, RGB(255, 255, 255));

			aniUseTool_2_left.AddBitmap(IDB_UseToolHammer_Left_01, RGB(255, 255, 255));
			aniUseTool_2_left.AddBitmap(IDB_UseToolHammer_Left_02, RGB(255, 255, 255));
			aniUseTool_2_left.AddBitmap(IDB_UseToolHammer_Left_03, RGB(255, 255, 255));

			aniUseTool_2_right.AddBitmap(IDB_UseToolHammer_Right_01, RGB(255, 255, 255));
			aniUseTool_2_right.AddBitmap(IDB_UseToolHammer_Right_02, RGB(255, 255, 255));
			aniUseTool_2_right.AddBitmap(IDB_UseToolHammer_Right_03, RGB(255, 255, 255));
		}
		// 鋤頭(Hoe)
		{
			aniUseTool_3_back.AddBitmap(IDB_UseToolHoe_Back_01, RGB(255, 255, 255));
			aniUseTool_3_back.AddBitmap(IDB_UseToolHoe_Back_02, RGB(255, 255, 255));

			aniUseTool_3_front.AddBitmap(IDB_UseToolHoe_Front_01, RGB(255, 255, 255));
			aniUseTool_3_front.AddBitmap(IDB_UseToolHoe_Front_02, RGB(255, 255, 255));
			aniUseTool_3_front.AddBitmap(IDB_UseToolHoe_Front_03, RGB(255, 255, 255));

			aniUseTool_3_left.AddBitmap(IDB_UseToolHoe_Left_01, RGB(255, 255, 255));
			aniUseTool_3_left.AddBitmap(IDB_UseToolHoe_Left_02, RGB(255, 255, 255));
			aniUseTool_3_left.AddBitmap(IDB_UseToolHoe_Left_03, RGB(255, 255, 255));
			aniUseTool_3_left.AddBitmap(IDB_UseToolHoe_Left_04, RGB(255, 255, 255));

			aniUseTool_3_right.AddBitmap(IDB_UseToolHoe_Right_01, RGB(255, 255, 255));
			aniUseTool_3_right.AddBitmap(IDB_UseToolHoe_Right_02, RGB(255, 255, 255));
			aniUseTool_3_right.AddBitmap(IDB_UseToolHoe_Right_03, RGB(255, 255, 255));
			aniUseTool_3_right.AddBitmap(IDB_UseToolHoe_Right_04, RGB(255, 255, 255));

		}
		// 種子袋(Seed)
		{
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed01, RGB(255,255,255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed02, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed03, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed04, RGB(255, 255, 255));
		}
		// 鐮刀(Sickle)
		{
			aniUseTool_5_back.AddBitmap(IDB_UseToolSickle_Back_01, RGB(255, 255, 255));
			aniUseTool_5_back.AddBitmap(IDB_UseToolSickle_Back_02, RGB(255, 255, 255));
			aniUseTool_5_back.AddBitmap(IDB_UseToolSickle_Back_03, RGB(255, 255, 255));
			aniUseTool_5_back.AddBitmap(IDB_UseToolSickle_Back_04, RGB(255, 255, 255));

			aniUseTool_5_front.AddBitmap(IDB_UseToolSickle_Front_01, RGB(255, 255, 255));
			aniUseTool_5_front.AddBitmap(IDB_UseToolSickle_Front_02, RGB(255, 255, 255));
			aniUseTool_5_front.AddBitmap(IDB_UseToolSickle_Front_03, RGB(255, 255, 255));
			aniUseTool_5_front.AddBitmap(IDB_UseToolSickle_Front_04, RGB(255, 255, 255));

			aniUseTool_5_left.AddBitmap(IDB_UseToolSickle_Left_01, RGB(255, 255, 255));
			aniUseTool_5_left.AddBitmap(IDB_UseToolSickle_Left_02, RGB(255, 255, 255));
			aniUseTool_5_left.AddBitmap(IDB_UseToolSickle_Left_03, RGB(255, 255, 255));
			aniUseTool_5_left.AddBitmap(IDB_UseToolSickle_Left_04, RGB(255, 255, 255));

			aniUseTool_5_right.AddBitmap(IDB_UseToolSickle_Right_01, RGB(255, 255, 255));
			aniUseTool_5_right.AddBitmap(IDB_UseToolSickle_Right_02, RGB(255, 255, 255));
			aniUseTool_5_right.AddBitmap(IDB_UseToolSickle_Right_03, RGB(255, 255, 255));
			aniUseTool_5_right.AddBitmap(IDB_UseToolSickle_Right_04, RGB(255, 255, 255));

		}
		// 澆水器(WateringCan)
		{
			aniUseTool_6_back.AddBitmap(IDB_UseToolWateringCan_Back_01, RGB(255, 255, 255));
			aniUseTool_6_back.AddBitmap(IDB_UseToolWateringCan_Back_02, RGB(255, 255, 255));

			aniUseTool_6_front.AddBitmap(IDB_UseToolWateringCan_Front_01, RGB(255, 255, 255));
			aniUseTool_6_front.AddBitmap(IDB_UseToolWateringCan_Front_02, RGB(255, 255, 255));

			aniUseTool_6_left.AddBitmap(IDB_UseToolWateringCan_Left_01, RGB(255, 255, 255));
			aniUseTool_6_left.AddBitmap(IDB_UseToolWateringCan_Left_02, RGB(255, 255, 255));
			
			aniUseTool_6_right.AddBitmap(IDB_UseToolWateringCan_Right_01, RGB(255, 255, 255));
			aniUseTool_6_right.AddBitmap(IDB_UseToolWateringCan_Right_02, RGB(255, 255, 255));
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
		bx = x + 64;
	}

	void CPlayer::SetY(int y)
	{
		this->lastY = this->y;
		this->y = y;
		by = y + 40;
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

	int CPlayer::GetBodyX() const
	{
		return bx;
	}

	int CPlayer::GetBodyY() const
	{
		return by;
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

	int CPlayer::GetCurrentTool() const
	{
		return toolSelector;
	}
	
	void CPlayer::ChangeMoveState(int mapInfoID)
	{
		switch (mapInfoID)
		{
		case 9:
			currentMoveState = RadishMove;
			break;
		default:
			currentMoveState = NormalMove;
			break;
		}
	}

	// OnMove
	// 需要傳入m 透過m回傳現在位置的屬性(EX: 是否是障礙物...等)
	void CPlayer::OnMove(CGameMap* m)
	{
		
		
		if (currentMoveState == RadishMove)
			Move(m, &aniRadishMoveUp, &aniRadishMoveDown, &aniRadishMoveLeft, &aniRadishMoveRight);
		else if (currentMoveState == NormalMove)
			Move(m, &aniMoveUp, &aniMoveDown, &aniMoveLeft, &aniMoveRight);
	}

	void CPlayer::Move(CGameMap* m, CAnimation* moveUp, CAnimation* moveDown, CAnimation* moveLeft, CAnimation* moveRight)
	{
		// 每一步移動量
		const int STEP_SIZE = 5;
		if (isMovingLeft)
		{
			// 更改方向旗標
			lastDirection = direction;
			direction = 3;

			// 當按下方向鍵時可先切換面向的方向, 不管之後是否有真的要移動
			facingDirection->OnMove();
			facingDirection = moveLeft;
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
		else if (isMovingRight)
		{
			// 更改方向旗標
			lastDirection = direction;
			direction = 4;

			facingDirection->OnMove();
			facingDirection = moveRight;
			if (m->IsEmpty(bx + width + STEP_SIZE, by + 64) && m->IsEmpty(bx + width + STEP_SIZE, by + 80))
			{
				x += STEP_SIZE;
				bx += STEP_SIZE;
				ex += STEP_SIZE;
				m->SetSX(m->GetSX() + STEP_SIZE);
			}
		}
		else if (isMovingUp)
		{
			// 更改方向旗標
			lastDirection = direction;
			direction = 1;

			facingDirection->OnMove();
			facingDirection = moveUp;
			if (m->IsEmpty(bx, by + 64 - STEP_SIZE) && m->IsEmpty(bx + width, by + 64 - STEP_SIZE))
			{
				y -= STEP_SIZE;
				by -= STEP_SIZE;
				ey -= STEP_SIZE;
				m->SetSY(m->GetSY() - STEP_SIZE);
			}
		}
		else if (isMovingDown)
		{
			// 更改方向旗標
			lastDirection = direction;
			direction = 2;

			facingDirection->OnMove();
			facingDirection = moveDown;
			if (m->IsEmpty(bx, by + 80 + STEP_SIZE) && m->IsEmpty(bx + width, by + 80 + STEP_SIZE))
			{
				y += STEP_SIZE;
				by += STEP_SIZE;
				ey += STEP_SIZE;
				m->SetSY(m->GetSY() + STEP_SIZE);
			}
		}
		else if (isUsingTool) {
			if (facingDirection->IsFinalBitmap()) {
				facingDirection->Reset();
				isUsingTool = false;
				direction = lastDirection;
				facingDirection = lastFacingDirection;
			}
			else
				facingDirection->OnMove();
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
		const char KEY_A = 0x41;  // keyboard A鍵
		const char KEY_W = 'W'; // keyboard Q鍵

		//
		// 按W切換玩家手上拿的工具
		//
		if (key == KEY_W)
		{
			// 切換工具選擇器
			toolSelector++;
			if (toolSelector < 0) toolSelector = tool.size() - 1;
			else if (toolSelector >= tool.size()) toolSelector = 0;

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
			case 6:
				lastFacingDirection = facingDirection;
				facingDirection = &aniChangeTool_6;
				break;
			default:
				break;
			}
		}
		//
		// 按A使用工具動作的動畫與執行農務事件
		//
		else if (key == KEY_A)
		{
			// 使用工具動畫的旗標
			isUsingTool = true;

			// 看看現在玩家拿甚麼工具 顯示動畫
			switch (toolSelector)
			{
			case 0: // FIXME
				isUsingTool = false;
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
			case 6:
				// 根據方向來決定用哪一邊的動畫
				if (direction == 1) facingDirection = &aniUseTool_6_back;
				else if (direction == 2) facingDirection = &aniUseTool_6_front;
				else if (direction == 3) facingDirection = &aniUseTool_6_left;
				else facingDirection = &aniUseTool_6_right;
				break;
			default:
				break;
			}
			
			// 傳入農務事件觸發
			mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd);
		}
		else
		{
			// 傳入其他事件觸發
			mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd);
		}
	}

	CPlayer::MoveState CPlayer::GetCurrentMoveState()
	{
		return currentMoveState;
	}

	void CPlayer::OnKeyUp(UINT key, CMapManager * mm, CGameDialog * gd)
	{
		const char KEY_A = 0x41;  // keyboard A鍵
		const char KEY_W = 'W'; // keyboard Q鍵

		// 放開Q鍵 變回原來的姿勢
		if (key == KEY_W)
		{
			Sleep(200);
			facingDirection = lastFacingDirection;
		}

	
	}
}