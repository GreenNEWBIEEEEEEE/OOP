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
			toolName = "Seed of Radish";
			break;
		case 7:
			toolName = "Seed of Potato";
			break;
		case 8:
			toolName = "Seed of Tomato";
			break;
		case 9:
			toolName = "Seed of EggPlant";
			break;
		case 10:
			toolName = "Seed of Corn";
			break;
		case 11:
			toolName = "Seed of Peanut";
			break;
		default:
			toolName = "";
			break;
		}
	}
	CToolSeed::~CToolSeed() {}

}