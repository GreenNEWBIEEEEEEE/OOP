#pragma once

#include "CMapEvent.h"

namespace game_framework
{
	class CMapFarmingEvent : public CMapEvent
	{
	public:
		CMapFarmingEvent();
		~CMapFarmingEvent();

		void Execute(
			CPlayer *p, 
			CMapManager *mm, 
			CGameDialog *gd, 
			vector<CShopMenu*> sms
		);

		int getEventID() const;

		UINT getKeyCode() const;

	private:
		///
		/// �A�Ȩƥ󪺭ӧO�ƥ�(�l�ƥ�)���l���(�Ҧp: ����/�ص浥)
		/// �]���A�Ȩƥ�O�]�t�۷�s���ƥ� 
		/// �]����ӧO�ƥ������l��� �o��execute�N���|�g�Ӫ�!
		/// ��M �o�ǬO�Ѫ��󤺳���execute�I�s �ҥH�Oprivate����
		///
		// ����l�ƥ�
		void Weed(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// ��~����F�l�ƥ�
		void CutTrunk(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// ���ؤl�ƥ�
		void Plant(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// ����l�ƥ�
		void Water(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// �Ħ��l�ƥ�
		void Harvest(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// �S�a�l�ƥ�
		void Hoeing(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// �}�a���Y�ƥ�
		void BreakStone(CPlayer *p, CMapManager *mm, CGameDialog *gd);
	};
}