#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CClinicMenu.h"
#include <random>

namespace game_framework
{
	CClinic::CClinic(CPlayer * p, CGameDialog * gd, CTimer * timer)
		: CShopMenu(p, gd, timer)
	{
	}
	
	void CClinic::LoadBitmap()
	{
		CShopMenu::LoadBitmap();
		background.LoadBitmap(IDB_ClinicBG);
		background.SetTopLeft(0, 0);
		selector.SetTopLeft(240, 230);
		hp_up.LoadBitmap(IDB_HP_Up, RGB(255,255,255));
		hp_up.SetTopLeft(240, 230);
	}

	// Callbacks
	void Clinic_ReEnableInfoBoard_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CClinic *clinic = (CClinic*)sm;
		clinic->Enable_InfoBoard();
	}
	void Clinic_Disable_InGD(CGameDialog::DialogOptionsResult r, CShopMenu *sm)
	{
		CClinic *clinic = (CClinic*)sm;
		if (r == CGameDialog::DialogOptionsResult::Yes)
		{
			clinic->Disable();
		}
		else
		{
			clinic->Enable_InfoBoard();
		}
	}

	void CClinic::OnKeyDown(UINT key)
	{
		const char KEY_D = 0x44; // keyboard D ¨ú®ø
		const char KEY_A = 0x41; // keyboard A ÁÊ¶R

		// Leave
		if (key == KEY_D)
		{
			this->enable_infoboard = false;
			if (gd != nullptr)
			{
				gd->AddQuestion("Do you want to leave?");
				gd->AddOptionResultMessage("Thank you. Please come again.", "Ok.");
				gd->SetCallback(&Clinic_Disable_InGD, (CShopMenu*)this);
				gd->Enable();
			}
		}

		// Purchase
		else if (key == KEY_A)
		{
			if (player != nullptr)
			{
				random_device rd;
				default_random_engine engine = default_random_engine(rd());
				uniform_int_distribution<int> disPrice(0, 100);
				int r_price = disPrice(engine);

				// turn off the info board
				this->enable_infoboard = false;
				if (player->GetMoney() >= r_price && player->GetHealthPoint() < 100)
				{
					// 
					player->DecreaseMoney(r_price);
					player->IncreaseHP(100);
					
					// show information after buying
					gd->AddMessage("Your HP is 100 now.");

					// show the current money of player
					CString nowMoney_str = "";
					nowMoney_str.Format("You now have $ %d left.", player->GetMoney());
					gd->AddMessage((LPCTSTR)nowMoney_str);
				}
				else if (player->GetHealthPoint() == 100)
				{
					gd->AddMessage("You are healthy.");
					gd->AddMessage("You don't need any treatment.");
					gd->Enable();
				}
				else
				{
					gd->AddMessage("You don't have enough money.");
					gd->Enable();
				}
				// Re-enable the information board
				gd->SetCallback(&Clinic_ReEnableInfoBoard_InGD, (CShopMenu*)this);
				gd->Enable();
			}
			
		}
		else
		{
			// Do nothing
		}
	}
	
	void CClinic::OnMove()
	{

	}

	void CClinic::OnShow()
	{
		if (enable)
		{
			blackBG.ShowBitmap();
			background.ShowBitmap();

			hp_up.ShowBitmap();

			if (this->enable_infoboard == true)
			{

				// Show selector
				selector.ShowBitmap();

				// information board
				infoBoardBG.ShowBitmap();
				// Decribe
				DrawTexts("Increase HP to 100!", 50, 370, 160);
				DrawTexts("Price : Random Price!", 50, 400, 160);
				// 
				DrawTexts("[A] Buy [D] Quit", 400, 430, 140);
			}

		}
	}
}