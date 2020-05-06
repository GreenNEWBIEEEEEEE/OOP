#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapManager.h"
#include "CMapEvent.h"
#include "CMapInfo.h"
#include "CMapFarmingEvent.h"
#include "CTool.h"

namespace game_framework
{
	CMapFarmingEvent::CMapFarmingEvent() : CMapEvent(5, 'A'){}

	CMapFarmingEvent::~CMapFarmingEvent() {}

	void CMapFarmingEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm)
	{
		// ��player��W�����u��ӨM�w�n�F��
		switch (p->GetCurrentTool())
		{
		case 0:
			Harvest(p, mm, gd); // �I�s�����l�ƥ���
			break;
			// ���Y: �Ω��~����F
		case 1:
			CutTrunk(p, mm, gd); // �I�s��~����F���l�ƥ���
			break;
		case 2:
			BreakStone(p, mm, gd); // �I�s�����l�ƥ���
			break;
		case 3:
			Hoeing(p, mm, gd); // �I�s�S�a�l�ƥ���
			break;
			// �ؤl�U: �Ω󼽺�
		case 4:
			Plant(p, mm, gd); // �I�s���ؤl�ƥ���
			break;

			// �I�M: �Ω󰣯�
		case 5:
			Weed(p, mm, gd); // �I�s���󪺤l�ƥ���
			break;

			// �����: �Ω���
		case 6:
			Water(p, mm, gd);
			break;

			// ���ʧ@
		default:
			break;
		}
	}

	int CMapFarmingEvent::getEventID() const
	{
		return CMapEvent::getEventID();
	}

	UINT CMapFarmingEvent::getKeyCode() const
	{
		return CMapEvent::getKeyCode();
	}


	///
	/// �A�Ȩƥ󪺭ӧO�ƥ�(�l�ƥ�)���l���(�Ҧp: ����/�ص浥)
	///
	// ����
	void CMapFarmingEvent::Weed(CPlayer *p, CMapManager *mm, CGameDialog *gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �Q�έ�~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);
		
		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OhasWeeds �N�i�H����; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasWeeds || landState == CMapInfo::ArableLandState::isGrowing || landState == CMapInfo::ArableLandState::wateredIsGrowing || landState == CMapInfo::ArableLandState::isMature)
				{
					eMapInfo->SetElemID(3); // �ܦ��Ŧa
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}
	// ��~����F
	void CMapFarmingEvent::CutTrunk(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �H��~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OhasWeeds �N�i�H����; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasTrunk)
				{
					eMapInfo->SetElemID(3); // �ܦ��Ŧa
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}
	// ����
	void CMapFarmingEvent::Plant(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���ˬd���a���ؤl�U�ƶq�ܤ֭n��1�H�W
		if (p->GetBackpack()->at(4)->GetNumber() < 1)
		{
			// ��ܴ��ܨõ���
			gd->AddMessage("You don't have enough seed!");
			gd->Enable();
			return; 
		}

		// ����9�c��P�N��:
		// e0 e1 e2
		// e3 pg e5
		// e6 e7 e8

		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���o����9�檺��y��
		int ex[9] = 
		{
			pgx - 1, pgx, pgx + 1,
			pgx - 1, pgx, pgx + 1,
			pgx - 1, pgx, pgx + 1,
		};
		int ey[9] =
		{
			pgy - 1, pgy - 1, pgy - 1,
			pgy, pgy, pgy,
			pgy + 1, pgy + 1, pgy + 1,
		};

		// ���ؤ@�� �����x��X�� ���O���@�U�ؤl
		// Flag �O�_���\����
		bool planted = false;

		// ����ƥ󤺮e
		for (unsigned i = 0; i < 9; ++i)
		{
			// ���oMapInfo
			CMapInfo * eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex[i], ey[i]);

			// �Ӯ椣���� �B �O�i�Ѧa
			if (eMapInfo != nullptr && eMapInfo->IsArable())
			{
				// �O�Ŧa�~�༽��
				if (eMapInfo->GetArableLandState() == CMapInfo::ArableLandState::EmptyLand)
				{
					planted = true;
					// �󴫹Ϥ�
					eMapInfo->SetElemID(5);
					// �󴫪��A
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
				}
			}
		}

		// �Y�����ءA���ؤl�U�ƶq
		if (planted)
		{
			p->GetBackpack()->at(4)->DecreaseNumber(1);
		}
	}

	// ���
	void CMapFarmingEvent::Water(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �Q�έ�~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr && eMapInfo->IsArable())
		{
			// �ˬd�i�Ѧa���A
			CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
			// �w���ؤl���O�|�����
			if (landState == CMapInfo::ArableLandState::seedPlanted)
			{
				// �󴫹ϤΪ��A
				eMapInfo->SetElemID(6);
				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredSeedPlanted);
				// ***�Ұʭp�ɾ�***
				eMapInfo->EnableGrowingCounter();
			}
			// �F��@�Ӧ������q���O�|�����
			if (landState == CMapInfo::ArableLandState::isGrowing)
			{
				// �󴫹ϤΪ��A
				eMapInfo->SetElemID(8);
				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredIsGrowing);
				// ***�Ұʭp�ɾ�***
				eMapInfo->EnableGrowingCounter();
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}

	// �Ħ�
	void CMapFarmingEvent::Harvest(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �H��~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OisMature �N�i�H����; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::isMature)
				{
					p->ChangeMoveState(CPlayer::MoveState::RadishMove);
					eMapInfo->SetElemID(3); // �ܦ��d�g
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}

	void CMapFarmingEvent::BreakStone(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �H��~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OhasStone �N�i�H�����Y; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasStone)
				{
					eMapInfo->SetElemID(3); // �ܦ��Ŧa
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}
	//�S�a
	void CMapFarmingEvent::Hoeing(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �H��~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OSoil �N�i�H�Ѧa; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::Soil)
				{
					eMapInfo->SetElemID(1); // �ܦ��P�g
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::EmptyLand);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}

	/*
	// ��A�@��
	void CMapFarmingEvent::SellCrop(CPlayer *p, CMapManager *mm, CGameDialog *gd)
	{
		// ���oplayer�{�b������y��
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// ���oplayer���V���ƥ�@�ή檺��y��
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// �H��~���o���ƥ�@�ή檺��y�� �����oMapInfo��K����ާ@, �קK�@���I�s��Ƴy���{���X����
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// �}�l���椺�e
		// ���ˬdMapInfo���S�����T����
		if (eMapInfo != nullptr)
		{
			// ���ˬd�i��
			if (eMapInfo->IsArable())
			{
				// �ˬd�i�Ѧa���A �Y�OhasWeeds �N�i�H����; �_�h���ʧ@
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasTrunk)
				{
					eMapInfo->SetElemID(3); // �ܦ��Ŧa
					// **���n: �n���ܪ��A**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// �����ƥ󤺮e
		eMapInfo = nullptr;
	}
	*/
}