#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CTool.h"

namespace game_framework {
	bool CTool::IsEnable()
	{
		return number > 0;
	}

	CTool::CTool(int toolID, int number)
	{
		this->toolID = toolID;
		this->number = number;

		switch (toolID)
		{
		case 0:			// 手
			icon = &hand;
				break;
		case 1:			// 斧頭
			icon = &axe;
				break;
		case 2:			// 槌子
			icon = &hammer;
				break;
		case 3:			// 鋤頭
			icon = &hoe;
				break;
		case 4:			// 種子袋
			icon = &seed01;
				break;
		case 5:			// 鐮刀
			icon = &sickle;
				break;
		case 6:			// 澆水器
			icon = &waterer;
				break;
		default:
			break;
		}
	}
	CTool::~CTool()
	{

	}

	int CTool::GetToolID()
	{
		return toolID;
	}

	void CTool::ShowIcon(int x, int y)
	{
		icon->SetTopLeft(x, y);
		icon->ShowBitmap();
	}
	string CTool::GetInfo()
	{
		return toolName + "  *" + to_string(number);
	}
	void CTool::LoadBitmap()
	{
		hand.LoadBitmap(IDB_Axe);
		axe.LoadBitmap(IDB_Axe);
		hammer.LoadBitmap(IDB_Hammer);
		hoe.LoadBitmap(IDB_Hoe);
		seed01.LoadBitmap(IDB_Seed01);
		sickle.LoadBitmap(IDB_Sickle);
		waterer.LoadBitmap(IDB_WateringCan);
	}

}