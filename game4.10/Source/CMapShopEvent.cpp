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
#include "CToolsMachinesShopMenu.h"

namespace game_framework
{
	CMapShopEvent::CMapShopEvent(int eventCode)
		:CMapEvent(eventCode, 'H')
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
	void HandleToolsMachinesShop(CGameDialog::DialogOptionsResult dor, CShopMenu *sm)
	{
		CToolsMachinesShopMenu *tmsm = (CToolsMachinesShopMenu*)sm;
		if (dor == CGameDialog::DialogOptionsResult::Yes)
		{
			tmsm->Enable_InfoBoard();
		}
		else
		{
			tmsm->Disable();
		}
	}

	void CMapShopEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		CPlantShopMenu * psm = ((CPlantShopMenu*)sms.at(0));
		CAnimalShopMenu * ansm = ((CAnimalShopMenu*)sms.at(1));
		CToolsMachinesShopMenu *tmsm = ((CToolsMachinesShopMenu*)sms.at(2));
		
		switch (eventCode)
		{
		case 6: // Plant Shop
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
		case 7: // Animal Shop
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
		case 8: // ToolsMachines Shop
			if (tmsm->GetTimer()->GetHour() >= 19)
			{
				gd->AddMessage("Closed now!");
				gd->Enable();
			}
			else
			{
				tmsm->Enable();
				gd->SetCallback(&HandleAnimalShop, tmsm);
				gd->AddQuestion("Do you want to buy some tools?");
				gd->AddOptionResultMessage("Welcome to this shop.", "Good Bye!");
				gd->Enable();
			}
			break;
		default:
			break;
		}
	}

	
}