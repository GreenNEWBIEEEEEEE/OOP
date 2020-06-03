#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CShopMenu.h"
#include "CAnimalShopMenu.h"

namespace game_framework
{
	CAnimalShopMenu::CAnimalShopMenu(CPlayer *p, CGameDialog *gd, CTimer *timer)
		:CShopMenu(p, gd, timer)
	{

	}

	void CAnimalShopMenu::LoadBitmap()
	{
		// base 
		CShopMenu::LoadBitmap();
		good_Chicken.LoadBitmap(IDB_Good_Chicken, RGB(255, 128, 255));
		good_Cow.LoadBitmap(IDB_Good_Cow, RGB(255, 128, 255));
		background.LoadBitmap(IDB_AnimalShopBg);
		background.SetTopLeft(0, 0);
		good_Chicken.SetTopLeft(170, 230);
		good_Cow.SetTopLeft(320, 230);
		selector.SetTopLeft(170, 230);
	}

	void ANSM_ReEnableInfoBoard_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CAnimalShopMenu *ansm = (CAnimalShopMenu*)sm;
		ansm->Enable_InfoBoard();
	}
	void ANSM_Disable_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CAnimalShopMenu *ansm = (CAnimalShopMenu*)sm;
		if (r == CGameDialog::DialogOptionsResult::Yes)
		{
			ansm->Disable();
		}
		else
		{
			ansm->Enable_InfoBoard();
		}
	}

	void CAnimalShopMenu::OnKeyDown(UINT key)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D 取消
		const char KEY_A = 0x41; // keyboard A 購買

		if (key == KEY_LEFT)
		{
			if (goodSelector == 0) goodSelector = 1;
			else goodSelector--;
		}
		else if (key == KEY_RIGHT)
		{
			if (goodSelector == 1) goodSelector = 0;
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
				gd->SetCallback(&ANSM_Disable_InGD, (CShopMenu*)this);
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
				// Purchase a chicken
				case 0:
					if (player->GetMoney() >= PRICE_CHICKEN)
					{
						// FIXME: enable尚未enable的雞
						this->enable_infoboard = false;
						player->DecreaseMoney(PRICE_CHICKEN);
						gd->AddMessage("You bought a chicken.");
						gd->AddMessage("Take good care of it, ");
						gd->AddMessage("otherwise it will die!");
						CString nowMoney_str = "";
						nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
						gd->AddMessage((LPCTSTR)nowMoney_str);
						gd->SetCallback(&ANSM_ReEnableInfoBoard_InGD, (CShopMenu*)this);
						gd->Enable();
					}
					else
					{
						gd->AddMessage("You don't have enough money.");
						gd->Enable();
					}
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

	void CAnimalShopMenu::OnMove()
	{
		switch (goodSelector)
		{
		case 0:
			selector.SetTopLeft(170, 230);
			break;
		case 1:
			selector.SetTopLeft(320, 230);
			break;
		default:
			break;
		}
	}

	void CAnimalShopMenu::OnShow()
	{
		if (enable)
		{
			blackBG.ShowBitmap();
			background.ShowBitmap();

			if (enable_infoboard)
			{
				selector.ShowBitmap();
				good_Chicken.ShowBitmap();
				good_Cow.ShowBitmap();
				infoBoardBG.ShowBitmap();
				switch (goodSelector)
				{
				case 0:
					DrawTexts("Chicken", 40, 370, 160);
					DrawTexts("Price : $ 40", 40, 400, 160);
					break;
				case 1:
					DrawTexts("Cow", 40, 370, 160);
					DrawTexts("Price : $ 60", 40, 400, 160);
					break;
				default:
					break;
				}
			}

		}
	}

	
}

