#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolHand.h"

namespace game_framework {

	CToolHand::CToolHand(int toolID, int number) : CTool(toolID, number) { toolName = "Hand"; }
	CToolHand::~CToolHand() {}

}