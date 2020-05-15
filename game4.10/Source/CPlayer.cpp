#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameDialog.h"
#include "CMapManager.h"
#include "CTool.h"
#include "CToolHand.h"
#include "CToolAxe.h"
#include "CToolHammer.h"
#include "CToolHoe.h"
#include "CToolSeed.h"
#include "CToolSickle.h"
#include "CToolWaterer.h"
#include "CShopMenu.h"
#include "CAnimal.h"
#include "CGameObject.h"
namespace game_framework {
	CPlayer::CPlayer() :
		aniMoveLeft(3),
		aniMoveRight(3),
		aniMoveUp(3),
		aniMoveDown(3)
	{
		width = 64; height = 80;
		x = lastX = 600; y = lastY = 300;
		bx = x + 64; by = y + 40;
		facingDirection = &aniMoveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;

		backpack.push_back(new CToolHand(0, 1)); // ��
		backpack.push_back(new CToolAxe(1, 1)); // ���Y
		backpack.push_back(new CToolHammer(2, 1)); // �l�l
		backpack.push_back(new CToolHoe(3, 1)); // �S�Y
		backpack.push_back(new CToolSeed(4, 6)); // �ؤl�U
		backpack.push_back(new CToolSickle(5, 1)); // �I�M
		backpack.push_back(new CToolWaterer(6, 1)); // �����
		toolSelector = 0;  // �@�}�l�O��

		// �]�w �ϥΤu��ʧ@ ���ʵe�C�V�����ɶ����j
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

		// �]�w�����B��O��
		money = 100;
		healthPoint = 100;
	}

	CPlayer::~CPlayer() {
		facingDirection = nullptr;
		for (vector<CTool*>::iterator i = backpack.begin(); i != backpack.end(); i++)
			delete *i;
	}

