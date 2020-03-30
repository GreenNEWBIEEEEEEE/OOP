<<<<<<< HEAD
#pragma once
=======
#ifndef CPLAYER_H
#define CPLAYER_H
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
namespace game_framework {

	class CGameMap;
	class CMapManager;
	class CGameDialog;
	class CPlayer
	{
	public:
		CPlayer();
		~CPlayer();

		///
		/// �s��Player���ݩʡB�X��
		///
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
<<<<<<< HEAD
		void SetX(int x);
		void SetY(int y);
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		int GetLastX() const;
		int GetLastY() const;

		///
		/// �C���y�{
		///
		void LoadBitmap();
		void OnMove(CGameMap* m);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd);

=======
		void OnMove(CGameMap *m);
		void OnShow(CGameMap *m);
		
		void OnKeyDown(UINT key, CGameMap *m);
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
	private:
		// ���a����Ϥ��e��
		int width, height;
		// ���a�b�a�ϤW���y��(�I�y��)
		int x, y;
		// �W�@���O�s����m(�i�Ω��������m�٭�)
		int lastX, lastY;
		// ���a�{�b�b���i�a��/�����W
		int mapID; 
		// ���a�W�@���b���ӳ���(�i�Ω�����٭�)
		int lastMapID;

		// ���ʪ��ʵe
		CAnimation *facingDirection = nullptr; // ���V��e���V����V���ʵe
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;

		// ���A�X�� : �O�_�W/�U/��/�k��
		bool isMovingLeft , isMovingRight, isMovingUp, isMovingDown;
	};
}
#endif