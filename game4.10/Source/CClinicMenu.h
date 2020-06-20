#pragma once
#include "CShopMenu.h"

namespace game_framework
{
	class CClinic : public CShopMenu
	{
	public:
		CClinic(CPlayer *p, CGameDialog *gd, CTimer *timer);
		void OnKeyDown(UINT key);
		void LoadBitmap();
		void OnShow();
		void OnMove();
	private:
		CMovingBitmap hp_up;
	};
}