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

namespace game_framework
{
	CMapShopEvent::CMapShopEvent(int eventCode)
		:CMapEvent(eventCode, 'H')
	{

	}

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

	void CMapShopEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
		CPlantShopMenu * psm = ((CPlantShopMenu*)sm);
		switch (eventCode)
		{
		case 6: // Plant Shop
			psm->Enable(p, gd);
			gd->SetCallback(&HandlePlantShop, sm);
			gd->AddQuestion("Do you want to buy some seed?");
			gd->AddOptionResultMessage("Welcome to this shop.", "Good Bye!");
			gd->Enable();
			break;
		case 7:
			break;
		default:
			break;
		}
	}

	
}