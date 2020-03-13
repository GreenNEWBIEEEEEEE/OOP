namespace game_framework {
	class CCat
	{
	public:
		CCat();
		void LoadBitmap();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetMovingDown(bool flag);
		void OnMove();
		void OnShow();
		
	
	private:
		CMovingBitmap bmp;
		int x, y;
		bool is_angry;
		bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	
	};
}



