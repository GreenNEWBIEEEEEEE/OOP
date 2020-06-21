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
#include "CAnimalShopMenu.h"
#include "CFoodShopMenu.h"
#include "CClinic.h"

namespace game_framework
{
	CMapShopEvent::CMapShopEvent(int eventCode)
		:CMapEvent(eventCode, 0x0D)
	{

	}

	// Callback functions
	void HandlePlantShop(CGameDialog::DialogOptionsResult dor, CShopMenu *sm)
	{
		CPlantShopMenu* psm = (CPlantShopMenu*)sm;
		if (dor == CGameDialog::DialogOptionsResult::Yes)
		{
			psm->Enable_InfoBoard();
		}
		else
		{
			psm->Disable();
		}
	}
	void HandleAnimalShop(CGameDialog::DialogOptionsResult dor, CShopMenu *sm)
	{
		CAnimalShopMenu *ansm = (CAnimalShopMenu*)sm;
		if (dor == CGameDialog::DialogOptionsResult::Yes)
		{
			ansm->Enable_InfoBoard();
		}
		else
		{
			ansm->Disable();
		}
	}
	void HandleFoodShop(CGameDialog::DialogOptionsResult dor, CShopMenu *sm)
	{
		CFoodShopMenu *fsm = (CFoodShopMenu*)sm;
		if (dor == CGameDialog::DialogOptionsResult::Yes)
		{
			fsm->Enable_InfoBoard();
		}
		else
		{
			fsm->Disable();
		}
	}
	void HandleClinic(CGameDialog::DialogOptionsResult dor, CShopMenu *sm)
	{
		CClinic *clinic = (CClinic*)sm;
		if (dor == CGameDialog::DialogOptionsResult::Yes)
		{
			clinic->Enable_InfoBoard();
		}
		else
		{
			clinic->Disable();
		}
	}

	void CMapShopEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CPlantShopMenu * psm = (CPlantShopMenu*)sms.at(0);
		CAnimalShopMenu * ansm = (CAnimalShopMenu*)sms.at(1);
		CFoodShopMenu *fsm = (CFoodShopMenu*)sms.at(2);
		CClinic *clinic = (CClinic*)sms.at(3);
		
		switch (eventCode)
		{
		case 6: // Plant Shop
		{
			if (psm->GetTimer()->GetHour() >= 19)
			{
				gd->AddMessage("Closed now!");
				gd->Enable();
			}
			else
			{
				psm->Enable();
				gd->SetCallback(&HandlePlantShop, psm);
				gd->AddQuestion("Do you want to buy some seed?");
				gd->AddOptionResultMessage("Welcome to this shop.", "Good Bye!");
				gd->Enable();
			}
			break;
		}
		case 7: // Animal Shop
		{
			if (ansm->GetTimer()->GetHour() >= 19)
			{
				gd->AddMessage("Closed now!");
				gd->Enable();
			}
			else
			{
				ansm->Enable();
				gd->SetCallback(&HandleAnimalShop, ansm);
				gd->AddQuestion("Do you want to buy some animals?");
				gd->AddOptionResultMessage("Welcome to this shop.", "Good Bye!");
				gd->Enable();
			}
			break;
		}
		case 8: // Food Shop
		{
			if (fsm->GetTimer()->GetHour() >= 19)
			{
				gd->AddMessage("Closed now!");
				gd->Enable();
			}
			else
			{
				fsm->Enable();
				gd->SetCallback(&HandleFoodShop, fsm);
				gd->AddQuestion("Do you want to buy some food?");
				gd->AddOptionResultMessage("Welcome to this shop.", "Good Bye!");
				gd->Enable();
			}
			break;
		}
		case 9:
		{
			if (clinic->GetTimer()->GetHour() >= 19)
			{
				gd->AddMessage("Closed now!");
				gd->Enable();
			}
			else
			{
				clinic->Enable();
				gd->SetCallback(&HandleClinic, clinic);
				gd->AddQuestion("Do you want to see a doctor?");
				gd->AddOptionResultMessage("Welcome to this clinic.", "Good Bye!");
				gd->Enable();
			}
			break;
		}
		default:
			break;
		}
	}

	
}