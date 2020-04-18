#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolHoe.h"

namespace game_framework {

	CToolHoe::CToolHoe(int toolID, int number) : CTool(toolID, number) { toolName = "Hoe"; }
	CToolHoe::~CToolHoe() {}

}