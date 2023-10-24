//マウス処理のヘッダファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"
#include "game_sistem.h"

//マクロ定義
#define MOUSEKINDMAX 8					//マウスのボタンの種類
#define MOUSECODEERRINDEX 999			//マウスコードを変換した要素番号のエラー値

#define CASUALMOUSE_1(x,y)  720 - y - 0.8 * x - 102			//float型 (カジュアルの当たり判定)
#define CASUALMOUSE_2(x,y)  720 - y + 0.8 * x - 1083.6		//float型 (カジュアルの当たり判定)
#define CASUALMOUSE_3(x,y)  720 - y - 0.8 * x + 231.6		//float型 (カジュアルの当たり判定)
#define CASUALMOUSE_4(x,y)  720 - y + 0.8 * x - 1418		//float型 (カジュアルの当たり判定)

#define HARDMOUSE_1(x,y)  720 - y - 0.8 * x + 128		//float型 (ハードの当たり判定)
#define HARDMOUSE_2(x,y)  720 - y + 0.8 * x - 937.6		//float型 (ハードの当たり判定)
#define HARDMOUSE_3(x,y)  720 - y - 0.8 * x + 628		//float型 (ハードの当たり判定)

//構想体
typedef struct _MousePoint{
	int x;		//マウスのXの位置
	int y;		//マウスのYの位置
}MousePoint;

//外部のプロトタイプ宣言
extern void MouseNowIntoOld(void);					//Now○○系の変数の値をOld○○系の変数へ入れる
extern int MouseCodeToIndex(int MOUSE_INPUT_);		//マウスのボタンコードを配列の要素番号に変換する


extern void MouseInit(void);						//マウス処理の初期化
extern void MouseUpdate(void);						//マウス処理の更新
extern bool MouseDown(int MOUSE_INPUT_);				//特定のボタンを押したか
extern bool MouseClick(int MOUSE_INPUT_);				//特定のボタンをクリックしたか
extern bool MouseHere(void);							//範囲内かを判定
extern int  MousePressFrame(int MOUSE_INPUT_);		//特定のボタンを押したフレーム数


extern MousePoint GetPointMouse(void);				//マウスの現在位置を取得する
extern MousePoint GetOldPointMouse(void);			//マウスの前の位置を取得する
extern MousePoint GetDiffPointMouse(void);			//マウスの前と現在の差を取得する

extern int GetWheelMouse(void);						//マウスの現在のホイール量を取得する

//当たり判定
extern bool RuleBottun(Mode Bottun, int x, int y);			//ルール画面ボタン
extern bool BoxBottun(int rx, int ry, int lx, int ly);		//四角のボタン
extern bool CircleBottunClick(int x, int y, int r);			//マルのボタンクリック
extern bool CircleBottunOn(int x, int y, int r);			//マルのボタン乗ると