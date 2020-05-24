#pragma once

#include "CTimer.h"
#include "CPlayer.h"
#include "CGameDialog.h"

namespace game_framework
{
	class CShopMenu
	{
	public:
		CShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		~CShopMenu();
		void Enable();
		void Enable_InfoBoard();
		void Disable_InfoBoard();
		void Disable();
		bool IsEnable() const;
		void LoadBitmap();

	protected:
		CGameDialog * gd = nullptr;
		CTimer *timer = nullptr;
		CPlayer *player = nullptr;

		bool enable = false;
		bool enable_infoboard = false;

		CMovingBitmap selector;
		CMovingBitmap blackBG;
		CMovingBitmap background;
		CMovingBitmap infoBoardBG;

		int goodSelector = 0;

	// Tool functions
	protected:
		void DrawTexts(CString text, int posX, int posY, int fontSize);

	};
}