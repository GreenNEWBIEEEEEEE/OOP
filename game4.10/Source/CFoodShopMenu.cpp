#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CFood.h"
#include "CFoodShopMenu.h"

namespace game_framework
{
	CFoodShopMenu::CFoodShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer)
		: CShopMenu(p, gd, timer)
	{
		goods.push_back(&good_AppleJuice);
		goods.push_back(&good_Cake);
		goods.push_back(&good_DrinkBox);
		goods.push_back(&good_LunchBox);
		goods.push_back(&good_Meal);
		goods.push_back(&good_OrangeJuice);
	}

	void FSM_ReEnableInfoBoard_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CFoodShopMenu *fsm = (CFoodShopMenu*)sm;
		fsm->Enable_InfoBoard();
	}
	void FSM_Disable_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CFoodShopMenu *fsm = (CFoodShopMenu*)sm;
		if (r == CGameDialog::DialogOptionsResult::Yes)
		{
			fsm->Disable();
		}
		else
		{
			fsm->Enable_InfoBoard();
		}
	}

	void CFoodShopMenu::LoadBitmap()
	{
		CShopMenu::LoadBitmap();
		background.LoadBitmap(IDB_FoodShopBG);
		background.SetTopLeft(0, 0);

		good_AppleJuice.LoadBitmap(IDB_AppleJuice, RGB(255,255,255));
		good_Cake.LoadBitmap(IDB_Cake, RGB(255, 255, 255));
		good_DrinkBox.LoadBitmap(IDB_DrinkBox, RGB(255, 255, 255));
		good_LunchBox.LoadBitmap(IDB_LunchBox, RGB(255, 255, 255));
		good_Meal.LoadBitmap(IDB_Meal, RGB(255, 255, 255));
		good_OrangeJuice.LoadBitmap(IDB_OrangeJuice, RGB(255, 255, 255));
	}

	void CFoodShopMenu::OnKeyDown(UINT key)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D 取消
		const char KEY_A = 0x41; // keyboard A 購買
		if (key == KEY_LEFT)
		{
			if (goodSelector == 0) goodSelector = 5;
			else goodSelector--;
		}
		else if (key == KEY_RIGHT)
		{
			if (goodSelector == 5) goodSelector = 0;
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
				gd->SetCallback(&FSM_Disable_InGD, (CShopMenu*)this);
				gd->Enable();
			}
		}
		// Purchase
		else if (key == KEY_A)
		{
			if (player != nullptr)
			{
				switch (goodSelector)
				{
					// 
				case 0:
					processBuyingFood(15, 0);
					break;
				case 1:
					processBuyingFood(10, 1);
					break;
				case 2:
					processBuyingFood(20, 2);
					break;
				case 3:
					processBuyingFood(25, 3);
					break;
				case 4:
					processBuyingFood(20, 4);
					break;
				case 5:
					processBuyingFood(15, 5);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			// Do nothing
		}
	}

	void CFoodShopMenu::OnMove()
	{
		if (goodSelector % 3 == 0)
		{
			selector.SetTopLeft(120, 230);
		}
		else if (goodSelector % 3 == 1)
		{
			selector.SetTopLeft(240, 230);
		}
		else if (goodSelector % 3 == 2)
		{
			selector.SetTopLeft(360, 230);
		}
	}

	void CFoodShopMenu::OnShow()
	{
		if (enable)
		{
			blackBG.ShowBitmap();
			background.ShowBitmap();

			// Show goods & infos
			if (goodSelector < 3)
			{
				goods[0]->SetTopLeft(120, 230);
				goods[0]->ShowBitmap();
				goods[1]->SetTopLeft(240, 230);
				goods[1]->ShowBitmap();
				goods[2]->SetTopLeft(360, 230);
				goods[2]->ShowBitmap();
			}
			else
			{
				goods[3]->SetTopLeft(120, 230);
				goods[3]->ShowBitmap();
				goods[4]->SetTopLeft(240, 230);
				goods[4]->ShowBitmap();
				goods[5]->SetTopLeft(360, 230);
				goods[5]->ShowBitmap();
			}

			if (enable_infoboard)
			{
				selector.ShowBitmap();
				infoBoardBG.ShowBitmap();
				switch (goodSelector)
				{
				case 0:
					DrawTexts("Apple Juice (+ 15 HP)", 40, 370, 160);
					DrawTexts("Price : $15", 40, 400, 160);
					break;
				case 1:
					DrawTexts("Cake (+ 10 HP)", 40, 370, 160);
					DrawTexts("Price : $10", 40, 400, 160);
					break;
				case 2:
					DrawTexts("DrinkBox (+ 20 HP)", 40, 370, 160);
					DrawTexts("Price : $20", 40, 400, 160);
					break;
				case 3:
					DrawTexts("LunchBox (+ 25 HP)", 40, 370, 160);
					DrawTexts("Price : $25", 40, 400, 160);
					break;
				case 4:
					DrawTexts("Meal (+ 20 HP)", 40, 370, 160);
					DrawTexts("Price : $20", 40, 400, 160);
					break;
				case 5:
					DrawTexts("Orange Juice (+ 15 HP)", 40, 370, 160);
					DrawTexts("Price : $15", 40, 400, 160);
					break;
				default:
					break;
				}
				DrawTexts("[A] Buy [D] Quit", 400, 430, 140);
			}

		}
	}

	void CFoodShopMenu::processBuyingFood(int price, int foodPosition)
	{
		if (player->GetMoney() >= price)
		{
			// 交錢&交貨
			player->DecreaseMoney(price);
			player->GetFood()->at(foodPosition)->IncreaseNumber(1);

			// turn off the info board
			this->enable_infoboard = false;

			// show information after buying
			CString food_name;
			food_name.Format("You bought a %s.",
				player->GetFood()->at(foodPosition)->GetName().c_str());
			gd->AddMessage((LPCTSTR)food_name);

			// show the current money of player
			CString nowMoney_str = "";
			nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
			gd->AddMessage((LPCTSTR)nowMoney_str);

			// Re-enable the information board
			gd->SetCallback(&FSM_ReEnableInfoBoard_InGD, (CShopMenu*)this);
			gd->Enable();
		}
		else
		{
			gd->AddMessage("You don't have enough money.");
			gd->Enable();
		}
	}

	
}