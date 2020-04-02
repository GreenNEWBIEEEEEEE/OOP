#pragma once
namespace game_framework {

	class CGameMap;
	class CMapManager;
	class CGameDialog;
	class CPlayer
	{
	public:
		CPlayer();
		~CPlayer();

		///
		/// 存取Player的屬性、旗標
		///
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void SetX(int x);
		void SetY(int y);
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		int GetLastX() const;
		int GetLastY() const;
		/*
		int GetDirection() const;
		void SetPlantingLeft(bool flag);
		void SetPlantingRight(bool flag);
		void SetPlantingUp(bool flag);
		void SetPlantingDown(bool flag);
		*/
		///
		/// 遊戲流程
		///
		void LoadBitmap();
		void OnMove(CGameMap* m);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd);

	private:
		// 玩家角色圖片寬高
		int width, height;
		// 玩家在地圖上的座標(點座標)
		int x, y;
		// 上一次保存的位置(可用於場景的位置還原)
		int lastX, lastY;
		// 玩家現在在哪張地圖/場景上
		int mapID; 
		// 玩家上一次在哪個場景(可用於場景還原)
		int lastMapID;

		// 移動的動畫
		CAnimation *facingDirection = nullptr; // 指向當前面向的方向之動畫
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;
		// 狀態旗標 : 是否上/下/左/右移
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

		/*
		CAnimation aniPlantLeft, aniPlantRight, aniPlantUp, aniPlantDown;
		bool isPlantingLeft, isPlantingRight, isPlantingRight, isPlantingRight;
		*/
		CAnimation aniChangeTool_0;
		CAnimation aniChangeTool_1;
		CAnimation aniChangeTool_2;
		CAnimation aniChangeTool_3;
		CAnimation aniChangeTool_4;
		CAnimation aniChangeTool_5;
		// 工具
		vector<int> tool;
		unsigned int toolSelector;
	};
}