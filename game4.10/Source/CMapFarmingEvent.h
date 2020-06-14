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
		/// 農務事件的個別事件(子事件)之子函數(例如: 除草/種菜等)
		/// 因為農務事件是包含相當廣的事件 
		/// 因此把個別事件拆分成子函數 這樣execute就不會寫太長!
		/// 當然 這些是由物件內部的execute呼叫 所以是private成員
		///
		// 除草子事件
		void Weed(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 砍年輪樹幹子事件
		void CutTrunk(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 播種子事件
		void Plant(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 澆水子事件
		void Water(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 採收子事件
		void Harvest(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 鋤地子事件
		void Hoeing(CPlayer *p, CMapManager *mm, CGameDialog *gd);
		// 破壞石頭事件
		void BreakStone(CPlayer *p, CMapManager *mm, CGameDialog *gd);
	};
}