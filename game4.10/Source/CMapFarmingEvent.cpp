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

	void CMapFarmingEvent::Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms)
	{
		// 看player手上拿的工具來決定要幹嘛
		switch (p->GetCurrentToolNumber())
		{
		case 0:
			Harvest(p, mm, gd); // 呼叫收成子事件函數
			break;
			// 斧頭: 用於砍年輪樹幹
		case 1:
			CutTrunk(p, mm, gd); // 呼叫砍年輪樹幹的子事件函數
			break;
		case 2:
			BreakStone(p, mm, gd); // 呼叫收成子事件函數
			break;
		case 3:
			Hoeing(p, mm, gd); // 呼叫鋤地子事件函數
			break;
			// 鐮刀: 用於除草
		case 5:
			Weed(p, mm, gd); // 呼叫除草的子事件函數
			break;
			// 澆水器: 用於澆水
		case 6:
			Water(p, mm, gd);
			break;
			// 其餘的為各種子袋子，用以播種
		default:
			Plant(p, mm, gd); // 呼叫播種子事件函數
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
	/// 農務事件的個別事件(子事件)之子函數(例如: 除草/種菜等)
	///
	// 除草
	void CMapFarmingEvent::Weed(CPlayer *p, CMapManager *mm, CGameDialog *gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 利用剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);
		
		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr)
		{
			// 先檢查可耕
			if (eMapInfo->IsArable())
			{
				// 檢查可耕地狀態 若是hasWeeds 就可以除草; 否則不動作
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				// 有雜草 or 有任何的種植狀態
				if (landState == CMapInfo::ArableLandState::hasWeeds || 
					landState >= 5)
				{
					eMapInfo->SetElemID(3); // 變成空地
					// **重要: 要改變狀態**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}
	// 砍年輪樹幹
	void CMapFarmingEvent::CutTrunk(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 以剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr)
		{
			// 先檢查可耕
			if (eMapInfo->IsArable())
			{
				// 檢查可耕地狀態 若是hasWeeds 就可以除草; 否則不動作
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasTrunk)
				{
					eMapInfo->SetElemID(3); // 變成空地
					// **重要: 要改變狀態**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}
	// 播種
	void CMapFarmingEvent::Plant(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 種子在背包的位置，表示種子的種類
		unsigned seedIndex = p->GetCurrentTool()->GetToolID();

		// 先檢查玩家的種子袋數量至少要有1以上
		if (p->GetBackpack()->at(seedIndex)->GetNumber() < 1)
		{
			// 顯示提示並結束
			gd->AddMessage("You don't have enough seed!");
			gd->Enable();
			return; 
		}

		// 播種9宮格與代號:
		// e0 e1 e2
		// e3 pg e5
		// e6 e7 e8

		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得全部9格的格座標
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

		// 播種一次 不管灑到幾格 都是扣一袋種子
		// Flag 是否成功播種
		bool planted = false;

		// 執行事件內容
		for (unsigned i = 0; i < 9; ++i)
		{
			// 取得MapInfo
			CMapInfo * eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex[i], ey[i]);

			// 該格不為空 且 是可耕地
			if (eMapInfo != nullptr && eMapInfo->IsArable())
			{
				// 是空地才能播種
				if (eMapInfo->GetArableLandState() == CMapInfo::ArableLandState::EmptyLand)
				{
					planted = true;
					// 更換圖片
					eMapInfo->SetElemID(5);
					// 更換狀態
					switch (seedIndex)
					{
					case 4:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::Radish);
						break;
					case 7:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::Potato);
						break;
					case 8:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::Tomato);
						break;
					case 9:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::EggPlant);
						break;
					case 10:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::Corn);
						break;
					case 11:
						eMapInfo->SetArableLandState(CMapInfo::ArableLandState::seedPlanted);
						eMapInfo->SetLandCrop(CMapInfo::Crop::Peanut);
						break;
					default:
						break;
					}
				}
			}
		}

		// 若有播種，扣種子袋數量
		if (planted)
		{
			p->GetBackpack()->at(seedIndex)->DecreaseNumber(1);
		}
	}

	// 澆水
	void CMapFarmingEvent::Water(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 利用剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr && eMapInfo->IsArable())
		{
			// 檢查可耕地狀態
			CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
			// 已撒種子但是尚未澆水
			if (landState == CMapInfo::ArableLandState::seedPlanted)
			{
				// 更換圖及狀態
				eMapInfo->SetElemID(6);
				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredSeedPlanted);
				// ***啟動計時器***
				eMapInfo->EnableGrowingCounter();
			}
			// 達到一個成長階段但是尚未澆水
			else if (landState == CMapInfo::ArableLandState::isGrowing1)
			{
				// 更換圖及狀態
				if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Radish)
					eMapInfo->SetElemID(8);
				else if(eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Corn)
					eMapInfo->SetElemID(37);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Tomato)
					eMapInfo->SetElemID(53);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Potato)
					eMapInfo->SetElemID(50);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Peanut)
					eMapInfo->SetElemID(47);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::EggPlant)
					eMapInfo->SetElemID(44);

				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredIsGrowing1);
				// ***啟動計時器***
				eMapInfo->EnableGrowingCounter();
			}
			else if (landState == CMapInfo::ArableLandState::isGrowing2)
			{
				// 更換圖及狀態
				if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Corn)
					eMapInfo->SetElemID(39);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Tomato)
					eMapInfo->SetElemID(55);

				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredIsGrowing2);
				// ***啟動計時器***
				eMapInfo->EnableGrowingCounter();
			}
			else if (landState == CMapInfo::ArableLandState::isGrowing3)
			{
				// 更換圖及狀態
				if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Corn)
					eMapInfo->SetElemID(41);
				else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Tomato)
					eMapInfo->SetElemID(57);

				eMapInfo->SetArableLandState(CMapInfo::ArableLandState::wateredIsGrowing3);
				// ***啟動計時器***
				eMapInfo->EnableGrowingCounter();
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}

	// 採收
	void CMapFarmingEvent::Harvest(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 以剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr)
		{
			// 先檢查可耕
			if (eMapInfo->IsArable())
			{
				// 檢查可耕地狀態 若是isMature 就可以收成; 否則不動作
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::isMature)
				{
					if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Radish)
						p->ChangeMoveState(CPlayer::MoveState::RadishMove);
					else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Corn)
						p->ChangeMoveState(CPlayer::MoveState::CornMove);
					else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::EggPlant)
						p->ChangeMoveState(CPlayer::MoveState::EggPlantMove);
					else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Tomato)
						p->ChangeMoveState(CPlayer::MoveState::TomatoMove);
					else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Potato)
						p->ChangeMoveState(CPlayer::MoveState::PotatoMove);
					else if (eMapInfo->GetCurrentCrop() == CMapInfo::Crop::Peanut)
						p->ChangeMoveState(CPlayer::MoveState::PeanutMove);

					eMapInfo->SetElemID(3); // 變成泥土
					// **重要: 要改變狀態**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
					eMapInfo->SetLandCrop(CMapInfo::Crop::None);
				}
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}

	void CMapFarmingEvent::BreakStone(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 以剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr)
		{
			// 先檢查可耕
			if (eMapInfo->IsArable())
			{
				// 檢查可耕地狀態 若是hasStone 就可以除石頭; 否則不動作
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::hasStone)
				{
					eMapInfo->SetElemID(3); // 變成空地
					// **重要: 要改變狀態**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::Soil);
				}
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}
	//鋤地
	void CMapFarmingEvent::Hoeing(CPlayer * p, CMapManager * mm, CGameDialog * gd)
	{
		// 取得player現在站的格座標
		int pgx = (p->GetBodyX() + 30) / 64, pgy = (p->GetBodyY() + 60) / 53;

		// 取得player面向的事件作用格的格座標
		int ex = pgx, ey = pgy;
		if (p->GetDirection() == 1) ey--;
		else if (p->GetDirection() == 2) ey++;
		else if (p->GetDirection() == 3) ex--;
		else ex++;

		// 以剛才取得的事件作用格的格座標 先取得MapInfo方便後續操作, 避免一直呼叫函數造成程式碼冗長
		CMapInfo *eMapInfo = mm->GetCurrentMap()->GetMapInfo(ex, ey);

		// 開始執行內容
		// 先檢查MapInfo有沒有正確取到
		if (eMapInfo != nullptr)
		{
			// 先檢查可耕
			if (eMapInfo->IsArable())
			{
				// 檢查可耕地狀態 若是Soil 就可以耕地; 否則不動作
				CMapInfo::ArableLandState landState = eMapInfo->GetArableLandState();
				if (landState == CMapInfo::ArableLandState::Soil)
				{
					eMapInfo->SetElemID(1); // 變成鬆土
					// **重要: 要改變狀態**
					eMapInfo->SetArableLandState(CMapInfo::ArableLandState::EmptyLand);
				}
			}
		}

		// 結束事件內容
		eMapInfo = nullptr;
	}
}