#pragma once

#include "CMapShowDialogEvent.h"

namespace game_framework {

	class CGameDialog {
	public:
		enum class DialogOptionsResult {
			Yes,
			No,
		};
		typedef void(*Callback) (void);
		typedef void(*CallbackForChangeToNewDay) (DialogOptionsResult, CTimer*, CWeather*);
		typedef void(*CallbackWithResult)(DialogOptionsResult);
		typedef void(*CallbackWithResultForShopMenu)(DialogOptionsResult, CShopMenu*);
		typedef void(*CallbackForTransitionMap)(CMapManager*, CPlayer*);

		CGameDialog();
		~CGameDialog();
		void AddMessage(string msg);
		void AddQuestion(string q);
		void AddOptionResultMessage(string msgForYes, string msgForNo);
		
		DialogOptionsResult GetCurrentOptionResult() const;

		void SetCallback(Callback cbp);
		void SetCallback(CallbackWithResult cbp);
		void SetCallback(CallbackWithResultForShopMenu cbp, CShopMenu* sm);
		void SetCallback(CallbackForChangeToNewDay cbp, CTimer* timer, CWeather* weather);	
		void SetCallback(CallbackForTransitionMap cbp, CMapManager* mm, CPlayer* p);
		void Enable();
		void Disable();

		bool IsEnable() const;

		void LoadBitmap();
		void OnKeyDown(UINT key);
		void OnMove();
		void OnShow();

	private:
		// DialogMessage物件
		struct GameDialogMessage
		{
			// message種類
			enum class MessageType
			{
				Normal,
				Question,
				OptionResult,
			};

			// 建立normal message 或 question message
			GameDialogMessage(string msg, bool isQuestion)
			{
				messageText = msg;
				if (isQuestion) 
				{
					messageType = MessageType::Question;
				}
				else
				{
					messageType = MessageType::Normal;
				}
			}

			// 建立 option result 的 message
			GameDialogMessage(string msgForYes, string msgForNo)
			{
				messageType = MessageType::OptionResult;
				messageForYes = msgForYes;
				messageForNo = msgForNo;
			}

			~GameDialogMessage()
			{
			}

			string messageForYes = "";
			string messageForNo = "";
			string messageText = "";

			bool IsQuestion() const
			{
				return messageType == MessageType::Question;
			}

			void SetMessageTextForOptionResult(DialogOptionsResult dor)
			{
				result = dor;
			}
			string GetMessageText() const
			{
				if (messageType != MessageType::OptionResult)
				{
					return messageText;
				}
				else
				{
					if (result == DialogOptionsResult::Yes)
						return messageForYes;
					else
						return messageForNo;
				}
			}

			// 表示該DialogMessage物件的message種類
			MessageType messageType = MessageType::Normal;
			DialogOptionsResult result = DialogOptionsResult::Yes;


		};

		// GameDialog所需
		vector<GameDialogMessage> dialogMessages;
		string messageToShow;
		unsigned msgSelector;
		unsigned ss;
		CMovingBitmap background;
		CMovingBitmap backgroundOnOptionYes;
		CMovingBitmap backgroundOnOptionNo;
		CMovingBitmap imageBackground;
		CMovingBitmap characterAvatar;
		// GameDialog狀態Flags
		bool enable;
		bool canContinue;
		bool isOnQuestion;
		bool done;
		bool allDone;
		// 當前對話框選項的結果, 每一次讓使用者選擇完就更新, 需要取用選擇結果可以用這個
		CGameDialog::DialogOptionsResult currentOptionResult;

		// Callback function pointer
		Callback cbFunc = nullptr;
		CallbackWithResult cbfwdor = nullptr;
		CallbackWithResultForShopMenu cbfwdor_sm = nullptr;
		CallbackForChangeToNewDay cbfctnd = nullptr;
		CallbackForTransitionMap cbftm = nullptr;


		CShopMenu *sm = nullptr;
		CTimer* timer = nullptr;
		CWeather* weather = nullptr;
		CMapManager* mm = nullptr;
		CPlayer* p = nullptr;

	private:
		void DrawTexts(CString text, int posX, int posY, int fontSize);

	};

}