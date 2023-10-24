//ゲームシーン切替関係のヘッダファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"

//マクロ定義
#define GAMEWIDTH 1280  //画面の幅
#define GAMEHEIGHT 720  //画面の高さ
#define GAMECOLOR 32   //画面の色
#define GAMEICON 1001  //画面アイコン

#define GAMEDEBUG true	//デバッグモード

#define GAMESCENECOUNT 7 //ゲームシーンの数
#define GAMESCENENAMEMAX 20 //ゲームシーン名の文字MAX

#define GETCOLOR_BLACK_ GetColor(0,0,0)		    //黒色
#define GETCOLOR_WHITE_ GetColor(255,255,255)   //白色
#define GETCOLOR_RED_ GetColor(255,0,0)		    //赤色(明るい)
#define GETCOLOR_DARKRED_ GetColor(180,0,0)		//赤色(暗い)
#define GETCOLOR_GREEN_ GetColor(0,150,0)       //緑色
#define GETCOLOR_BLUE_ GetColor(0,0,255)	    //青色
#define GETCOLOR_PURPLE_ GetColor(255,0,255)    //紫色
#define GETCOLOR_ORANGE_ GetColor(255,100,0)    //オレンジ色
#define GETCOLOR_YELLOW_ GetColor(255,215,0)    //黄色
#define GETCOLOR_CYAN_ GetColor(0,149,141)      //シアン

//ゲームシーン
typedef enum {
	TitleScene,		//タイトルシーン
	RuleScene,		//ルールシーン
	SelectionScene,	//選択シーン
	CheckScene,		//確認シーン
	BoutScene,		//勝負シーン
	ScoreScene,		//スコアシーン
	ResultScene		//リザルトシーン
}GameScene;
//外部のグローバル変数
extern GameScene NowGameScene;		//現在のゲームシーン
extern GameScene OldGameScene;		//直前のゲームシーン
//外部のプロトタイプ宣言
extern void TitleInit(void);		//タイトル初期化
extern void TitleCtrl(void);		//タイトル管理
extern void TitleProc(void);		//タイトル処理
extern void TitleDraw(void);		//タイトル描画

extern void RuleInit(void);		    //選択初期化
extern void RuleCtrl(void);		    //選択管理
extern void RuleProc(void);		    //選択処理
extern void RuleDraw(void);		    //選択描画

extern void SelectionInit(void);		//選択初期化
extern void SelectionCtrl(void);		//選択管理
extern void SelectionProc(void);		//選択処理
extern void SelectionDraw(void);		//選択描画

extern void CheckInit(void);		//確認初期化
extern void CheckCtrl(void);		//確認管理
extern void CheckProc(void);		//確認処理
extern void CheckDraw(void);		//確認描画

extern void BoutInit(void);		//勝負初期化
extern void BoutCtrl(void);		//勝負管理
extern void BoutProc(void);		//勝負処理
extern void BoutDraw(void);		//勝負描画

extern void ScoreInit(void);		//スコア初期化
extern void ScoreCtrl(void);		//スコア管理
extern void ScoreProc(void);		//スコア処理
extern void ScoreDraw(void);		//スコア描画

extern void ResultInit(void);		//リザルト初期化
extern void ResultCtrl(void);		//リザルト管理
extern void ResultProc(void);		//リザルト処理
extern void ResultDraw(void);		//リザルト描画
