#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
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

	}
	CTool::~CTool()
	{

	}

	void CTool::LoadBitmap()
	{
		//TODO:載入Icon圖
		switch (toolID)
		{
		case 0:			// 手
			break;
		case 1:			// 斧頭
			break;
		case 2:			// 槌子
			break;
		case 3:			// 鋤頭
			break;
		case 4:			// 種子袋
			break;
		case 5:			// 鐮刀
			break;
		case 6:			// 澆水器
			break;
		default:
			break;
		}
	}

}