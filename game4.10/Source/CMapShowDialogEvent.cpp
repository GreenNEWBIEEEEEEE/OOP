#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameDialog.h"
#include "CMapShowDialogEvent.h"

namespace game_framework
{
	CMapShowDialogEvent::CMapShowDialogEvent(int eventCode)
		: CMapEvent(eventCode, ' ')
	{

	}

	CMapShowDialogEvent::~CMapShowDialogEvent()
	{
	}

	void CMapShowDialogEvent::Execute(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		switch (eventCode)
		{
		case 10001:
			gd->AddMessage("Welcome to play this game.");
			gd->AddMessage("Have fun!");
			gd->Enable();
			break;
		case 10002:
			gd->AddMessage("Press W to change tools.");
			gd->AddMessage("Now you have :");
			gd->AddMessage("An axe.");
			gd->AddMessage("A hammer.");
			gd->AddMessage("A hoe.");
			gd->AddMessage("A seed bag.");
			gd->AddMessage("A waterer.");
			gd->AddMessage("A sickle.");
			gd->Enable();
			break;
		case 10003:
			gd->AddMessage("Press A to Use tool.");
			gd->AddMessage("Do some agricultural work.");
			gd->AddMessage("Good luck!");
			gd->Enable();
			break;
		case 10004:
			gd->AddMessage("This is a notice board.");
			gd->Enable();
			break;
		case 10005:
			gd->AddMessage("Here is your home.");
			gd->Enable();
			break;
		default:
			break;
		}
	}


}