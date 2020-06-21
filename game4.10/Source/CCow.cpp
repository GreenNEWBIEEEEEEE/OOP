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
#include "CCow.h"

namespace game_framework {
	CCow::CCow(int positionX, int positionY)
	{
		healthPoint = MAX_HP;
		width = 64; height = 20;  // height����53 �O���F���L��ŦX�I��box
		x = lastX = resetX = positionX;
		y = lastY = resetY = positionY;
		bx = x; by = y;
		currentDirection = CAnimal::Direction::Down;
		currentStatus = CAnimal::Status::Produce;
		currentMove = &moveDown;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		STEP_SIZE = 5;
		isPickedUp = false;
	}

	CCow::~CCow()
	{
	}

	void CCow::LoadBitmap()
	{
		{
			moveLeft.AddBitmap(IDB_Cow_Left01, RGB(255, 255, 255));
			moveLeft.AddBitmap(IDB_Cow_Left02, RGB(255, 255, 255));
			moveLeft.AddBitmap(IDB_Cow_Left03, RGB(255, 255, 255));
		}

		{
			moveRight.AddBitmap(IDB_Cow_Right01, RGB(255, 255, 255));
			moveRight.AddBitmap(IDB_Cow_Right02, RGB(255, 255, 255));
			moveRight.AddBitmap(IDB_Cow_Right03, RGB(255, 255, 255));
		}

		{
			moveUp.AddBitmap(IDB_Cow_Up01, RGB(255, 255, 255));
			moveUp.AddBitmap(IDB_Cow_Up02, RGB(255, 255, 255));
			moveUp.AddBitmap(IDB_Cow_Up03, RGB(255, 255, 255));
			moveUp.AddBitmap(IDB_Cow_Up04, RGB(255, 255, 255));
		}

		{
			moveDown.AddBitmap(IDB_Cow_Down01, RGB(255, 255, 255));
			moveDown.AddBitmap(IDB_Cow_Down02, RGB(255, 255, 255));
			moveDown.AddBitmap(IDB_Cow_Down03, RGB(255, 255, 255));
		}
	}

	void CCow::Produce()
	{
		if (timer->IsNewDay())
		{
			TRACE("\nTRIGGER Milk\n");
			bool groove01 = map->GetSpecifiedElementID(2, 4) == -116;
			bool groove02 = map->GetSpecifiedElementID(3, 4) == -116;
			bool groove03 = map->GetSpecifiedElementID(4, 4) == -116;
			bool groove04 = map->GetSpecifiedElementID(5, 4) == -116;
			if (currentStatus == Status::NoProduce || currentStatus == Status::Produce || currentStatus == Status::HighProduce)
			{
				if (groove01)
				{
					map->SetSpecifiedElementID(2, 4, -109);
					if (closePoint >= 10)
						currentStatus = Status::HighProduce;
					else
						currentStatus = Status::Produce;
					closePoint += 1;
				}
				else if (groove02)
				{
					map->SetSpecifiedElementID(3, 4, -109);
					if (closePoint >= 10)
						currentStatus = Status::HighProduce;
					else
						currentStatus = Status::Produce;
					closePoint += 1;
				}
				else if (groove03)
				{
					map->SetSpecifiedElementID(4, 4, -109);
					if (closePoint >= 10)
						currentStatus = Status::HighProduce;
					else
						currentStatus = Status::Produce;
					closePoint += 1;
				}
				else if (groove04)
				{
					map->SetSpecifiedElementID(5, 4, -109);
					if (closePoint >= 10)
						currentStatus = Status::HighProduce;
					else
						currentStatus = Status::Produce;
					closePoint += 1;
				}
				else
				{
					DecreaseHP(34);
					currentStatus = Status::Hungry;
				}
			}
			else if (currentStatus == Status::Hungry)
			{
				if (groove01)
				{
					map->SetSpecifiedElementID(2, 4, -109);
					IncreaseHP(15);
				}
				else if (groove02)
				{
					map->SetSpecifiedElementID(3, 4, -109);
					IncreaseHP(15);
				}
				else if (groove03)
				{
					map->SetSpecifiedElementID(4, 4, -109);
					IncreaseHP(15);
				}
				else if (groove04)
				{
					map->SetSpecifiedElementID(5, 4, -109);
					IncreaseHP(15);
				}
				else
					DecreaseHP(34);

				if (healthPoint == 100)
				{
					currentStatus = Status::Produce;
				}
			}

		}
	}

