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

	void CAnimal::SetMap(CGameMap* map)
	{
		this->map = map;
	}

	void CAnimal::SetTimer(CTimer* timer)
	{
		this->timer = timer;
	}

	void CAnimal::OnMove(CGameMap* m, vector<CGameObject*>* obj){
		if (timer->IsNewDay())
		{

			if (currentStatus == Status::NoProduce)     
			{
				//if(地圖有草堆)
				currentStatus = Status::Produce;
				//else if(地圖沒草堆)
				//HP -= 34;
				//currentStatus = Status::Hungry;
			}
			else if (currentStatus == Status::Hungry)  
			{
				//if(地圖有草堆)
				//HP += 15;                        // 這邊的+= -=都要改用function，因為有邊界判斷
				//else if (地圖沒草堆)
				//HP -= 34;
				if (healthPoint == 100)
				{
					currentStatus = Status::Produce;
				}
			}

		}
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

