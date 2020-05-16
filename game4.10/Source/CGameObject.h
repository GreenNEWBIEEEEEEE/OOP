#pragma once

namespace game_framework {
	class CAnimal;
	class CGameMap;
	class CGameObject
	{
	public:
		CGameObject();
		~CGameObject();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void SetX(int x);
		void SetY(int y);
		void SetBodyX(int bx);
		void SetBodyY(int by);
		void SetCollision(bool flag);
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		int GetHealthPoint() const;
		int GetBodyX() const;
		int GetBodyY() const;
		int GetLastX() const;
		int GetLastY() const;
		void DecreaseHP(int hp);
		void IncreaseHP(int hp);
		CAnimal* GetFacingAnimal();
		bool DetectCollision(vector<CGameObject*>* obj, int nextX, int nextY);
		virtual void OnMove(CGameMap* m, vector<CGameObject*>* obj) = 0;
		virtual void OnShow(CGameMap* m) = 0;
		virtual void LoadBitmap() = 0;

	protected:

		// 目前一整張玩家圖(包含上下左右 換工具 工具動作) "版面" 都是 128*120
		// 玩家角色圖片寬高
		int width, height;
		int STEP_SIZE = 5;
		// 玩家在地圖上的座標(點座標)
		int x, y;   // 整張圖的點座標
		int bx, by; // 玩家真正身體(body)的點座標
		int ex, ey; // 玩家觸發事件的點座標

		// 上一次保存的位置(可用於場景的位置還原)
		int lastX, lastY;

		bool collision = true;

		CAnimal* facingAnimal = nullptr;

		// 狀態旗標 : 是否上/下/左/右移
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

		int healthPoint;

	};


}