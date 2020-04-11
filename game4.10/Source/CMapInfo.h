#pragma once
#include "CGameDialog.h"
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
			isGrowing,                    // ���@�����b������
			wateredIsGrowing,             // ���@�����b�������åB�w���
			isMature,                     // �@���w�����ݱĦ�
		};

		CMapInfo();
		CMapInfo(int elemID);
		~CMapInfo();

		void SetElemID(int elemID);

		int GetElemID() const;

		// �[�J�ƥ�A�~���ȻݶǤJ�ƥ�X(event code)�AAddEvent�N�|�ھڨƥ�X�[�J�������ƥ�C
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

		bool isArable; // �i�ѺػP�_
		CMapInfo::ArableLandState landState;

		
		bool isGrowingCounterEnable = false;
		const int GROWING_COUNTER_MAX = 350;
		int growingCounter = 0;
		
	};
}
