#pragma once
#include "CShopMenu.h"

namespace game_framework
{
	class CFoodShopMenu : CShopMenu
	{
	public:
		CFoodShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnShow();
		void OnMove();
	};
}

