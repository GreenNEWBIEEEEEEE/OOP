#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapInfo.h"
#include "CMapTransitionEvent.h"
#include "CMapFarmingEvent.h"
#include "CMapShowDialogEvent.h"
#include "CMapShopEvent.h"
#include "CWeather.h"
#include "CMapManager.h"



namespace game_framework{

	 // 可耕地狀態
	enum ArableLandState;

	CMapInfo::CMapInfo() : elemID(0)
	{
		isArable = false;
	}

	CMapInfo::CMapInfo(int elemID)
	{
		this->elemID = elemID;
		switch (this->elemID)
		{
		case 1:
			isArable = true;
			landState = CMapInfo::ArableLandState::EmptyLand;
			break;
		case 3:
			isArable = true;
			landState = CMapInfo::ArableLandState::Soil;
			break;
		case -3:
			isArable = true;
			landState = CMapInfo::ArableLandState::hasWeeds;
			break;
		case -5:
			isArable = true;
			landState = CMapInfo::ArableLandState::hasTrunk;
			break;
		default:
			break;
		}
	}

	CMapInfo::~CMapInfo()
	{
		for (unsigned i = 0; i < events.size(); ++i) 
		{
			delete events[i];
			events[i] = nullptr;
		}
	}

	void CMapInfo::SetElemID(int elemID)
	{
		this->elemID = elemID;
		switch (this->elemID)
		{
		case 1:
			isArable = true;
			landState = CMapInfo::ArableLandState::EmptyLand;
			break;
		case 3:
			landState = CMapInfo::ArableLandState::Soil;
			break;
		case -3:
			isArable = true;
			landState = CMapInfo::ArableLandState::hasWeeds;
			break;
		case -5:
			isArable = true;
			landState = CMapInfo::ArableLandState::hasTrunk;
			break;
		default:
			break;
		}
	}

	int CMapInfo::GetElemID() const
	{
		return elemID;
	}

	// 新增事件 這裡也要註冊
	void CMapInfo::AddEvent(int eventCode)
	{
		switch (eventCode)
		{
		case 5:
			events.push_back(new CMapFarmingEvent());
			break;
		case 6:
			events.push_back(new CMapShopEvent(6));
			break;
		case 10001:
			events.push_back(new CMapShowDialogEvent(10001));
			break;
		case 10002:
			events.push_back(new CMapShowDialogEvent(10002));
			break;
		case 10003:
			events.push_back(new CMapShowDialogEvent(10003));
			break;
		case 10004:
			events.push_back(new CMapShowDialogEvent(10004));
			break;
		case 10005:
			events.push_back(new CMapShowDialogEvent(10005));
			break;
		case 10006:
			events.push_back(new CMapShowDialogEvent(10006));
			break;
		case 10007:
			events.push_back(new CMapShowDialogEvent(10007));
			break;
		case 10008:
			events.push_back(new CMapShowDialogEvent(10008));
			break;
		case 20001:
			events.push_back(new CMapTransitionEvent(20001));
			break;
		case 20002:
			events.push_back(new CMapTransitionEvent(20002));
		default:
			break;
		}
	}

	bool CMapInfo::hasEvents() const
	{
		return events.size() > 0;
	}

	void CMapInfo::triggerEventByKeyCode(UINT keyCode, CPlayer *p, CMapManager * mm, CGameDialog *gd, CShopMenu *sm)
	{
		for (unsigned i = 0; i < events.size(); ++i)
		{	
			// 如果player按的key 所對應的事件存在的話，執行事件

			if (events[i]->getKeyCode() == keyCode) {
				TRACE("\nAn event triggered.\n");
				events[i]->Execute(p, mm, gd, sm);

				///
				/// FOR DEBUGGING
				/// 
				if (events[i]->getEventID() == 5)
				{
					TRACE("\nFarming Event Triggered\n");
				}
			}
		}
	}

	bool CMapInfo::IsEmpty() const
	{
		return elemID >= 0;
	}

	bool CMapInfo::IsArable() const
	{
		return isArable;
	}

	CMapInfo::ArableLandState CMapInfo::GetArableLandState() const
	{
		return landState;
	}

	void CMapInfo::SetArableLandState(CMapInfo::ArableLandState state)
	{
		this->landState = state;
	}
	void CMapInfo::EnableGrowingCounter()
	{
		isGrowingCounterEnable = true;
	}
	void CMapInfo::DisableGrowingCounter()
	{
		isGrowingCounterEnable = false;
	}
	bool CMapInfo::IsGrowingCounterEnable() const
	{
		return isGrowingCounterEnable;
		
	}
	void CMapInfo::CountForGrowing(CTimer* timer)
	{
		TRACE("\n NewDay = %d  Hour = %d   Counter = %d\n", timer->IsNewDay(), timer->GetHour(), timer->GetHourCounter());
		if (timer->IsNewDay())
		{
			if (isArable)
			{
				if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
				{
					landState = CMapInfo::ArableLandState::isGrowing;
					elemID = 7;
				}
				else if (landState == CMapInfo::ArableLandState::wateredIsGrowing) {
					landState = CMapInfo::ArableLandState::isMature;
					elemID = 9;
				}
			}
			isGrowingCounterEnable = false;
		}
	}

	void CMapInfo::OnMove(CTimer* timer, CWeather* weather)
	{
		bool destroy = false;
		if (isGrowingCounterEnable)
		{
			CountForGrowing(timer);
		}

		if (weather != nullptr)
		{
			if (weather->ForecastWeather() == "Rainy")
			{
				if (isArable)
				{
					switch (elemID) {
					case 5:
						SetElemID(6);
						landState = wateredSeedPlanted;
						EnableGrowingCounter();
						break;
					case 7:
						SetElemID(8);
						landState = wateredIsGrowing;
						EnableGrowingCounter();
						break;
					default:
						break;
					}
				}
			}
			else if (weather->ForecastWeather() == "Typhoon")
			{
				//TRACE("\n NewDay = %d  Hour = %d   Counter = %d\n", timer->IsNewDay(), timer->GetHour(), timer->GetHourCounter());
				if (isArable)
				{
					if (timer->IsNewDay())
						destroy = (rand() % 100) >= 80; // 20%機率颱風摧毀

					if (destroy)
					{
						SetElemID(3);
						landState = Soil;
					}
				}
			}
		}
	}
}