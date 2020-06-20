#pragma once
#include "CGameObject.h"
#include "CShopMenu.h"
#include "CMapManager.h"

namespace game_framework
{
	class CMovingBitmap;
	class CAnimalShopMenu : public CShopMenu
	{
	public:
		CAnimalShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer, vector<CGameObject*>* objs, CMapManager *mm);
		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnShow();
		void OnMove();

	private:
		vector<CGameObject*>* objs = nullptr;
		CMapManager *mm = nullptr;

		CMovingBitmap good_Chicken;
		CMovingBitmap good_Cow;
		CMovingBitmap goods[2] = { good_Chicken, good_Cow };
		const int PRICE_CHICKEN = 30;
		const int PRICE_COW = 60;

	// Tool functions
	private:
		enum ProcessingFlag
		{
			ForChicken, ForCow
		};
		void ProcessBuyingChicken();
		void ProcessBuyingCow();
		void GeneratePosition(ProcessingFlag flag, int &x, int &y);

	};
}