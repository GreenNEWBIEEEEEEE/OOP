#pragma once

namespace game_framework {
	class CAnimal;
	class CGameMap;
	class CGameObject
	{
	public:
		CGameObject();
		~CGameObject();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void SetX(int x);
		void SetY(int y);
		void SetBodyX(int bx);
		void SetBodyY(int by);
		void SetCollision(bool flag);
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		int GetHealthPoint() const;
		int GetBodyX() const;
		int GetBodyY() const;
		int GetLastX() const;
		int GetLastY() const;
		void DecreaseHP(int hp);
		void IncreaseHP(int hp);
		CAnimal* GetFacingAnimal();
		bool DetectCollision(vector<CGameObject*>* obj, int nextX, int nextY);
		virtual void OnMove(CGameMap* m, vector<CGameObject*>* obj) = 0;
		virtual void OnShow(CGameMap* m) = 0;
		virtual void LoadBitmap() = 0;

	protected:

		// �ثe�@��i���a��(�]�t�W�U���k ���u�� �u��ʧ@) "����" ���O 128*120
		// ���a����Ϥ��e��
		int width, height;
		int STEP_SIZE = 5;
		// ���a�b�a�ϤW���y��(�I�y��)
		int x, y;   // ��i�Ϫ��I�y��
		int bx, by; // ���a�u������(body)���I�y��
		int ex, ey; // ���aĲ�o�ƥ��I�y��

		// �W�@���O�s����m(�i�Ω��������m�٭�)
		int lastX, lastY;

		bool collision = true;

		CAnimal* facingAnimal = nullptr;

		// ���A�X�� : �O�_�W/�U/��/�k��
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

		int healthPoint;

	};


}