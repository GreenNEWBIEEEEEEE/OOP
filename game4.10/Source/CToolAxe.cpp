#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CTool.h"
#include "CToolAxe.h"

namespace game_framework {

	CToolAxe::CToolAxe(int toolID, int number) : CTool(toolID, number) { toolName = "Axe"; }
	CToolAxe::~CToolAxe() {}

}