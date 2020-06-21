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
			HighProduce,			// 更高的生產量
			Produce,				// 普通的生產量
			Hungry,					// 飢餓狀態
			NoProduce,    			// 沒有生產量
		};
		virtual void LoadBitmap() = 0;
		virtual void OnMove(CGameMap* m, vector<CGameObject*>* obj) = 0;
		virtual void OnShow(CGameMap* m) = 0;
		Status GetCurrentStatus() const;
		int GetClosePoint() const;
		void UnableShowAndMove();		// 若玩家跟動物不在同一張地圖，就會關閉OnShow跟OnMove
		void EnableShowAndMove();		
		void ChangeStatus(Status status);
		void SetMap(CGameMap* map);   // 設定雞舍or牛舍or羊舍地圖
		void SetTimer(CTimer* timer);
		void Reset();
		void SetPickUp(bool flag);
		CGameMap* GetMap();            // 回傳此動物所屬地圖
	protected:
		int onMoveTimes = 3; // 為了讓移動更加順暢自然，在重新決定動物移動方向之前，要先走一定次數，才能重新決定方向
		int counter = 0;     // 計數onMove次數
		int closePoint = 0;  // 主人與動物的親密度
		int resetX, resetY;
		bool onShowAndMove = true;  // 如果雞被人類抱起來的話，就必須unable
		bool isPickedUp = false;
		CTimer* timer;
		CGameMap* map; // 雞舍 or 牛舍 or 羊舍

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

