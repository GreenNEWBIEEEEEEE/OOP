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
				// �e�X��e���V����V���ʵe
				// ��m�p��X���a���a���I�y��(x,y) �b screen�W���y�� �]���̲׬O�n�bscreen�W�e
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
			if (m->IsEmpty(bx - STEP_SIZE, by + 64) && m->IsEmpty(bx - STEP_SIZE, by + 80) && !DetectCollision(obj, -STEP_SIZE, 0))
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
			if (m->IsEmpty(bx + width + STEP_SIZE, by + 64) && m->IsEmpty(bx + width + STEP_SIZE, by + 80) && !DetectCollision(obj, STEP_SIZE, 0))
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
			if (m->IsEmpty(bx + 10, by + 64 - STEP_SIZE) && m->IsEmpty(bx - 10 + width, by + 64 - STEP_SIZE) && !DetectCollision(obj, 0, -STEP_SIZE))
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