	void CPlayer::LoadBitmap()
	{
		///
		/// ���J�W�U���k���ʪ��ʵe
		/// 
		for (unsigned int i = 0; i < backpack.size(); i++)
		{
			backpack[i]->LoadBitmap();
		}
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
		/// ���J�W�U���k���ʪ��ʵe
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
		/// ���J�����u�㪺�ʵe
		/// �аѾ\�U�Ӥu�㪺�s��
		///
		// ��
		{
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
			aniChangeTool_0.AddBitmap(IDB_ChangeToolHand, RGB(255, 255, 255));
		}
		// ���Y
		{
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
			aniChangeTool_1.AddBitmap(IDB_ChangeToolAxe, RGB(255, 255, 255));
		}
		// �l�l
		{
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
			aniChangeTool_2.AddBitmap(IDB_ChangeToolHammer, RGB(255, 255, 255));
		}
		// �S�Y
		{
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
			aniChangeTool_3.AddBitmap(IDB_ChangeToolHoe, RGB(255, 255, 255));
		}
		// �ؤl�U
		{
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
			aniChangeTool_4.AddBitmap(IDB_ChangeToolSeed, RGB(255, 255, 255));
		}
		// �I�M
		{
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
			aniChangeTool_5.AddBitmap(IDB_ChangeToolSickle, RGB(255, 255, 255));
		}
		// �����
		{
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255,255,255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
			aniChangeTool_6.AddBitmap(IDB_ChangeToolWateringCan, RGB(255, 255, 255));
		}

		///
		/// ���J�ϥΤu�㪺�ʵe
		///
		// ��(Hand)
		{

		}
		// ���Y(Axe)
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
		// �l�l(Hammer)
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
		// �S�Y(Hoe)
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
		// �ؤl�U(Seed)
		{
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed01, RGB(255,255,255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed02, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed03, RGB(255, 255, 255));
			aniUseTool_4.AddBitmap(IDB_UseToolPlantSeed04, RGB(255, 255, 255));
		}
		// �I�M(Sickle)
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
		// �����(WateringCan)
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

	void CPlayer::SetToolSelector(unsigned int select)
	{
		toolSelector = select;
	}

	void CPlayer::DecreaseMoney(int money)
	{
		if (money <= this->money)
		{
			this->money -= money;
		}
	}

	int CPlayer::GetDirection() const
	{
		return direction;
	}

	int CPlayer::GetCurrentTool() const
	{
		return toolSelector;
	}

	int CPlayer::GetMoney() const
	{
		return money;
	}

	vector<CTool*>* CPlayer::GetBackpack()
	{
		return &backpack;
	}

	void CPlayer::ChangeMoveState(MoveState state)
	{
		currentMoveState = state;
	}

	// OnMove
	// �ݭn�ǤJm �z�Lm�^�ǲ{�b��m���ݩ�(EX: �O�_�O��ê��...��)
	void CPlayer::OnMove(CGameMap* m, vector<CGameObject*>* obj)
	{
		if (currentMoveState == RadishMove)
			Move(m, &aniRadishMoveUp, &aniRadishMoveDown, &aniRadishMoveLeft, &aniRadishMoveRight, obj);
		else if (currentMoveState == NormalMove)
			Move(m, &aniMoveUp, &aniMoveDown, &aniMoveLeft, &aniMoveRight, obj);
	}

	void CPlayer::Move(CGameMap* m, CAnimation* moveUp, CAnimation* moveDown, CAnimation* moveLeft, CAnimation* moveRight, vector<CGameObject*>* obj)
	{
		// �C�@�B���ʶq
		if (isMovingLeft)
		{
			// ����V�X��
			lastDirection = direction;
			direction = 3;

			// ����U��V��ɥi���������V����V, ���ޤ���O�_���u���n����
			facingDirection->OnMove();
			facingDirection = moveLeft;
			// ������ê�� �� ���i��W�h���a�Ϯ�l
			// �ثe�]�w�� ���a���Ϥ��O64*80
			// �n�������O���a�U�b��, �p����ı�W�ݰ_�Ӥ~���|��a
			if (m->IsEmpty(bx - STEP_SIZE, by + 64) && m->IsEmpty(bx - STEP_SIZE, by + 80) && !DetectCollision(obj, -STEP_SIZE, 0))
			{
				x -= STEP_SIZE;
				bx -= STEP_SIZE;
				ex -= STEP_SIZE;
				// ���ʮɤ���map�bscreen�W���y�� �q�ӹF��screen�άO���Y��۪��a����ı�ĪG
				m->SetSX(m->GetSX() - STEP_SIZE);
			}
		}
		else if (isMovingRight)
		{
			// ����V�X��
			lastDirection = direction;
			direction = 4;

			facingDirection->OnMove();
			facingDirection = moveRight;
			if (m->IsEmpty(bx + width + STEP_SIZE, by + 64) && m->IsEmpty(bx + width + STEP_SIZE, by + 80) && !DetectCollision(obj, STEP_SIZE, 0))
			{
				x += STEP_SIZE;
				bx += STEP_SIZE;
				ex += STEP_SIZE;
				m->SetSX(m->GetSX() + STEP_SIZE);
			}
		}
		else if (isMovingUp)
		{
			// ����V�X��
			lastDirection = direction;
			direction = 1;

			facingDirection->OnMove();
			facingDirection = moveUp;
			if (m->IsEmpty(bx + 10, by + 64 - STEP_SIZE) && m->IsEmpty(bx - 10 + width, by + 64 - STEP_SIZE) && !DetectCollision(obj, 0, -STEP_SIZE))
			{
				y -= STEP_SIZE;
				by -= STEP_SIZE;
				ey -= STEP_SIZE;
				m->SetSY(m->GetSY() - STEP_SIZE);
			}
		}
		else if (isMovingDown)
		{
			// ����V�X��
			lastDirection = direction;
			direction = 2;

			facingDirection->OnMove();
			facingDirection = moveDown;
			// bx+/-5 �e�׳]�p�@�I
			if (m->IsEmpty(bx + 10, by + 80 + STEP_SIZE) && m->IsEmpty(bx - 10 + width, by + 80 + STEP_SIZE) && !DetectCollision(obj, 0, STEP_SIZE))
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
			// �e�X��e���V����V���ʵe
			// ��m�p��X���a���a���I�y��(x,y) �b screen�W���y�� �]���̲׬O�n�bscreen�W�e
			facingDirection->SetTopLeft(m->ScreenX(x), m->ScreenY(y));

		
			facingDirection->OnShow();
		}
	}


	void CPlayer::OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd, CShopMenu *sm, vector<CGameObject*>* obj)
	{
		const char KEY_A = 0x41;  // keyboard A��
		const char KEY_W = 'W'; // keyboard Q��
		const char KEY_B = 'B';  // keyboard B��

		//
		// ��W�������a��W�����u��
		//
		if (key == KEY_W)
		{
			// �����u���ܾ�
			toolSelector++;
			if (toolSelector < 0) toolSelector = backpack.size() - 1;
			else if (toolSelector >= backpack.size()) toolSelector = 0;

			// �ݬݿ�ܤF���� �Ӥ������a����
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
		// ��A�ϥΤu��ʧ@���ʵe�P����A�Ȩƥ�
		//
		else if (key == KEY_A)
		{
			// �ϥΤu��ʵe���X��
			isUsingTool = true;

			// �ݬݲ{�b���a���ƻ�u�� ��ܰʵe
			switch (toolSelector)
			{
			case 0: // FIXME
				isUsingTool = false;
				break;
			case 1:
				lastFacingDirection = facingDirection;
				// �ھڤ�V�ӨM�w�έ��@�䪺�ʵe
				if (direction == 1) facingDirection = &aniUseTool_1_back;
				else if (direction == 2) facingDirection = &aniUseTool_1_front;
				else if (direction == 3) facingDirection = &aniUseTool_1_left;
				else facingDirection = &aniUseTool_1_right;
				break;
			case 2:
				lastFacingDirection = facingDirection;
				// �ھڤ�V�ӨM�w�έ��@�䪺�ʵe
				if (direction == 1) facingDirection = &aniUseTool_2_back;
				else if (direction == 2) facingDirection = &aniUseTool_2_front;
				else if (direction == 3) facingDirection = &aniUseTool_2_left;
				else facingDirection = &aniUseTool_2_right;
				break;
			case 3:
				lastFacingDirection = facingDirection;
				// �ھڤ�V�ӨM�w�έ��@�䪺�ʵe
				if (direction == 1) facingDirection = &aniUseTool_3_back;
				else if (direction == 2) facingDirection = &aniUseTool_3_front;
				else if (direction == 3) facingDirection = &aniUseTool_3_left;
				else facingDirection = &aniUseTool_3_right;
				break;
			case 4:
				lastFacingDirection = facingDirection;
				// �����ؤl�ʧ@�u���@�ح��V
				facingDirection = &aniUseTool_4;
				break;
			case 5:
				lastFacingDirection = facingDirection;
				// �ھڤ�V�ӨM�w�έ��@�䪺�ʵe
				if (direction == 1) facingDirection = &aniUseTool_5_back;
				else if (direction == 2) facingDirection = &aniUseTool_5_front;
				else if (direction == 3) facingDirection = &aniUseTool_5_left;
				else facingDirection = &aniUseTool_5_right;
				break;
			case 6:
				// �ھڤ�V�ӨM�w�έ��@�䪺�ʵe
				if (direction == 1) facingDirection = &aniUseTool_6_back;
				else if (direction == 2) facingDirection = &aniUseTool_6_front;
				else if (direction == 3) facingDirection = &aniUseTool_6_left;
				else facingDirection = &aniUseTool_6_right;

				break;
			default:
				break;
			}
			

			// �����u�Τ�
			if ((facingDirection == &aniMoveUp && DetectCollision(obj, 0, -STEP_SIZE)) ||
				(facingDirection == &aniMoveDown && DetectCollision(obj, 0, STEP_SIZE)) || 
				(facingDirection == &aniMoveLeft && DetectCollision(obj, -STEP_SIZE, 0)) || 
				(facingDirection == &aniMoveRight && DetectCollision(obj, STEP_SIZE, 0)) )
			{
				CAnimal* facingAnimal = GetFacingAnimal();
				if (facingAnimal->GetCurrentStatus() == CAnimal::Status::Produce)
				{
					TRACE("\nTRIGGER Animal\n");
					facingAnimal->ChangeStatus(CAnimal::Status::NoProduce);
				}
			}

			// �ǤJ�A�Ȩƥ�Ĳ�o
			// 
			if (this->currentMoveState == MoveState::NormalMove)
				mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd, sm);
			else
				this->currentMoveState = MoveState::NormalMove;
		}
		else if (key == KEY_B)
		{
			STEP_SIZE = 50;
		}
		else
		{
			// �ǤJ��L�ƥ�Ĳ�o
			mm->GetCurrentMap()->triggerMapEvents(key, this, mm, gd, sm);
		}
	}

	CPlayer::MoveState CPlayer::GetCurrentMoveState()
	{
		return currentMoveState;
	}

	void CPlayer::OnKeyUp(UINT key, CMapManager * mm, CGameDialog * gd)
	{
		const char KEY_A = 0x41;  // keyboard A��
		const char KEY_W = 'W'; // keyboard Q��
		const char KEY_B = 'B'; // keyboard B��
		// ��}Q�� �ܦ^��Ӫ�����
		if (key == KEY_W)
		{
			Sleep(200);
			facingDirection = lastFacingDirection;
		}
		else if (key == KEY_B)
		{
			STEP_SIZE = 5;
		}
	
	}
}