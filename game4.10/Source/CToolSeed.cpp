#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolSeed.h"

namespace game_framework {

	CToolSeed::CToolSeed(int toolID, int number) : CTool(toolID, number) {}
	CToolSeed::~CToolSeed() {}

}