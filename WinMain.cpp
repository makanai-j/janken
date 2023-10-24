#include <time.h>
#include "DxLib.h"
#include "fps.h"
#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				 // Log.txtを出力しない
	ChangeWindowMode(true);								 // ウィンドウモード変更
	SetGraphMode(GAMEWIDTH, GAMEHEIGHT, GAMECOLOR);		//解像度設定
	SetWindowSize(GAMEWIDTH, GAMEHEIGHT);				//ウィンドウの大きさを設定
	SetMainWindowText("じゃンけんゲーム");				//ウィンドウのタイトル
	SetBackgroundColor(0, 0, 0);						//ウィンドウの背景色
	SetWaitVSyncFlag(true);								//垂直同期の設定
	SetAlwaysRunFlag(true);								//非アクティブでも実行する


	SetWindowIconID(GAMEICON);								//アイコンを設定


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) {
		return -1;   // エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);			//裏画面に描画する（ダブルバッファリング）

	FPSInit();								//FPS初期化
	
	KeyInit();								//キーボード初期化

	MouseInit();							//マウス初期化

	NowGameScene = TitleScene;				//タイトルからスタート
	//NowGameScene = BoutScene;				//タイトルからスタート

	TitleScene();							//タイトル初期化

	Data_Teigi();							//データ定義

	SetDrawMode(DX_DRAWMODE_BILINEAR);		// 描画モードをバイリニアフィルタリングにする

	srand((unsigned int)time(NULL));		//乱数の種の変更

	while (true) {

		//メッセージ処理をする
		if (ProcessMessage() != 0) {
			break;							//無限ループから出る（ゲーム終了）
		}

		//画面を消去する（1ループずつ書き換える）
		if (ClearDrawScreen() != 0) {		//無限ループから出る（ゲーム終了）
			break;
		}

		//ゲーム動作
		{
			FPSCheck();			//FPS計測
			KeyUpdate();		//キーボード更新
			MouseUpdate();		//マウス更新

			//シーン切り替え
			switch (NowGameScene)
			{
			case TitleScene:
				TitleCtrl();
				break;
			case RuleScene:
				RuleCtrl();
				break;
			case SelectionScene:
				SelectionCtrl();
				break;
			case CheckScene:
				CheckCtrl();
				break;
			case BoutScene:
				BoutCtrl();
				break;
			case ScoreScene:
				ScoreCtrl();
				break;
			case ResultScene:
				ResultCtrl();
				break;
			default:
				break;
			}

			ModeView();			//中央上モード表示
			PopUpView();		//左上ポップアップ表示

			OldGameScene = NowGameScene;    //直前のゲームシーンのぽ更新

			FPSWait();			//FPS待機
		}



		//裏外面を画面に描画
		ScreenFlip();
	}
	InitFontToHandle();		//全フォントデータの消去
	InitGraph();			//全画像データ消去
	FileRead_close(FileHandle_Rule);

	DxLib_End();    // ＤＸライブラリ使用の終了処理

	return 0;    // ソフトの終了 
}