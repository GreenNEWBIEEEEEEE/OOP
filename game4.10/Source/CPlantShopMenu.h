#pragma once

#include "CShopMenu.h"

namespace game_framework
{
	class CMovingBitmap;
	class CPlantShopMenu : public CShopMenu
	{
		
	public:
		enum SeedGoods {Radish, Corn, Tomato, Potato, Eggplant, Peanut};

		CPlantShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer);
		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnMove();
		void OnShow();

	private:
		// Goods
		CMovingBitmap good_RadishSeed;
		CMovingBitmap good_CornSeed;
		CMovingBitmap good_TomatoSeed;
		CMovingBitmap good_PotatoSeed;
		CMovingBitmap good_EggplantSeed;
		CMovingBitmap good_PeanutSeed;

		// prices 價格，是隨機浮動的(範圍在10~30間)
		int radish_price;
		int corn_price;
		int tomato_price;
		int potato_price;
		int eggplant_price;
		int peanut_price;

		// Talking icon
		CMovingBitmap icon_talking;

		// Seasons
		vector<CMovingBitmap*> spring_goods;
		vector<CMovingBitmap*> summer_goods;
		vector<CMovingBitmap*> fall_goods;
		vector<CMovingBitmap*> winter_goods;
		vector<CMovingBitmap*>* season_goods = nullptr;

	// Private tool functions
	private:
		// Update seasons of goods: 更新季節性的貨物集合
		// 會在OnKeyDown/OnMove呼叫，以即時更新季節貨物
		void updateSeasonOfGoods();

		// Process buying seed : 處理購買種子的標準流程的函數
		// price: 欲購買之seed的價格
		// toolSeedPosition: 購買後應該放在player背包的何處
		void processBuyingSeed(int price, int toolSeedPosition);

		void talking();
		

	};
}
