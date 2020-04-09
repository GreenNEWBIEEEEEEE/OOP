//
// �{�bEvent Code (�ƥ�X) ��t�@�Ӭ۷��n������
// �]�����Ǩƥ󪺯u�ꤺ�e�h�����P�A�Ҧp�G
// ��ܮت���ܤ��e�C�ӷ�M�����@�ˡF�����ഫ���n�ഫ�������]���P�A�p�q���~��Фl�αq�Фl�쳥�~
// �]���Aevent code �N����N��A�P�@"��"�ƥ�A���P�����e
// �]���A�N��event code �Ӷi�椣�P���e��hard coding
// �C���V�e�j�A��M����n���覡�O�⤺�e�����X�ӧ@���}��������
// ���L�H�ڭ̪��M�D�ӬݡA�{�b�o�ˤ]�S���򤣦n
// ���A�N��ƥ�������W�@�L�G���N���A�ثe�N�O��key code�Ӫ��
// �]�N�O���A���a�����Pkey��Ĳ�o���P"����"���ƥ�
//

#pragma once

#include "CMapManager.h"

namespace game_framework{
	class CMapEvent
	{
	public:
		CMapEvent(int eventCode, UINT keyCode);
		virtual ~CMapEvent() {};
		
		virtual void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd) = 0;
		int getEventID() const;
		UINT getKeyCode() const;

	protected:
		const int eventCode;
		const UINT keyCode;


	};
}
