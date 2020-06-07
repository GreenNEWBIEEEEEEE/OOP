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
		int GetClosePoint();
		void UnableShowAndMove();
		void EnableShowAndMove();
		void ChangeStatus(Status status);
		void SetMap(CGameMap* map);   // �]�w����or����or�Ϫ٦a��
		void SetTimer(CTimer* timer);
		void Reset();
		void SetPickUp(bool flag);
		CGameMap* GetMap();            // �^�Ǧ��ʪ����ݦa��
	protected:
		int onMoveTimes = 3; // ���F�����ʧ�[���Z�۵M�A�b���s�M�w�ʪ����ʤ�V���e�A�n�����@�w���ơA�~�୫�s�M�w��V
		int counter = 0;     // �p��onMove����
		int closePoint = 0;  // �D�H�P�ʪ����˱K��
		int resetX, resetY;
		bool onShowAndMove = true;  // �p�G���Q�H����_�Ӫ��ܡA�N����unable
		bool isPickedUp = false;
		CTimer* timer;
		CGameMap* map; // ���� or ���� or �Ϫ�

		Direction currentDirection;
		Direction lastDirection;
		Status currentStatus = Status::Produce;

		CAnimation moveLeft;
		CAnimation moveRight;
		CAnimation moveUp;
		CAnimation moveDown;
		CAnimation* currentMove;

	};
}

