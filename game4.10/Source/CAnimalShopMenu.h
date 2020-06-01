#pragma once
#include "CShopMenu.h"

namespace game_framework
{
	class CMovingBitmap;
	class CAnimalShopMenu : public CShopMenu
	{
	public:
		CAnimalShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		int GetCurrentSelection() const;
		CTimer* GetTimer() const;

		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnShow();
		void OnMove();

	private:
		CMovingBitmap good_Chicken;
		CMovingBitmap good_Cow;
		CMovingBitmap goods[2] = { good_Chicken, good_Cow };
		const int PRICE_CHICKEN = 30;
		const int PRICE_COW = 60;
	};
}