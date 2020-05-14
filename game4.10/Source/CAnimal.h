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

		enum class Status {			// 健康狀態
			Produce,				// 可生產
			Hungry,					// 如果以WaitingForFeed到了明天(NewDay)，就會切換到Hungry
			NoProduce    			// 無法生產
		};

	

		virtual void LoadBitmap() = 0;

		virtual void OnMove(CGameMap* m, vector<CGameObject*>* obj) = 0;
		virtual void OnShow(CGameMap* m) = 0;
		Status GetCurrentStatus();
		void ChangeStatus(Status status);
		void SetMap(CGameMap* map);   // 設定雞舍or牛舍or羊舍地圖
		void SetTimer(CTimer* timer);
	protected:
		CTimer* timer;
		CGameMap* map; // 雞舍 or 牛舍 or 羊舍

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

