#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CGameObject.h" 
#include "CPlayer.h"
#include "CMapManager.h"
#include "CAnimal.h"
#include "CGameMap.h"
#include "CTimer.h"

namespace game_framework
{
	CAnimal::CAnimal()
	{
	}

	CAnimal::~CAnimal()
	{
	}

	void CAnimal::Reset()
	{
		x = bx = resetX;
		y = by = resetY;
		EnableShowAndMove();
		SetCollision(true);
	}

	void CAnimal::UnableShowAndMove()
	{
		onShowAndMove = false;
	}

	void CAnimal::EnableShowAndMove()
	{
		onShowAndMove = true;
	}

	void CAnimal::SetMap(CGameMap* map)
	{
		this->map = map;
	}

	void CAnimal::SetTimer(CTimer* timer)
	{
		this->timer = timer;
	}

	CGameMap* CAnimal::GetMap()
	{
		return map;
	}

	void CAnimal::SetPickUp(bool flag)
	{
		isPickedUp = flag;
	}


	void CAnimal::ChangeStatus(Status status)
	{
		currentStatus = status;
	}

	CAnimal::Status CAnimal::GetCurrentStatus()
	{
		return currentStatus;
	}


}

