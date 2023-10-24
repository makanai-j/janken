//ゲーム処理のソースファイル

//ヘッダファイル読み込み
#include "game.h"
#include "key.h"

//グローバル変数

//ゲームシーン
GameScene NowGameScene;		//現在のゲームシーン

//ゲームシーンの名前
char GameSceneName[GAMESCENECOUNT][GAMESCENENAMEMAX]
{
	"タイトル画面",
	"プレイ画面",
	"リザルト画面"
};

//関数

//タイトル初期化
void TitleInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

		ScreenFlip();
		WaitTimer(2000);
	}

	return;
}
//タイトル管理
void TitleCtrl(void)
{
	TitleProc();	//処理をしてから
	TitleDraw();	//描画する

	return;
}
//タイトル処理
void TitleProc(void)
{
	//シーン切り替え（スペースキーが押されたとき）
	if (KeyClick(KEY_INPUT_SPACE) == true){

		//切り替え
		NowGameScene = PlayScene;

		//プレイ画面初期化
		PlayInit();

		return;
	}

	return;
}
//タイトル描画
void TitleDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == TitleScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(255,123,15), true);

		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "描画中");
	}

	return;
}

//プレイ初期化
void PlayInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");


		ScreenFlip();
		WaitTimer(2000);
	}

	return;
}
//プレイ管理
void PlayCtrl(void)
{
	PlayProc();	//処理をしてから
	PlayDraw();	//描画する

	return;
}
//プレイ処理
void PlayProc(void)
{
	//シーン切り替え（スペースキーが押されたとき）
	if (KeyClick(KEY_INPUT_SPACE) == true) {

		//切り替え
		NowGameScene = ResultScene;

		//リザルト画面初期化
		ResultInit();

		return;
	}

	return;
}
//プレイ描画
VOID PlayDraw(VOID)
{
	if (GAMEDEBUG == TRUE && NowGameScene == PlayScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(177, 210, 25), TRUE);

		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "描画中");
	}

	return;
}

//リザルト初期化
VOID ResultInit(VOID)
{
	if (GAMEDEBUG == TRUE) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

		ScreenFlip();
		WaitTimer(2000);
	}

	return;
}
//リザルト管理  
VOID ResultCtrl(VOID)
{
	ResultProc();	//処理をしてから
	ResultDraw();	//描画する

	return;
}
//リザルト処理  
VOID ResultProc(VOID)
{
	//シーン切り替え（スペースキーが押されたとき）
	if (KeyClick(KEY_INPUT_SPACE) == TRUE) {

		//切り替え
		NowGameScene = TitleScene;

		//プレイ画面初期化
		TitleInit();

		return;
	}

	return;
}
//リザルト描画  
VOID ResultDraw(VOID)
{
	if (GAMEDEBUG == TRUE && NowGameScene == ResultScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(177, 21, 255), TRUE);

		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "描画中");
	}

	return;
}