#pragma once
#include "CShopMenu.h"

namespace game_framework
{
	class CFoodShopMenu : public CShopMenu
	{
	public:
		CFoodShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		void LoadBitmap();
		void OnKeyDown(UINT key);
		void OnMove();
		void OnShow();

	private:
		CMovingBitmap good_AppleJuice;
		CMovingBitmap good_Cake;
		CMovingBitmap good_DrinkBox;
		CMovingBitmap good_LunchBox;
		CMovingBitmap good_Meal;
		CMovingBitmap good_OrangeJuice;
		vector<CMovingBitmap*> goods;
	};
}

