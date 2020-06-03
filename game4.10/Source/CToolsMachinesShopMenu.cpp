#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolsMachinesShopMenu.h"

namespace game_framework
{
	CToolsMachinesShopMenu::CToolsMachinesShopMenu(CPlayer * p, CGameDialog * gd, CTimer * timer)
		:CShopMenu(p, gd, timer)
	{

	}
	void TMSM_ReEnableInfoBoard_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CToolsMachinesShopMenu *tmsm = (CToolsMachinesShopMenu*)sm;
		tmsm->Enable_InfoBoard();
	}
	void TMSM_Disable_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CToolsMachinesShopMenu *tmsm = (CToolsMachinesShopMenu*)sm;
		if (r == CGameDialog::DialogOptionsResult::Yes)
		{
			tmsm->Disable();
		}
		else
		{
			tmsm->Enable_InfoBoard();
		}
	}

	void CToolsMachinesShopMenu::OnKeyDown(UINT key)
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
				gd->SetCallback(&TMSM_Disable_InGD, (CShopMenu*)this);
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

	void CToolsMachinesShopMenu::LoadBitmap()
	{
		CShopMenu::LoadBitmap();
		background.LoadBitmap(IDB_ToolsMachinesShopBG);
		background.SetTopLeft(0, 0);
	}

	void CToolsMachinesShopMenu::OnMove()
	{

	}

	void CToolsMachinesShopMenu::OnShow()
	{
		if (enable)
		{
			blackBG.ShowBitmap();
			background.ShowBitmap();

			if (enable_infoboard)
			{
				selector.ShowBitmap();
				infoBoardBG.ShowBitmap();
				switch (goodSelector)
				{
				case 0:
					break;
				case 1:
					break;
				default:
					break;
				}
			}

		}
	}
}