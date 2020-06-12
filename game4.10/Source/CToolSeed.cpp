#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolSeed.h"

namespace game_framework {

	CToolSeed::CToolSeed(int toolID, int number) : CTool(toolID, number) 
	{ 
		switch (toolID)
		{
		case 4:
			toolName = "Radish";
			break;
		case 7:
			toolName = "Potato";
			break;
		case 8:
			toolName = "Tomato";
			break;
		case 9:
			toolName = "EggPlant";
			break;
		case 10:
			toolName = "Corn";
			break;
		case 11:
			toolName = "Peanut";
			break;
		default:
			toolName = "";
			break;
		}
	}
	CToolSeed::~CToolSeed() {}

}