	void CCow::OnMove(CGameMap * m, vector<CGameObject*>* obj)
	{
		Produce();
		if (map == m)
		{
			if (!isPickedUp)
			{
				onShowAndMove = true;
				collision = true;
			}

			if (onShowAndMove)
			{
				if (counter >= onMoveTimes)
				{
					int rnd = (rand() % 100);
					isMovingLeft = rnd < 10;
					isMovingRight = rnd >= 10 && rnd < 20;
					isMovingUp = rnd >= 20 && rnd < 30;
					isMovingDown = rnd >= 30 && rnd < 40;
					onMoveTimes = rand() % 6 + 5;
					//TRACE("\n TImes : %d\n", onMoveTimes);
					counter = 0;
				}

				// �C�@�B���ʶq
				if (isMovingLeft)
				{
					// ����V�X��
					lastDirection = currentDirection;
					currentDirection = CAnimal::Direction::Left;

					// ����U��V��ɥi���������V����V, ���ޤ���O�_���u���n����
					currentMove->OnMove();
					currentMove = &moveLeft;
					// ������ê�� �� ���i��W�h���a�Ϯ�l
					// �ثe�]�w�� ���a���Ϥ��O64*80
					// �n�������O���a�U�b��, �p����ı�W�ݰ_�Ӥ~���|��a
					if (m->IsEmpty(bx - STEP_SIZE, by) && 
						m->IsEmpty(bx - STEP_SIZE, by + height + 33) && 
						!DetectCollision(obj, -STEP_SIZE, 0))
					{
						x -= STEP_SIZE;
						bx -= STEP_SIZE;
						ex -= STEP_SIZE;
					}
				}
				else if (isMovingRight)
				{
					// ����V�X��
					lastDirection = currentDirection;
					currentDirection = CAnimal::Direction::Right;

					currentMove->OnMove();
					currentMove = &moveRight;
					if (m->IsEmpty(bx + width + STEP_SIZE, by) && 
						m->IsEmpty(bx + width + STEP_SIZE, by + height + 33) && 
						!DetectCollision(obj, STEP_SIZE, 0))
					{
						x += STEP_SIZE;
						bx += STEP_SIZE;
						ex += STEP_SIZE;
					}
				}
				else if (isMovingUp)
				{
					// ����V�X��
					lastDirection = currentDirection;
					currentDirection = CAnimal::Direction::Up;

					currentMove->OnMove();
					currentMove = &moveUp;
					if (m->IsEmpty(bx, by - STEP_SIZE) && 
						m->IsEmpty(bx + width, by - STEP_SIZE) && 
						!DetectCollision(obj, 0, -STEP_SIZE))
					{
						y -= STEP_SIZE;
						by -= STEP_SIZE;
						ey -= STEP_SIZE;
					}
				}
				else if (isMovingDown)
				{
					// ����V�X��
					lastDirection = currentDirection;
					currentDirection = CAnimal::Direction::Down;

					currentMove->OnMove();
					currentMove = &moveDown;
					// bx+/-5 �e�׳]�p�@�I
					if (m->IsEmpty(bx, by + height + 33 + STEP_SIZE) && 
						m->IsEmpty(bx + width, by + height + 33 + STEP_SIZE) && 
						!DetectCollision(obj, 0, STEP_SIZE))
					{
						y += STEP_SIZE;
						by += STEP_SIZE;
						ey += STEP_SIZE;
					}
				}

				counter++;
			}
		}
		else
		{
			onShowAndMove = false;
			collision = false;
		}
	}

	void CCow::OnShow(CGameMap * m)
	{
		if (map == m)
		{
			if (onShowAndMove)
			{
				if (currentMove != nullptr)
				{
					// �e�X��e���V����V���ʵe
					// ��m�p��X���a���a���I�y��(x,y) �b screen�W���y�� �]���̲׬O�n�bscreen�W�e
					currentMove->SetTopLeft(m->ScreenX(x), m->ScreenY(y));


					currentMove->OnShow();
				}
			}
		}
	}
}