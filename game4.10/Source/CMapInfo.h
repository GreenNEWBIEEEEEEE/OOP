#pragma once
#include "CGameDialog.h"
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
			isGrowing,                    // 有作物正在成長中
			wateredIsGrowing,             // 有作物正在成長中並且已澆水
			isMature,                     // 作物已成熟待採收
		};

		CMapInfo();
		CMapInfo(int elemID);
		~CMapInfo();

		void SetElemID(int elemID);

		int GetElemID() const;

		// 加入事件，外部僅需傳入事件碼(event code)，AddEvent就會根據事件碼加入相應的事件。
		void AddEvent(int eventCode);

		bool hasEvents() const;

		void triggerEventByKeyCode(UINT keyCode, CPlayer *p, CMapManager * mm, CGameDialog *gd);

		bool IsEmpty() const;

		bool IsArable() const;

		CMapInfo::ArableLandState GetArableLandState() const;

		void SetArableLandState(CMapInfo::ArableLandState state);

		void EnableGrowingCounter();

		void DisableGrowingCounter();
		
		bool IsGrowingCounterEnable() const;
		
		void CountForGrowing();

		void OnMove();

	private:
		int elemID;
		std::vector<CMapEvent*> events;

		bool isArable; // 可耕種與否
		CMapInfo::ArableLandState landState;

		
		bool isGrowingCounterEnable = false;
		const int GROWING_COUNTER_MAX = 350;
		int growingCounter = 0;
		
	};
}
