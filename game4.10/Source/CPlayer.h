#pragma once
#include "CGameObject.h"
namespace game_framework {
	class CFoodMenu;
	class CTool;
	class CFood;
	class CGameMap;
	class CMapManager;
	class CGameDialog;
	class CShopMenu;
	class CPlayer : public CGameObject
	{
	public:
		enum MoveState
		{
			RadishMove,					// �a�ۥ��ڽ�����
			CornMove,
			PotatoMove,
			TomatoMove,
			EggPlantMove,
			PeanutMove,
			NormalMove,					// �@�먫��
			EggMove,
			ChickenMove,
			GrassMove,
			MilkMove,
			BigMilkMove,
			GoldenEggMove,
			CheeseMove,
			ButterMove
		};

		CPlayer();
		~CPlayer();

		///
		/// �s��Player���ݩʡB�X��
		///
		int GetDirection() const;
		int GetCurrentTool() const;
		int GetMoney() const;
		vector<CTool*>* GetBackpack();
		vector<CFood*>* GetFood();
		void SetToolSelector(unsigned int select);
		CFood* GetSelectedFood(int number);
		void ChangeMoveState(MoveState state);
		void DecreaseMoney(int money);
		MoveState GetCurrentMoveState();
		bool DetectLeftCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal); // ��������I���M�a�ϸI���A�p�GhasAnimal�OTrue�A�N��H�����W����ʪ�
		bool DetectRightCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		bool DetectUpCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);
		bool DetectDownCollision(CGameMap* m, vector<CGameObject*>* obj, bool hasAnimal);

		bool DetectLeftElementID(CGameMap* m, vector<int> elemID, int distance = 1); 
		bool DetectRightElementID(CGameMap* m, vector<int> elemID, int distance = 1);
		bool DetectUpElementID(CGameMap* m, vector<int> elemID, int distance = 1);
		bool DetectDownElementID(CGameMap* m, vector<int> elemID, int distance = 1);

		CAnimal* GetPickUpAnimal();
		void Move(CGameMap* m, CAnimation* moveUp, CAnimation* moveDown, CAnimation* moveLeft, CAnimation* moveRight, vector<CGameObject*>* obj);
		///
		/// �C���y�{
		///
		void LoadBitmap();
		void OnMove(CGameMap* m, vector<CGameObject*>* obj);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, 
			CMapManager *mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms, 
			CGameMap* m, 
			vector<CGameObject*>* obj, CFoodMenu* fm);
		void OnKeyUp(UINT key, CMapManager *mm, CGameDialog *gd);

		void DoSomethingInChickenCoop(CMapManager *mm, CGameMap* m, vector<CGameObject*>* obj);
		void DoSomethingInCowCoop(CMapManager *mm, CGameMap* m, vector<CGameObject*>* obj);
		void SellThing(CGameMap* m);

	private:
		MoveState currentMoveState = NormalMove;

		// ���a��V�X��
		// 1=�W, 2=�U, 3=��, 4=�k
		int direction = 2;
		int lastDirection;
		bool fixAnimation = false;
		CAnimal* pickUpAnimal = nullptr;

		// ���ʪ��ʵe
		CAnimation *lastFacingDirection = nullptr;
		CAnimation *facingDirection = nullptr; // ���V��e���V����V���ʵe
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;
		CAnimation aniRadishMoveLeft, aniRadishMoveRight, aniRadishMoveUp, aniRadishMoveDown;
		CAnimation aniEggMoveLeft, aniEggMoveRight, aniEggMoveUp, aniEggMoveDown;
		CAnimation aniGrassMoveLeft, aniGrassMoveRight, aniGrassMoveUp, aniGrassMoveDown;
		CAnimation aniChickenMoveLeft, aniChickenMoveRight, aniChickenMoveUp, aniChickenMoveDown;

		CAnimation aniMilkMoveLeft, aniMilkMoveRight, aniMilkMoveUp, aniMilkMoveDown;
		CAnimation aniSmallMilkMoveLeft, aniSmallMilkMoveRight, aniSmallMilkMoveUp, aniSmallMilkMoveDown;
		CAnimation aniGoldenEggMoveLeft, aniGoldenEggMoveRight, aniGoldenEggMoveUp, aniGoldenEggMoveDown;
		CAnimation aniCheeseMoveLeft, aniCheeseMoveRight, aniCheeseMoveUp, aniCheeseMoveDown;
		CAnimation aniButterMoveLeft, aniButterMoveRight, aniButterMoveUp, aniButterMoveDown;
		CAnimation aniPotatoMoveLeft, aniPotatoMoveRight, aniPotatoMoveUp, aniPotatoMoveDown;
		CAnimation aniTomatoMoveLeft, aniTomatoMoveRight, aniTomatoMoveUp, aniTomatoMoveDown;
		CAnimation aniCornMoveLeft, aniCornMoveRight, aniCornMoveUp, aniCornMoveDown;
		CAnimation aniEggPlantMoveLeft, aniEggPlantMoveRight, aniEggPlantMoveUp, aniEggPlantMoveDown;
		CAnimation aniPeanutMoveLeft, aniPeanutMoveRight, aniPeanutMoveUp, aniPeanutMoveDown;


		// �󴫤u�㪺�ʵe
		CAnimation aniChangeTool_0;
		CAnimation aniChangeTool_1;
		CAnimation aniChangeTool_2;
		CAnimation aniChangeTool_3;
		CAnimation aniChangeTool_4;
		CAnimation aniChangeTool_5;
		CAnimation aniChangeTool_6;
		CAnimation aniChangeTool_7;
		CAnimation aniChangeTool_8;
		CAnimation aniChangeTool_9;
		CAnimation aniChangeTool_10;
		CAnimation aniChangeTool_11;

		// �ϥΤu�㪺�ʵe
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

		// �u/�D�㪺�I�]
		vector<CTool*> backpack;
		vector<CFood*> food;
		unsigned int toolSelector;

		// ���a�ݩ�
		int money;

	};
}