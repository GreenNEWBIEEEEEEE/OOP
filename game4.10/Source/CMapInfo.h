#pragma once
#include "CGameDialog.h"
#include "CShopMenu.h"
#include "CPlantShopMenu.h"

namespace game_framework {
	class CMapInfo {
	public:
		// 可耕地狀態
		enum ArableLandState 
		{
			Soil,                         // 泥土
			EmptyLand,                    // 空地
			hasWeeds,                     // 有雜草
			hasStone,					  // 有石頭
			hasTrunk,                     // 有樹幹

			seedPlanted,                  // 已播撒種子                
			wateredSeedPlanted,           // 已播撒種子並且已澆水
			isGrowing1,                    // 有作物正在成長中
			wateredIsGrowing1,             // 有作物正在成長中並且已澆水
			isGrowing2,                    // 有作物正在成長中
			wateredIsGrowing2,             // 有作物正在成長中並且已澆水
			isGrowing3,                    // 有作物正在成長中
			wateredIsGrowing3,             // 有作物正在成長中並且已澆水
			isMature,                     // 作物已成熟待採收

		};

		enum Crop {
			None,
			Radish,
			Corn,
			Potato,
			Tomato,
			EggPlant,
			Peanut
		};

		CMapInfo();
		CMapInfo(int elemID);
		~CMapInfo();

		void SetElemID(int elemID);

		int GetElemID() const;

		// 加入事件，外部僅需傳入事件碼(event code)，AddEvent就會根據事件碼加入相應的事件。
		void AddEvent(int eventCode);

		bool hasEvents() const;

		void triggerEventByKeyCode(
			UINT keyCode, 
			CPlayer *p, 
			CMapManager * mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms
		);

		bool IsEmpty() const;

		bool IsArable() const;

		CMapInfo::ArableLandState GetArableLandState() const;

		CMapInfo::Crop GetCurrentCrop() const;

		void SetLandCrop(CMapInfo::Crop crop);

		void SetArableLandState(CMapInfo::ArableLandState state);

		void EnableGrowingCounter();

		void DisableGrowingCounter();
		
		bool IsGrowingCounterEnable() const;
		
		void CountForGrowing(CTimer* timer);

		void OnMove(CTimer* timer, CWeather* weather);

	private:
		int elemID;
		std::vector<CMapEvent*> events;

		bool isArable; // 可耕種與否
		CMapInfo::ArableLandState landState;
		CMapInfo::Crop landCrop = Crop::None;
		
		bool isGrowingCounterEnable = false;
		
	private:
		void StateMachine_Radish();
		void StateMachine_Potato();
		void StateMachine_Tomato();
		void StateMachine_EggPlant();
		void StateMachine_Corn();
		void StateMachine_Peanut();
	};
}
