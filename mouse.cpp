//マウス処理のソースファイル

//ヘッダファイル読み込み
#include "mouse.h"
#include "PopUp.h"
#include "game_scene.h"
#include "game_sistem.h"
#include <math.h>

//グローバル変数
MousePoint NowPoint;				//現在のマウスの位置
MousePoint OldPoint;				//以前のマウスの位置

int NowMousePressFrame[MOUSEKINDMAX];	//現在のマウスのボタンを押しているフレーム数を管理
int OldMousePressFrame[MOUSEKINDMAX];	//以前のマウスのボタンを押しているフレーム数を管理

int NowWheelValue;					//現在のマウスのホイール回転量
int OldWheelValue;				//以前のマウスのホイール回転量

//マウスのボタンコードとフレーム数を管理している配列の要素数を紐づける
int MouseCodeIndex[MOUSEKINDMAX]{
	MOUSE_INPUT_LEFT,				//配列の要素数0にはマウスのボタン情報の0x0001の情報を入れる
	MOUSE_INPUT_RIGHT,				//配列の要素数1にはマウスのボタン情報の0x0002の情報を入れる
	MOUSE_INPUT_MIDDLE,				//配列の要素数2にはマウスのボタン情報の0x0004の情報を入れる
	MOUSE_INPUT_4,					//配列の要素数3にはマウスのボタン情報の0x0008の情報を入れる
	MOUSE_INPUT_5,					//配列の要素数4にはマウスのボタン情報の0x0010の情報を入れる
	MOUSE_INPUT_6,					//配列の要素数5にはマウスのボタン情報の0x0020の情報を入れる
	MOUSE_INPUT_7,					//配列の要素数6にはマウスのボタン情報の0x0040の情報を入れる
	MOUSE_INPUT_8,					//配列の要素数7にはマウスのボタン情報の0x0080の情報を入れる
};

//Now○○系の変数の値をOld○○系の変数へ入れる
void MouseNowIntoOld(void)
{
	OldPoint = NowPoint;		//マウスの位置
	
	//フレーム数
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}

	//ホイール量
	OldWheelValue = NowWheelValue;

	return;
}

//マウスのボタンコードを配列の要素数に変換する
int MouseCodeToIndex(int MOUSE_INPUT_)
{
	for (int i = 0; i < MOUSEKINDMAX; i++) {

		//マウスコードが紐づけされているなら
		if (MouseCodeIndex[i] == MOUSE_INPUT_) {

			return i;
		}
	}
	//マウスコードがないならエラー
	return MOUSECODEERRINDEX;
}

//マウス処理の処理の初期化
void MouseInit(void)
{
	//マウス処理の初期化
	NowPoint.x = 0;
	NowPoint.y = 0;

	//フレーム数
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		NowMousePressFrame[i] = 0;
	}

	//ホイール量
	NowWheelValue = 0;

	//old系も初期化
	MouseNowIntoOld();

	return;
}

