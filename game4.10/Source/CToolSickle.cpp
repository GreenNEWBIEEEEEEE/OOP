#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CToolSickle.h"

namespace game_framework {

	CToolSickle::CToolSickle(int toolID, int number) : CTool(toolID, number) {}
	CToolSickle::~CToolSickle() {}

}