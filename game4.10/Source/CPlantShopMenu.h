#pragma once

#include "CShopMenu.h"

namespace game_framework
{
	class CMovingBitmap;
	class CPlantShopMenu : public CShopMenu
	{
	public:
		CPlantShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);

		int GetCurrentSelection() const;
		CTimer* GetTimer() const;

		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnMove();
		void OnShow();

	private:
		CMovingBitmap good_RadishSeed;
		CMovingBitmap good_Seed02;
		CMovingBitmap good_Seed03;
		CMovingBitmap goods[3] = { good_RadishSeed, good_Seed02, good_Seed03 };
	};
}
