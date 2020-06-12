#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMapManager.h"
#include "CMapShopEvent.h"
#include "CPlantShopMenu.h"
#include "CTool.h"

namespace game_framework
{

	CPlantShopMenu::CPlantShopMenu(CPlayer *p, CGameDialog * gd, CTimer *timer)
		:CShopMenu(p, gd, timer)
	{
		spring_goods.push_back(&good_RadishSeed);
		spring_goods.push_back(&good_CornSeed);
		spring_goods.push_back(&icon_talking);
		
		summer_goods.push_back(&good_TomatoSeed);
		summer_goods.push_back(&good_TomatoSeed);
		summer_goods.push_back(&icon_talking);

		fall_goods.push_back(&good_EggplantSeed);
		fall_goods.push_back(&good_PotatoSeed);
		fall_goods.push_back(&icon_talking);

		winter_goods.push_back(&good_EggplantSeed);
		winter_goods.push_back(&good_PeanutSeed);
		winter_goods.push_back(&icon_talking);
	}

	void CPlantShopMenu::LoadBitmap()
	{
		// base
		CShopMenu::LoadBitmap();

		// taking icon
		icon_talking.LoadBitmap(IDB_OtherIcons_Talking, RGB(255, 255, 255));
		icon_talking.SetTopLeft(360, 230);

		// Shop Backgound: ����H���d�x
		background.LoadBitmap(IDB_PlantShopBG);
		background.SetTopLeft(0, 0);

		// goods
		good_RadishSeed.LoadBitmap(IDB_RadishSeed, RGB(255, 255, 255));
		good_CornSeed.LoadBitmap(IDB_CornSeed, RGB(255, 255, 255));
		good_TomatoSeed.LoadBitmap(IDB_TomatoSeed, RGB(255, 255, 255));
		good_PotatoSeed.LoadBitmap(IDB_PotatoSeed, RGB(255, 255, 255));
		good_EggplantSeed.LoadBitmap(IDB_EggplantSeed, RGB(255, 255, 255));
		good_PeanutSeed.LoadBitmap(IDB_PeanutSeed, RGB(255, 255, 255));
		
		//good_RadishSeed.SetTopLeft(120, 230);
		//good_Seed02.SetTopLeft(240, 230);
		//good_Seed03.SetTopLeft(360, 230);
	}

