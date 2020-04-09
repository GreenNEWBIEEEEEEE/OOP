//
// 現在Event Code (事件碼) 扮演一個相當重要的角色
// 因為有些事件的真實內容多有不同，例如：
// 對話框的對話內容每個當然都不一樣；場景轉換中要轉換的場景也不同，如從野外到房子或從房子到野外
// 因此，event code 就能夠代表，同一"種"事件，不同的內容
// 因此，就用event code 來進行不同內容的hard coding
// 遊戲越龐大，當然比較好的方式是把內容提取出來作為腳本之類的
// 不過以我們的專題來看，現在這樣也沒什麼不好
// 那，代表事件種類的獨一無二的代號，目前就是用key code來表示
// 也就是說，玩家按不同key來觸發不同"種類"的事件
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
