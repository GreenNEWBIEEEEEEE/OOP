#pragma once

#include "CShopMenu.h"
#include "CPlayer.h"
#include "CTimer.h"

namespace game_framework
{
	class CMovingBitmap;
	class CPlantShopMenu : public CShopMenu
	{
	public:
		CPlantShopMenu();
		CPlantShopMenu(CGameDialog *gd, CTimer *timer);

		void SetPlayerDataOnce(CPlayer *player);
		void SetGameDialogOnce(CGameDialog *gd);
		int GetCurrentSelection() const;
		CTimer* GetTimer() const;
		
		void Enable();
		void Enable(CPlayer *p, CGameDialog *gd);
		void Enable_InfoBoard();
		void Disable_InfoBoard();
		void Disable();
		bool IsEnable();

		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnMove();
		void OnShow();



	private:
		CGameDialog * gd = nullptr;
		CTimer *timer = nullptr;

		bool enable = false;
		bool enable_infoboard = false;

		CMovingBitmap blackBG;
		CMovingBitmap background;
		CMovingBitmap infoBoardBG;

		int goodSelector = 0;
		CMovingBitmap selector;
		CMovingBitmap good_RadishSeed;
		CMovingBitmap good_Seed02;
		CMovingBitmap good_Seed03;
		CMovingBitmap goods[3] = { good_RadishSeed, good_Seed02, good_Seed03 };

		// 玩家指標 Disable時會回復成nullptr
		CPlayer *player = nullptr;

	// private tool functions
	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);

	};
}
