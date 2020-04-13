#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolHammer.h"

namespace game_framework {

	CToolHammer::CToolHammer(int toolID, int number) : CTool(toolID, number) {}
	CToolHammer::~CToolHammer() {}

}