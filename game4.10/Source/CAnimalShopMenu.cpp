#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CShopMenu.h"
#include "CAnimal.h"
#include "CChicken.h"
#include "CCow.h"
#include <random>
#include "CAnimalShopMenu.h"

namespace game_framework
{
	CAnimalShopMenu::CAnimalShopMenu(
		CPlayer *p, 
		CGameDialog *gd, 
		CTimer *timer,
		vector<CGameObject*>* objs,
		CMapManager *mm)
		:CShopMenu(p, gd, timer)
	{
		this->objs = objs;
		this->mm = mm;
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

	// Callbacks
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
					ProcessBuyingChicken();
					break;
				case 1:
					ProcessBuyingCow();
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
				DrawTexts("[A] Buy [D] Quit", 400, 430, 140);
			}

		}
	}

	void CAnimalShopMenu::ProcessBuyingChicken()
	{
		// 先關閉
		this->enable_infoboard = false;
		// 先檢查金錢足夠與否
		if (player->GetMoney() >= PRICE_CHICKEN)
		{
			// 旗標：購買有效與否
			bool isBought = false;
			for (unsigned i = 1; i <= 4; ++i)
			{
				// 有空缺的就補
				if ((*objs)[i] == nullptr)
				{
					// 生成可以放置的位置
					int gx = 0, gy = 0;
					GeneratePosition(ProcessingFlag::ForChicken, gx, gy);
					// 創建新的雞進去
					(*objs)[i] = new CChicken(gx * 64, gy * 53);
					/*重要：也要把初始相關設定(地圖/時間等)匯入*/
					((CAnimal*)(*objs)[i])->SetTimer(timer);
					((CAnimal*)(*objs)[i])->SetMap(mm->GetChickenCoop());
					((CAnimal*)(*objs)[i])->LoadBitmap();
					isBought = true;
					break;
				}
			}

			// 根據購買與否，顯示相應訊息
			if (isBought)
			{
				player->DecreaseMoney(PRICE_CHICKEN);
				gd->AddMessage("You bought a chicken.");
				gd->AddMessage("Take good care of it, ");
				gd->AddMessage("otherwise it will die!");
				CString nowMoney_str = "";
				nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
				gd->AddMessage((LPCTSTR)nowMoney_str);
			}
			else
			{
				gd->AddMessage("You have owned enough chickens !");
			}
		}
		else
		{
			gd->AddMessage("You don't have enough money.");
			gd->Enable();
		}
		gd->SetCallback(&ANSM_ReEnableInfoBoard_InGD, (CShopMenu*)this);
		gd->Enable();

	}

	void CAnimalShopMenu::ProcessBuyingCow()
	{
		// 先關閉infoboard
		this->enable_infoboard = false;
		// 先檢查金錢足夠與否
		if (player->GetMoney() >= PRICE_COW)
		{
			// 旗標：購買有效與否
			bool isBought = false;
			for (unsigned i = 5; i <= 8; ++i)
			{
				// 有空缺的就補
				if ((*objs)[i] == nullptr)
				{
					// 生成可以放置的位置
					int gx = 0, gy = 0;
					GeneratePosition(ProcessingFlag::ForCow, gx, gy);
					// 創建新的牛進去
					(*objs)[i] = new CCow(gx * 64, gy * 53);
					/*重要：也要把初始相關設定(地圖/時間等)匯入*/
					((CAnimal*)(*objs)[i])->SetTimer(timer);
					((CAnimal*)(*objs)[i])->SetMap(mm->GetCowCoop());
					((CAnimal*)(*objs)[i])->LoadBitmap();
					isBought = true;
					break;
				}
			}

			// 根據購買與否，顯示相應訊息
			if (isBought)
			{
				player->DecreaseMoney(PRICE_COW);
				gd->AddMessage("You bought a cow.");
				gd->AddMessage("Take good care of it, ");
				gd->AddMessage("otherwise it will die!");
				CString nowMoney_str = "";
				nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
				gd->AddMessage((LPCTSTR)nowMoney_str);
			}
			else
			{
				gd->AddMessage("You have owned enough cows !");
			}
		}
		else
		{
			gd->AddMessage("You don't have enough money.");
			gd->Enable();
		}
		// 重新開啟infoboard的callback
		gd->SetCallback(&ANSM_ReEnableInfoBoard_InGD, (CShopMenu*)this);
		gd->Enable();
	}

	void CAnimalShopMenu::GeneratePosition(ProcessingFlag flag, int &x, int &y)
	{
		// 旗標：是否找到合適位置
		bool isFoundProperPos = false;
		// 直到找到合適的
		while (!isFoundProperPos)
		{
			// 產生隨機格座標
			random_device rd;
			default_random_engine engine = default_random_engine(rd());
			uniform_int_distribution<int> disX(2, 9);
			uniform_int_distribution<int> disY(6, 10);
			int rgx = disX(engine); // 2~9
			int rgy = disY(engine); // 6~10
			
			// 先變成true，待與重疊條件式做AND運算
			isFoundProperPos = true;
			// 檢查重疊
			unsigned upBound = (flag == ProcessingFlag::ForChicken ? 5 : 8);
			unsigned downBound = (flag == ProcessingFlag::ForChicken ? 1 : 4);
			for (unsigned i = downBound; i <= upBound; ++i)
			{
				if ((*objs)[i] != nullptr)
				{
					int gx_obj = (*objs)[i]->GetBodyX() / 64;
					int gy_obj = (*objs)[i]->GetBodyY() / 53;
					isFoundProperPos = ((rgx != gx_obj) && (rgy != gy_obj)) && isFoundProperPos;
				}
			}

			if (isFoundProperPos)
			{
				x = rgx;
				y = rgy;
				TRACE("\nrgx=%d rgy=%d\n", rgx, rgy);
			}
		}
	}

	
}

