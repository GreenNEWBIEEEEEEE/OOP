#pragma once
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
		void SetX(int x);
		void SetY(int y);
		int GetWidth() const;
		int GetHeight() const;
		int GetX() const;
		int GetY() const;
		int GetBodyX() const;
		int GetBodyY() const;
		int GetLastX() const;
		int GetLastY() const;
		int GetDirection() const;
		int GetCurrentTool() const;

		///
		/// �C���y�{
		///
		void LoadBitmap();
		void OnMove(CGameMap* m);
		void OnShow(CGameMap* m);
		void OnKeyDown(UINT key, CMapManager *mm, CGameDialog *gd);
		void OnKeyUp(UINT key, CMapManager *mm, CGameDialog *gd);

	private:
		// �ثe�@��i���a��(�]�t�W�U���k ���u�� �u��ʧ@) "����" ���O 128*120
		// ���a����Ϥ��e��
		int width, height;

		// ���a�b�a�ϤW���y��(�I�y��)
		int x, y;   // ��i�Ϫ��I�y��
		int bx, by; // ���a�u������(body)���I�y��
		int ex, ey; // ���aĲ�o�ƥ��I�y��
		
		// �W�@���O�s����m(�i�Ω��������m�٭�)
		int lastX, lastY;

		// ���a��V�X��
		// 1=�W, 2=�U, 3=��, 4=�k
		int direction = 2;
		int lastDirection;
		
		// ���a�{�b�b���i�a��/�����W
		int mapID; 
		
		// ���a�W�@���b���ӳ���(�i�Ω�����٭�)
		int lastMapID;

		// ���ʪ��ʵe
		CAnimation *lastFacingDirection = nullptr;
		CAnimation *facingDirection = nullptr; // ���V��e���V����V���ʵe
		CAnimation aniMoveLeft, aniMoveRight, aniMoveUp, aniMoveDown;
		// ���A�X�� : �O�_�W/�U/��/�k��
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;

		/*
		CAnimation aniPlantLeft, aniPlantRight, aniPlantUp, aniPlantDown;
		bool isPlantingLeft, isPlantingRight, isPlantingRight, isPlantingRight;
		*/

		// �󴫤u�㪺�ʵe
		CAnimation aniChangeTool_0;
		CAnimation aniChangeTool_1;
		CAnimation aniChangeTool_2;
		CAnimation aniChangeTool_3;
		CAnimation aniChangeTool_4;
		CAnimation aniChangeTool_5;
		CAnimation aniChangeTool_6;

		// �ϥΤu�㪺�ʵe
		bool isUsingTool = false;
		CAnimation aniUseTool_0;
		CAnimation aniUseTool_1_front;
		CAnimation aniUseTool_1_back;
		CAnimation aniUseTool_1_left;
		CAnimation aniUseTool_1_right;

		CAnimation aniUseTool_2_front;
		CAnimation aniUseTool_2_back;
		CAnimation aniUseTool_2_left;
		CAnimation aniUseTool_2_right;

		CAnimation aniUseTool_3_front;
		CAnimation aniUseTool_3_back;
		CAnimation aniUseTool_3_left;
		CAnimation aniUseTool_3_right;

		CAnimation aniUseTool_4;

		CAnimation aniUseTool_5_front;
		CAnimation aniUseTool_5_back;
		CAnimation aniUseTool_5_left;
		CAnimation aniUseTool_5_right;

		CAnimation aniUseTool_6_front;
		CAnimation aniUseTool_6_back;
		CAnimation aniUseTool_6_left;
		CAnimation aniUseTool_6_right;

		// �u/�D�㪺�I�]
		vector<int> tool;
		unsigned int toolSelector;
	};
}