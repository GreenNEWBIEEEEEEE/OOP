#pragma once
#include "CGameDialog.h"
#include "CShopMenu.h"
#include "CPlantShopMenu.h"

namespace game_framework {
	class CMapInfo {
	public:
		// �i�Ѧa���A
		enum ArableLandState 
		{
			Soil,                         // �d�g
			EmptyLand,                    // �Ŧa
			hasWeeds,                     // ������
			hasStone,					  // �����Y
			hasTrunk,                     // ����F

			seedPlanted,                  // �w�����ؤl                
			wateredSeedPlanted,           // �w�����ؤl�åB�w���
			isGrowing1,                    // ���@�����b������
			wateredIsGrowing1,             // ���@�����b�������åB�w���
			isGrowing2,                    // ���@�����b������
			wateredIsGrowing2,             // ���@�����b�������åB�w���
			isGrowing3,                    // ���@�����b������
			wateredIsGrowing3,             // ���@�����b�������åB�w���
			isMature,                     // �@���w�����ݱĦ�

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

		// �[�J�ƥ�A�~���ȻݶǤJ�ƥ�X(event code)�AAddEvent�N�|�ھڨƥ�X�[�J�������ƥ�C
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

		bool isArable; // �i�ѺػP�_
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
