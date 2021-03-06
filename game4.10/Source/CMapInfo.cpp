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
#include "CMapSleepEvent.h"



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

	// 事件註冊
	void CMapInfo::AddEvent(int eventCode)
	{
		if (eventCode >= 10000 && eventCode <= 19999)
		{
			events.push_back(new CMapShowDialogEvent(eventCode));
		}
		else if (eventCode >= 20000 && eventCode <= 29999)
		{
			events.push_back(new CMapTransitionEvent(eventCode));
		}
		else if (eventCode >= 30000 && eventCode <= 30001)
		{
			events.push_back(new CMapSleepEvent(eventCode));
		}
		else if (eventCode >= 6 && eventCode <= 9)
		{
			events.push_back(new CMapShopEvent(eventCode));
		}
		else if (eventCode == 5)
		{
			events.push_back(new CMapFarmingEvent());
		}
	}

	bool CMapInfo::hasEvents() const
	{
		return events.size() > 0;
	}

	void CMapInfo::triggerEventByKeyCode(
		UINT keyCode, 
		CPlayer *p, 
		CMapManager * mm, 
		CGameDialog *gd, 
		vector<CShopMenu*> sms)
	{
		for (unsigned i = 0; i < events.size(); ++i)
		{	
			// 如果player按的key 所對應的事件存在的話，執行事件

			if (events[i]->getKeyCode() == keyCode) {
				TRACE("\nAn event triggered.\n");
				events[i]->Execute(p, mm, gd, sms);

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

	CMapInfo::Crop CMapInfo::GetCurrentCrop() const
	{
		return landCrop;
	}

	void CMapInfo::StateMachine_Radish()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isGrowing1;
			elemID = 7;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing1) {
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 9;
		}
	}

	void CMapInfo::StateMachine_Potato()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 51;
		}

	}

	void CMapInfo::StateMachine_Tomato()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isGrowing1;
			elemID = 52;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing1)
		{
			landState = CMapInfo::ArableLandState::isGrowing2;
			elemID = 54;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing2) {
			landState = CMapInfo::ArableLandState::isGrowing3;
			elemID = 56;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing3) {
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 58;
		}

	}

	void CMapInfo::StateMachine_EggPlant()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 45;
		}
	}

	void CMapInfo::StateMachine_Corn()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isGrowing1;
			elemID = 36;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing1)
		{
			landState = CMapInfo::ArableLandState::isGrowing2;
			elemID = 38;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing2) {
			landState = CMapInfo::ArableLandState::isGrowing3;
			elemID = 40;
		}
		else if (landState == CMapInfo::ArableLandState::wateredIsGrowing3) {
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 42;
		}

	}

	void CMapInfo::StateMachine_Peanut()
	{
		if (landState == CMapInfo::ArableLandState::wateredSeedPlanted)
		{
			landState = CMapInfo::ArableLandState::isMature;
			elemID = 48;
		}
	}

	void CMapInfo::SetLandCrop(CMapInfo::Crop crop)
	{
		landCrop = crop;
	}

	void CMapInfo::CountForGrowing(CTimer* timer)
	{
		TRACE("\n NewDay = %d  Hour = %d   Counter = %d\n", timer->IsNewDay(), timer->GetHour(), timer->GetHourCounter());
		if (timer->IsNewDay())
		{
			if (isArable)
			{
				if (landCrop == Crop::Radish)
					StateMachine_Radish();
				else if (landCrop == Crop::Peanut)
					StateMachine_Peanut();
				else if (landCrop == Crop::Potato)
					StateMachine_Potato();
				else if (landCrop == Crop::Tomato)
					StateMachine_Tomato();
				else if (landCrop == Crop::Corn)
					StateMachine_Corn();
				else if (landCrop == Crop::EggPlant)
					StateMachine_EggPlant();
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
					case 5:				// 白蘿蔔
						SetElemID(6);
						landState = wateredSeedPlanted;
						EnableGrowingCounter();
						break;
					case 7:
						SetElemID(8);
						landState = wateredIsGrowing1;
						EnableGrowingCounter();
						break;
					case 36:			//玉米
						SetElemID(37);
						landState = wateredIsGrowing1;
						EnableGrowingCounter();
						break;
					case 38:
						SetElemID(39);
						landState = wateredIsGrowing2;
						EnableGrowingCounter();
						break;
					case 40:
						SetElemID(41);
						landState = wateredIsGrowing3;
						EnableGrowingCounter();
						break;
					case 52:			//番茄
						SetElemID(53);
						landState = wateredIsGrowing1;
						EnableGrowingCounter();
						break;
					case 54:
						SetElemID(55);
						landState = wateredIsGrowing2;
						EnableGrowingCounter();
						break;
					case 56:
						SetElemID(57);
						landState = wateredIsGrowing3;
						EnableGrowingCounter();
						break;
					case 43:			// 茄子
						SetElemID(44);
						landState = wateredIsGrowing1;
						EnableGrowingCounter();
						break;
					case 46:			// 花生
						SetElemID(47);
						landState = wateredIsGrowing1;
						EnableGrowingCounter();
						break;
					case 49:			// 馬鈴薯
						SetElemID(50);
						landState = wateredIsGrowing1;
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
						landCrop = None;
					}
				}
			}
		}
	}
}