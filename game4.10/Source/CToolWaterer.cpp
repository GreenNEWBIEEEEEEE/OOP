#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolWaterer.h"

namespace game_framework {

	CToolWaterer::CToolWaterer(int toolID, int number) : CTool(toolID, number) {}
	CToolWaterer::~CToolWaterer() {}

}