#pragma once
#include "CShopMenu.h"

namespace game_framework
{
	class CMovingBitmap;
	class CToolsMachinesShopMenu : public CShopMenu
	{
	public:
		CToolsMachinesShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnShow();
		void OnMove();
	private:

	};
}