//マウス処理の更新
void MouseUpdate(void)
{
	//マウスのボタン情報をすべて取得する変数
	int Input;

	//現在の情報を以前の情報として保存
	MouseNowIntoOld();

	//現在のマウスのクライアント座標の位置を取得　
	GetMousePoint(&NowPoint.x, &NowPoint.y);		
	//GetMousePoint(&NowPoint.xのアドレス, &NowPoint.yのアドレス)
	//NowPoint.xにX座標の値が入って戻ってくる。yも同様。

	//もし、マウスの座標がゲーム画面外にあるなら、ゲーム画面内に収める
	if (NowPoint.x < 0) { NowPoint.x = 0;} //左
	else if (NowPoint.x > GAMEWIDTH) { NowPoint.x = GAMEWIDTH; } //右
	if (NowPoint.y < 0) { NowPoint.y = 0; } //上
	else if (NowPoint.y > GAMEHEIGHT) { NowPoint.y = GAMEHEIGHT; } //下

	//マウスのボタン情報を一気に取得
	Input = GetMouseInput();

	//各ボタンを押しているかチェック
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		/* [if分の条件説明]
		   まず　８７６５４中右左
				 １１１１１１１１　　といったように、2進数の
				 それぞれの桁にマウス各ボタンが割り振られている。（中はホイール）

				 これを&演算でマスク処理することで
				 どこのボタンが押されたのかを判断することが可能。

				 （例）右ボタンが押されたとき
				 00000010 & 00000001 = 00000000   左じゃないなー
				 00000010 & 00000010 = 00000010   右だ！
		 */
		if ((Input & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			//現在押しているボタンのフレーム数をカウントアップ
			NowMousePressFrame[i]++;
		}
		else if ((Input & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			//現在押しているボタンのフレーム数をゼロクリア
			NowMousePressFrame[i] = 0;
		}
	}

	//ホイール回転量を取得
	NowWheelValue = GetMouseWheelRotVol();

	return;
}

//特定のマウスを押したか
//引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
bool MouseDown(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//実在するマウスコードなら
	if (index != MOUSECODEERRINDEX) {
		//現在押しているなら
		if (NowMousePressFrame[index] > 0) {

			return true;		//押している
		}
	}


	return FALSE;			//押してない
}


//特定のマウスを押したか
//引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
//説明：「マウスボタンを押す→マウスボタンを上げる」がセットで行われた時が、クリック
bool MouseClick(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//実在するマウスコードなら
	if (index != MOUSECODEERRINDEX) {
		//現在押しているなら
		if (NowMousePressFrame[index]  == 0			//現在は押していないが
			&& OldMousePressFrame[index] > 0) {		//前は押していた

			return true;		//押している
		}
	}

	return FALSE;			//押してない
}

//マウスの現在位置が指定の場所にあるか(ボタン用)
bool MouseHere(void)
{
	if (NowPoint.x > 590 && NowPoint.x < 690				//xの範囲内かつ
		&& NowPoint.y > 500 && NowPoint.y < 550) {			//yの範囲内
		
		return true;
	}
	
	return false;
}

//特定のマウスボタンを押したフレーム数
//引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
//戻り値はフレーム数
int MousePressFrame(int MOUSE_INPUT_)
{
	//マウスコードを配列の要素数に変換
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//実在するマウスコードなら
	if (index != MOUSECODEERRINDEX) {

		return NowMousePressFrame[index];
	}


	return 0;
}

//マウスの現在位置を取得する
MousePoint GetPointMouse(void)
{
	return NowPoint;
}

//マウスの前の位置を取得する
MousePoint GetOldPointMouse(void)
{
	return OldPoint;
}

//マウスの現在位置を取得する
MousePoint GetDiffPointMouse(void)
{
	MousePoint diff;
	diff.x = OldPoint.x - NowPoint.x;
	diff.y = OldPoint.y - NowPoint.y;
	return diff;
}

//マウスの現在のホイール量を取得する
int GetWheelMouse(void)
{
	return NowWheelValue;
}

//ボタンの当たり判定
//ルール画面
bool RuleBottun(Mode Bottun, int x, int y)
{
	switch (Bottun) {
	case Casual_1:
		if (720 - y - 0.8 * x - 102 < 0			//float型 (カジュアルの当たり判定)
		&& 720 - y + 0.8 * x - 1083.6 < 0	//float型 (カジュアルの当たり判定)
		&& 170 < y && y < 250) {			//カジュアルか判定
			DrawStringToHandle(600, 180, "1", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Casual_3:
		if (720 - y + 0.8 * x - 1083.6 > 0		//float型 (カジュアルの当たり判定)
		&& 720 - y - 0.8 * x + 231.6 > 0	//float型 (カジュアルの当たり判定)
		&& 170 < y && y < 250){				//カジュアルか判定
			DrawStringToHandle(810, 180, "3", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Casual_5:
		if (720 - y - 0.8 * x + 231.6 < 0		//float型 (カジュアルの当たり判定)
		&& 720 - y + 0.8 * x - 1418 < 0		//float型 (カジュアルの当たり判定)
		&& 170 < y && y < 250){				//カジュアルか判定
			DrawStringToHandle(1020, 180, "5", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Hard_5:
		if (720 - y - 0.8 * x + 128	< 0			//float型 (カジュアルの当たり判定)
		&& 720 - y + 0.8 * x - 937.6 < 0	//float型 (カジュアルの当たり判定)
		&& 400 < y && y < 480){				//ハードか判定
			DrawStringToHandle(650, 410, "5", GETCOLOR_DARKRED_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Hard_10:
		if (720 - y + 0.8 * x - 937.6 > 0		//float型 (カジュアルの当たり判定)
		&& 720 - y - 0.8 * x + 628 > 0		//float型 (カジュアルの当たり判定)
		&& 400 < y && y < 480){				//ハードか判定
			DrawStringToHandle(950, 410, "10", GETCOLOR_DARKRED_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
	}
	return false;
	/*
	720 - y - 0.8 * x - 102			//float型 (カジュアルの当たり判定)
	720 - y + 0.8 * x - 1083.6		//float型 (カジュアルの当たり判定)
	720 - y - 0.8 * x + 231.6		//float型 (カジュアルの当たり判定)
	720 - y + 0.8 * x - 1418		//float型 (カジュアルの当たり判定)
	
	720 - y - 0.8 * x + 128		//float型 (ハードの当たり判定)
	720 - y + 0.8 * x - 937.6	//float型 (ハードの当たり判定)
	720 - y - 0.8 * x + 628		//float型 (ハードの当たり判定)
	*/
}
//四角ボタン
bool BoxBottun(int rx, int ry, int lx, int ly)
{
	if (rx < GetPointMouse().x && GetPointMouse().x < lx
		&& ry < GetPointMouse().y && GetPointMouse().y < ly
		&& MouseClick(MOUSE_INPUT_LEFT) == true) {
		return true;
	}
	return false;
}
//マルのボタン
//クリック
bool CircleBottunClick(int x, int y, int r)
{
	double dis;		//中心とマウスの距離
	int dis_x;		//中心 x 座標とマウス x の差
	int dis_y;		//中心 y 座標とマウス y の差

	dis_x = x - GetPointMouse().x;
	dis_y = y - GetPointMouse().y;
	dis = sqrt(pow(dis_x, 2) + pow(dis_y, 2));

	if (dis < r		//指定した半径より内側か
		&& MouseClick(MOUSE_INPUT_LEFT) == true) {
		return true;
	}
	return false;
}
//のる
bool CircleBottunOn(int x, int y, int r)
{
	double dis;		//中心とマウスの距離
	int dis_x;		//中心 x 座標とマウス x の差
	int dis_y;		//中心 y 座標とマウス y の差

	dis_x = x - GetPointMouse().x;
	dis_y = y - GetPointMouse().y;
	dis = sqrt(pow(dis_x, 2) + pow(dis_y, 2));

	if (dis < r) {	//指定した半径より内側か
		return true;
	}
	return false;
}