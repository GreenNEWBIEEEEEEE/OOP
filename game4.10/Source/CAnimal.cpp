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
				//if(�a�Ϧ����)
				currentStatus = Status::Produce;
				//else if(�a�ϨS���)
				//HP -= 34;
				//currentStatus = Status::Hungry;
			}
			else if (currentStatus == Status::Hungry)  
			{
				//if(�a�Ϧ����)
				//HP += 15;                        // �o�䪺+= -=���n���function�A�]������ɧP�_
				//else if (�a�ϨS���)
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

