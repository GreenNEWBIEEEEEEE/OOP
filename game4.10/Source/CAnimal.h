#pragma once
#include "CGameObject.h"
namespace game_framework {
	class CGameObject;
	class CGameMap;
	class CTimer;
	class CAnimal : public CGameObject
	{
	public:
		CAnimal();
		~CAnimal();
		enum class Direction{
			Up,
			Down,
			Left,
			Right
		};

		enum class Status {			// ���d���A
			Produce,				// �i�Ͳ�
			Hungry,					// �p�G�HWaitingForFeed��F����(NewDay)�A�N�|������Hungry
			NoProduce    			// �L�k�Ͳ�
		};

	

		virtual void LoadBitmap() = 0;

		virtual void OnMove(CGameMap* m, vector<CGameObject*>* obj) = 0;
		virtual void OnShow(CGameMap* m) = 0;
		Status GetCurrentStatus();
		void ChangeStatus(Status status);
		void SetMap(CGameMap* map);   // �]�w����or����or�Ϫ٦a��
		void SetTimer(CTimer* timer);
	protected:
		CTimer* timer;
		CGameMap* map; // ���� or ���� or �Ϫ�

		Direction currentDirection;
		Direction lastDirection;
		Status currentStatus;

		CAnimation moveLeft;
		CAnimation moveRight;
		CAnimation moveUp;
		CAnimation moveDown;
		CAnimation* currentMove;

	};
}

