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
		int GetBodyX() const;
		int GetBodyY() const;
		int GetLastX() const;
		int GetLastY() const;
		int GetDirection() const;
		int GetCurrentTool() const;

		///
		/// 遊戲流程
		///
		void LoadBitmap();
		void OnMove(CGameMap* m);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd);
		void OnKeyUp(UINT key, CMapManager *mm, CGameDialog *gd);

	private:
		// 目前一整張玩家圖(包含上下左右 換工具 工具動作) "版面" 都是 128*120
		// 玩家角色圖片寬高
		int width, height;

		// 玩家在地圖上的座標(點座標)
		int x, y;   // 整張圖的點座標
		int bx, by; // 玩家真正身體(body)的點座標
		int ex, ey; // 玩家觸發事件的點座標
		
		// 上一次保存的位置(可用於場景的位置還原)
		int lastX, lastY;

		// 玩家方向旗標
		// 1=上, 2=下, 3=左, 4=右
		int direction = 2;
		int lastDirection;
		
		// 玩家現在在哪張地圖/場景上
		int mapID; 
		
		// 玩家上一次在哪個場景(可用於場景還原)
		int lastMapID;

		// 移動的動畫
		CAnimation *lastFacingDirection = nullptr;
		CAnimation *facingDirection = nullptr; // 指向當前面向的方向之動畫
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;
		// 狀態旗標 : 是否上/下/左/右移
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

		/*
		CAnimation aniPlantLeft, aniPlantRight, aniPlantUp, aniPlantDown;
		bool isPlantingLeft, isPlantingRight, isPlantingRight, isPlantingRight;
		*/

		// 更換工具的動畫
		CAnimation aniChangeTool_0;
		CAnimation aniChangeTool_1;
		CAnimation aniChangeTool_2;
		CAnimation aniChangeTool_3;
		CAnimation aniChangeTool_4;
		CAnimation aniChangeTool_5;
		CAnimation aniChangeTool_6;

		// 使用工具的動畫
		bool isUsingTool = false;
		CAnimation aniUseTool_0;
		CAnimation aniUseTool_1_front;
		CAnimation aniUseTool_1_back;
		CAnimation aniUseTool_1_left;
		CAnimation aniUseTool_1_right;

		CAnimation aniUseTool_2_front;
		CAnimation aniUseTool_2_back;
		CAnimation aniUseTool_2_left;
		CAnimation aniUseTool_2_right;

		CAnimation aniUseTool_3_front;
		CAnimation aniUseTool_3_back;
		CAnimation aniUseTool_3_left;
		CAnimation aniUseTool_3_right;

		CAnimation aniUseTool_4;

		CAnimation aniUseTool_5_front;
		CAnimation aniUseTool_5_back;
		CAnimation aniUseTool_5_left;
		CAnimation aniUseTool_5_right;

		CAnimation aniUseTool_6_front;
		CAnimation aniUseTool_6_back;
		CAnimation aniUseTool_6_left;
		CAnimation aniUseTool_6_right;

		// 工/道具的背包
		vector<int> tool;
		unsigned int toolSelector;
	};
}