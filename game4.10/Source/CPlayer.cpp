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
		width = 53; height = 64;
		x = lastX = 300; y = lastY = 200;
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

		tool.push_back(0); 
		tool.push_back(1);
		tool.push_back(2);
		tool.push_back(3);
		toolSelector = 0;
	}

	CPlayer::~CPlayer() {
		facingDirection = nullptr;
	}

	void CPlayer::LoadBitmap()
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

		aniChangeTool_0.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		aniChangeTool_0.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		aniChangeTool_0.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		aniChangeTool_0.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		aniChangeTool_0.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));

		aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		aniChangeTool_1.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));

		aniChangeTool_2.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		aniChangeTool_2.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		aniChangeTool_2.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		aniChangeTool_2.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		aniChangeTool_2.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));

		aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));

		aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));

		aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));

		/*
		aniPlantLeft.AddBitmap(IDB_PLAYER01_PLANTLEFT1, RGB(255,255,255));
		aniPlantLeft.AddBitmap(IDB_PLAYER01_PLANTLEFT2, RGB(255, 255, 255));
		aniPlantLeft.AddBitmap(IDB_PLAYER01_PLANTLEFT3, RGB(255, 255, 255));

		aniPlantRight.AddBitmap(IDB_PLAYER01_PLANTRIGHT1, RGB(255, 255, 255));
		aniPlantRight.AddBitmap(IDB_PLAYER01_PLANTRIGHT2, RGB(255, 255, 255));
		aniPlantRight.AddBitmap(IDB_PLAYER01_PLANTRIGHT3, RGB(255, 255, 255));

		aniPlantUp.AddBitmap(IDB_PLAYER01_PLANTUP1, RGB(255, 255, 255));
		aniPlantUp.AddBitmap(IDB_PLAYER01_PLANTUP2, RGB(255, 255, 255));
		aniPlantUp.AddBitmap(IDB_PLAYER01_PLANTUP3, RGB(255, 255, 255));

		aniPlantDown.AddBitmap(IDB_PLAYER01_PLANTDOWN1, RGB(255, 255, 255));
		aniPlantDown.AddBitmap(IDB_PLAYER01_PLANTDOWN2, RGB(255, 255, 255));
		aniPlantDown.AddBitmap(IDB_PLAYER01_PLANTDOWN3, RGB(255, 255, 255));
		
		aniChangeTool_0.AddBitmap(IDB_PLAYER01_CHANGETOOL_0_1, RGB(255, 255, 255));
		*/
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
	// �ݭn�ǤJm �z�Lm�^�ǲ{�b��m���ݩ�(EX: �O�_�O��ê��...��)
	void CPlayer::OnMove(CGameMap* m)
	{
		// �C�@�B���ʶq
		const int STEP_SIZE = 5;
		
		if (isMovingLeft)
		{
			// ����U��V��ɥi���������V����V, ���ޤ���O�_���u���n����
			facingDirection->OnMove();
			facingDirection = &aniMoveLeft;
			// ������ê�� �� ���i��W�h���a�Ϯ�l
			// �ثe�]�w�� ���a���Ϥ��O��ӫ�����l(80*120), ��Ӯ�l�O80*60
			// �n�������O���a�U�b��, �p����ı�W�ݰ_�Ӥ~���|��a
			if (m->IsEmpty(x - STEP_SIZE, y + 80) && m->IsEmpty(x - STEP_SIZE, y + 120))
			{
				x -= STEP_SIZE;
				// ���ʮɤ���map�bscreen�W���y�� �q�ӹF��screen�άO���Y��۪��a����ı�ĪG
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
			// �e�X��e���V����V���ʵe
			// ��m�p��X���a���a���I�y��(x,y) �b screen�W���y�� �]���̲׬O�n�bscreen�W�e
			facingDirection->SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			facingDirection->OnShow();
		}


	}

	void CPlayer::OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd)
	{
		const char KEY_A = 0x41;  // keyboard A��
		const char KEY_Q = 0x51; // keyboard Q��
		// �ǤJ�ƥ�Ĳ�o
		mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd);

		if (key == KEY_Q)
		{
			toolSelector++;
			if (toolSelector < 0)
				toolSelector = tool.size() - 1;
			else if (toolSelector >= tool.size())
				toolSelector = 0;

			switch (toolSelector)
			{
			case 0:
				facingDirection = &aniChangeTool_0;
				break;
			case 1:
				facingDirection = &aniChangeTool_1;
				break;
			case 2:
				facingDirection = &aniChangeTool_2;
				break;
			case 3:
				facingDirection = &aniChangeTool_3;
				break;
			case 4:
				facingDirection = &aniChangeTool_4;
				break;
			case 5:
				facingDirection = &aniChangeTool_5;
				break;
			default:
				break;
			}
		}
		if (key == KEY_A)
		{
			
		}




	}
}