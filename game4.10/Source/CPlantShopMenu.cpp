#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapInfo.h"
#include "CMapTransitionEvent.h"
#include "CMapFarmingEvent.h"
#include "CMapShowDialogEvent.h"
#include "CMapManager.h"
#include "CMapShopEvent.h"
#include "CPlantShopMenu.h"
#include "CTool.h"

namespace game_framework
{
	CPlantShopMenu::CPlantShopMenu()
	{
	}

	CPlantShopMenu::CPlantShopMenu(CGameDialog * gd, CTimer *timer)
	{
		this->gd = gd;
		this->timer = timer;
	}

	void CPlantShopMenu::LoadBitmap()
	{
		blackBG.LoadBitmap(IDB_ShopMenuBlackBG);
		background.LoadBitmap(IDB_PlantShopBG, RGB(255, 255, 255));
		infoBoardBG.LoadBitmap(IDB_DIALOG_BG_01);
		good_RadishSeed.LoadBitmap(IDB_Seed01, RGB(255, 255, 255));
		good_Seed02.LoadBitmap(IDB_Seed02, RGB(255, 255, 255));
		good_Seed03.LoadBitmap(IDB_Seed03, RGB(255, 255, 255));
		selector.LoadBitmap(IDB_PlantShopSelector, RGB(255, 255, 255));

		blackBG.SetTopLeft(0, 0);
		background.SetTopLeft(0, 0);
		infoBoardBG.SetTopLeft(20, 360);
		selector.SetTopLeft(120, 230);
		good_RadishSeed.SetTopLeft(120, 230);
		good_Seed02.SetTopLeft(240, 230);
		good_Seed03.SetTopLeft(360, 230);
	}

	void CPlantShopMenu::SetPlayerDataOnce(CPlayer * player)
	{
		this->player = player;
	}

	void CPlantShopMenu::SetGameDialogOnce(CGameDialog * gd)
	{
		this->gd = gd;
	}

	int CPlantShopMenu::GetCurrentSelection() const
	{
		return goodSelector;
	}

	CTimer * CPlantShopMenu::GetTimer() const
	{
		return this->timer;
	}

	void CPlantShopMenu::Enable()
	{
		GAME_ASSERT(
			((player != nullptr) && (gd != nullptr)),
			"呼叫Enable前應該先呼叫SetPlayerDataOnce以及SetGameDialogOnce");
		enable = true;
	}

	void CPlantShopMenu::Enable(CPlayer * p, CGameDialog * gd)
	{
		this->player = p;
		this->gd = gd;
		enable = true;
	}

	void CPlantShopMenu::Enable_InfoBoard()
	{
		this->enable_infoboard = true;
	}

	void CPlantShopMenu::Disable()
	{
		enable = false;
		this->enable_infoboard = false;
		// player/gd不再使用 因此回復成nullptr
		player = nullptr;
		//gd = nullptr;
	}

	void CPlantShopMenu::Disable_InfoBoard()
	{
		this->enable_infoboard = false;
	}

	bool CPlantShopMenu::IsEnable()
	{
		return enable;
	}

	// Callback function
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
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_D = 0x44; // keyboard D 取消
		const char KEY_A = 0x41; // keyboard A 購買

		// Callback func pointers
		CGameDialog::CallbackWithResultForShopMenu reenable_infoBoard_inGD = &ReEnableInfoBoard_InGD;
		CGameDialog::CallbackWithResultForShopMenu disable_inGD = &Disable_InGD;

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
				gd->SetCallback(disable_inGD, (CShopMenu*)this);
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
				case 0:
					if (player->GetMoney() >= 10)
					{
						// FIXME: 尚未增加種子
						this->enable_infoboard = false;
						player->DecreaseMoney(10);
						player->GetBackpack()->at(4)->IncreaseNumber(1);
						gd->AddMessage("You bought a bag of Seed 01.");
						CString nowMoney_str = "";
						nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
						gd->AddMessage((LPCTSTR)nowMoney_str);
						gd->SetCallback(reenable_infoBoard_inGD, (CShopMenu*)this);
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
	

	void CPlantShopMenu::OnMove()
	{
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
				selector.ShowBitmap();
				good_RadishSeed.ShowBitmap();
				good_Seed02.ShowBitmap();
				good_Seed03.ShowBitmap();
				infoBoardBG.ShowBitmap();
				switch (goodSelector)
				{
				case 0:
					DrawTexts("Seed 01", 40, 370, 160);
					DrawTexts("Price : $ 10", 40, 400, 160);
					break;
				case 1:
					DrawTexts("Seed 02", 40, 370, 160);
					DrawTexts("Price : $ 15", 40, 400, 160);
					break;
				case 2:
					DrawTexts("Seed 03", 40, 370, 160);
					DrawTexts("Price : $ 20", 40, 400, 160);
					break;
				default:
					break;
				}
			}
			
		}
	}

	void CPlantShopMenu::DrawTexts(CString text, int posX, int posY, int fontSize)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp = nullptr;
		f.CreatePointFont(fontSize, "Consolas");
		fp = pDC->SelectObject(&f);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(posX, posY, text);
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}