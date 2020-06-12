#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CTool.h"

namespace game_framework {
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
		case 4:			// 白蘿蔔種子
			icon = &radishSeed;
				break;
		case 5:			// 鐮刀
			icon = &sickle;
				break;
		case 6:			// 澆水器
			icon = &waterer;
				break;
		case 7:			// 馬鈴薯種子袋
			icon = &potatoSeed;
			break;
		case 8:			// 番茄種子袋
			icon = &tomatoSeed;
			break;
		case 9:			// 茄子種子袋
			icon = &eggPlantSeed;
			break;
		case 10:			// 玉米種子袋
			icon = &cornSeed;
			break;
		case 11:			// 花生種子袋
			icon = &peanutSeed;
			break;
		default:
			break;
		}
	}
	CTool::~CTool()
	{

	}

	void CTool::LoadBitmap()
	{
		hand.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		axe.LoadBitmap(IDB_Axe, RGB(255, 255, 255));
		hammer.LoadBitmap(IDB_Hammer, RGB(255, 255, 255));
		hoe.LoadBitmap(IDB_Hoe, RGB(255, 255, 255));
		radishSeed.LoadBitmap(IDB_Seed01, RGB(255, 255, 255));
		sickle.LoadBitmap(IDB_Sickle, RGB(255, 255, 255));
		waterer.LoadBitmap(IDB_WateringCan, RGB(255, 255, 255));
	}

	bool CTool::IsEnable() const
	{
		return number > 0;
	}

	int CTool::GetToolID() const
	{
		return toolID;
	}

	int CTool::GetNumber() const
	{
		return this->number;
		return 0;
	}

	void CTool::ShowIcon(int x, int y)
	{
		icon->SetTopLeft(x, y);
		icon->ShowBitmap();
	}

	string CTool::GetInfo() const
	{
		return toolName + "  *" + to_string(number);
	}

	void CTool::IncreaseNumber(int number)
	{
		if (number > 0)
		{
			this->number += number;
		}
	}

	void CTool::DecreaseNumber(int number)
	{
		if (this->number >= number)
		{
			this->number -= number;
		}
	}

	

}