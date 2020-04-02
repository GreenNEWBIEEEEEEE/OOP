#pragma once
#include "CGameDialog.h"
namespace game_framework {
	class CMapInfo {
	public:
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
		
	private:
		int elemID;
		std::vector<CMapEvent*> events;
		
	};
}
