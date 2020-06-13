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

		// prices ����A�O�H���B�ʪ�(�d��b10~30��)
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
		// Update seasons of goods: ��s�u�`�ʪ��f�����X
		// �|�bOnKeyDown/OnMove�I�s�A�H�Y�ɧ�s�u�`�f��
		void updateSeasonOfGoods();

		// Process buying seed : �B�z�ʶR�ؤl���зǬy�{�����
		// price: ���ʶR��seed������
		// toolSeedPosition: �ʶR�����ө�bplayer�I�]����B
		void processBuyingSeed(int price, int toolSeedPosition);

		void talking();
		

	};
}