	// Callback functions
	void ReEnableInfoBoard_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CPlantShopMenu *psm = (CPlantShopMenu*)sm;
		psm->Enable_InfoBoard();
	}
	void Disable_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CPlantShopMenu *psm = (CPlantShopMenu*)sm;
		if (r == CGameDialog::DialogOptionsResult::Yes)
		{
			psm->Disable();
		}
		else
		{
			psm->Enable_InfoBoard();
		}
	}

	// FIXME
	void CPlantShopMenu::OnKeyDown(UINT key)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_D = 0x44; // keyboard D ����
		const char KEY_A = 0x41; // keyboard A �ʶR

		// Select
		if (key == KEY_LEFT)
		{
			if (goodSelector == 0) goodSelector = 2;
			else goodSelector--;
		}
		else if (key == KEY_RIGHT)
		{
			if (goodSelector == 2) goodSelector = 0;
			else goodSelector++;
		}

		// Leave
		else if (key == KEY_D)
		{
			this->enable_infoboard = false;
			if (gd != nullptr)
			{
				gd->AddQuestion("Do you want to leave?");
				gd->AddOptionResultMessage("Thank you. Please come again.", "Ok.");
				gd->SetCallback(&Disable_InGD, (CShopMenu*)this);
				gd->Enable();
			}
		}

		// Purchase
		else if (key == KEY_A)
		{
			if (player != nullptr)
			{
				// Spring
				if (timer->GetMonth() >= 1 && timer->GetMonth() <= 3)
				{
					switch (goodSelector)
					{
					case 0:
						processBuyingSeed(10, 4);
						break;
					case 1:
						processBuyingSeed(15, 10);
						break;
					default:
						break;
					}
				}
				// Summer
				else if (timer->GetMonth() >= 4 && timer->GetMonth() <= 6)
				{
					switch (goodSelector)
					{
					case 0:
						processBuyingSeed(15, 8);
						break;
					case 1:
						processBuyingSeed(20, 10);
						break;
					default:
						break;
					}
				}
				// Fall
				else if (timer->GetMonth() >= 7 && timer->GetMonth() <= 9)
				{
					switch (goodSelector)
					{
					case 0:
						processBuyingSeed(15, 9); // Eggplant
						break;
					case 1:
						processBuyingSeed(20, 7); // Potato
						break;
					default:
						break;
					}
				}
				// Winter
				else
				{
					switch (goodSelector)
					{
					case 0:
						processBuyingSeed(23, 9); // Eggplant
						break;
					case 1:
						processBuyingSeed(20, 11); // Peanut
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			// Do nothing
		}
	}
	
	void CPlantShopMenu::OnMove()
	{
		// Update season 
		updateSeasonOfGoods();

		// Move selector position
		switch (goodSelector)
		{
		case 0:
			selector.SetTopLeft(120, 230);
			break;
		case 1:
			selector.SetTopLeft(240, 230);
			break;
		case 2:
			selector.SetTopLeft(360, 230);
			break;
		default:
			break;
		}
	}
	
	void CPlantShopMenu::OnShow()
	{
		if (enable)
		{
			blackBG.ShowBitmap();
			background.ShowBitmap();
			
			if (this->enable_infoboard == true)
			{
				// Show selector
				selector.ShowBitmap();

				// information board
				infoBoardBG.ShowBitmap();
				
				// According to seasons, sell different seeds.
				// Display different seed information on the information board.
				for (unsigned i = 0; i < season_goods->size(); ++i)
				{
					season_goods->at(i)->SetTopLeft(120 * (i + 1), 230);
					season_goods->at(i)->ShowBitmap();
				}
				// Spring
				if (timer->GetMonth() >= 1 && timer->GetMonth() <= 3)
				{
					switch (goodSelector)
					{
					case 0:
						DrawTexts("Seed of Radish", 40, 370, 160);
						DrawTexts("Price : $ 10", 40, 400, 160);
						break;
					case 1:
						DrawTexts("Seed of Corn", 40, 370, 160);
						DrawTexts("Price : $ 15", 40, 400, 160);
						break;
					default:
						DrawTexts("Press A to Talk.", 40, 370, 160);
						break;
					}
				}
				// Summer
				else if (timer->GetMonth() >= 4 && timer->GetMonth() <= 6)
				{
					switch (goodSelector)
					{
					case 0:
						DrawTexts("Seed of Corn", 40, 370, 160);
						DrawTexts("Price : $ 15", 40, 400, 160);
						break;
					case 1:
						DrawTexts("Seed of Tomato", 40, 370, 160);
						DrawTexts("Price : $ 20", 40, 400, 160);
						break;
					default:
						DrawTexts("Press A to Talk.", 40, 370, 160);
						break;
					}
				}
				// Fall
				else if (timer->GetMonth() >= 7 && timer->GetMonth() <= 9)
				{
					switch (goodSelector)
					{
					case 0:
						DrawTexts("Seed of Eggplant", 40, 370, 160);
						DrawTexts("Price : $ 15", 40, 400, 160);
						break;
					case 1:
						DrawTexts("Seed of Potato", 40, 370, 160);
						DrawTexts("Price : $ 20", 40, 400, 160);
						break;
					default:
						DrawTexts("Press A to Talk.", 40, 370, 160);
						break;
					}
				}
				// Winter
				else
				{
					switch (goodSelector)
					{
					case 0:
						DrawTexts("Seed of Eggplant", 40, 370, 160);
						DrawTexts("Price : $ 23", 40, 400, 160);
						break;
					case 1:
						DrawTexts("Seed of Peanut", 40, 370, 160);
						DrawTexts("Price : $ 20", 40, 400, 160);
						break;
					default:
						DrawTexts("Press A to Talk.", 40, 370, 160);
						break;
					}
				}

				// 
				DrawTexts("[A] Buy [D] Quit", 400, 430, 140);
			}
			
		}
	}
	
	
	void CPlantShopMenu::updateSeasonOfGoods()
	{
		// Spring
		if (timer->GetMonth() >= 1 && timer->GetMonth() <= 3)
		{
			season_goods = &spring_goods;
		}
		// Summer
		else if (timer->GetMonth() >= 4 && timer->GetMonth() <= 6)
		{
			season_goods = &summer_goods;
		}
		// Fall
		else if (timer->GetMonth() >= 7 && timer->GetMonth() <= 9)
		{
			season_goods = &fall_goods;
		}
		// Winter
		else
		{
			season_goods = &winter_goods;
		}
	}

	void CPlantShopMenu::processBuyingSeed(int price, int toolSeedPosition)
	{
		if (player->GetMoney() >= price)
		{
			// turn off the info board
			this->enable_infoboard = false;
			// ���&��f
			player->DecreaseMoney(price);
			player->GetBackpack()->at(toolSeedPosition)->IncreaseNumber(1);
			
			// show information after buying
			CString seed_name;
			seed_name.Format("You bought a bag of %s.", 
				player->GetBackpack()->at(toolSeedPosition)->GetName().c_str());
			gd->AddMessage((LPCTSTR)seed_name);
			
			// show the current money of player
			CString nowMoney_str = "";
			nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
			gd->AddMessage((LPCTSTR)nowMoney_str);
			
			// Re-enable the information board
			gd->SetCallback(&ReEnableInfoBoard_InGD, (CShopMenu*)this);
			gd->Enable();
		}
		else
		{
			gd->AddMessage("You don't have enough money.");
			gd->Enable();
		}
	}
}