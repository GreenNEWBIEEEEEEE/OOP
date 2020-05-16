#pragma once
#include "CGameObject.h"
namespace game_framework {
	class CTool;
	class CGameMap;
	class CMapManager;
	class CGameDialog;
	class CShopMenu;
	class CPlayer : public CGameObject
	{
	public:
		enum MoveState
		{
			RadishMove,					// 帶著白蘿蔔走路
			NormalMove,					// 一般走路
			EggMove,
			ChickenMove,
			GrassMove,
			MilkMove
		};
		CPlayer();
		~CPlayer();

		///
		/// 存取Player的屬性、旗標
		///
		int GetDirection() const;
		int GetCurrentTool() const;
		int GetMoney() const;
		vector<CTool*>* GetBackpack();
		void SetToolSelector(unsigned int select);
		void ChangeMoveState(MoveState state);
		void DecreaseMoney(int money);
		MoveState GetCurrentMoveState();
		bool DetectLeftCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		bool DetectRightCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		bool DetectUpCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		bool DetectDownCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		void Move(CGameMap* m, CAnimation* moveUp, CAnimation* moveDown, CAnimation* moveLeft, CAnimation* moveRight, vector<CGameObject*>* obj);
		///
		/// 遊戲流程
		///
		void LoadBitmap();
		void OnMove(CGameMap* m, vector<CGameObject*>* obj);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd, CShopMenu *sm, CGameMap* m, vector<CGameObject*>* obj);
		void OnKeyUp(UINT key, CMapManager *mm, CGameDialog *gd);

	private:
		MoveState currentMoveState = NormalMove;

		// 玩家方向旗標
		// 1=上, 2=下, 3=左, 4=右
		int direction = 2;
		int lastDirection;
		
		CAnimal* pickUpAnimal = nullptr;

		// 移動的動畫
		CAnimation *lastFacingDirection = nullptr;
		CAnimation *facingDirection = nullptr; // 指向當前面向的方向之動畫
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;
		CAnimation aniRadishMoveLeft, aniRadishMoveRight, aniRadishMoveUp, aniRadishMoveDown;
		CAnimation aniEggMoveLeft, aniEggMoveRight, aniEggMoveUp, aniEggMoveDown;
		CAnimation aniGrassMoveLeft, aniGrassMoveRight, aniGrassMoveUp, aniGrassMoveDown;
		CAnimation aniChickenMoveLeft, aniChickenMoveRight, aniChickenMoveUp, aniChickenMoveDown;

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
		vector<CTool*> backpack;
		unsigned int toolSelector;

		// 玩家屬性
		int money;

	};
}