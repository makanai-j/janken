//ゲームシステムのソースファイル

//ヘッダファイル読み込み
#include <stdlib.h>

#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"

//変数
Mode NowMode = NonMode;

Dasite Dasite_1 = Nonselect;		//　初めの出し手	　( Nonselectで初期化 )
Dasite Dasite_2 = Nonselect;		//　次の出し手 　	　( Nonselectで初期化 )
Dasite Misete_1 = Nonselect;		//　初めの見せ手	　( Nonselectで初期化 )
Dasite Misete_2 = Nonselect;		//　次の見せ手 　	　( Nonselectで初期化 )
Dasite Syoubute_You = Nonselect;	//　自分の勝負する手　( Nonselectで初期化 )
Dasite Enemyte_1 = Nonselect;		//　初めの見せ手 　   ( Nonselectで初期化 )
Dasite Enemyte_2 = Nonselect;		//　次の見せ手 　     ( Nonselectで初期化 )
Dasite Syoubute_Enemy = Nonselect;	//　敵の勝負する手 　 ( Nonselectで初期化 )

int Point_You = 0;  	//自分のポイント
int Point_Enemy = 0;	//敵のポイント

int BoutPointCheck_You = 999;							//勝負ポイント判断の変数(カジュアルかハードかの判断にも使える)
int BoutPointCheck_Enemy = 999;							//勝負ポイント判断の変数(カジュアルかハードかの判断にも使える)

//勝ち負けの判断表
int Victory_or_Defeat[TEKAZU][TEKAZU]{
	//グー、チョキ、パー
	   2,     0,     1,    4,   //グー
	   1,     2,     0,    4,	  //チョキ
	   0,     1,     2,    4,	  //パー
	   3,     3,     3,    0
};
//モードによるポイント表
int BoutPoint[TEKAZU1][TEKAZU2]{
	//勝ち、負け、あいこ
	   3,    -1,    0,    1,   -1,	  //同じ出して
	   2,    -1,    0,    1,   -1,	  //異なる出して
	   1,     0,    0,    1,   -1,	  //カジュアルモード
};

//関数
//モード選択 (ルール処理の判定 に使用)
bool ModeSelect()
{
	if (KeyClick(KEY_INPUT_Q) == true
		|| RuleBottun(Casual_1, GetPointMouse().x, GetPointMouse().y) == true) {
		NowMode = Casual_1;
	}
	else if (KeyClick(KEY_INPUT_W) == true
		|| RuleBottun(Casual_3, GetPointMouse().x, GetPointMouse().y) == true) {
		NowMode = Casual_3;
	}
	else if (KeyClick(KEY_INPUT_E) == true
		|| RuleBottun(Casual_5, GetPointMouse().x, GetPointMouse().y) == true) {
		NowMode = Casual_5;
	}
	else if (KeyClick(KEY_INPUT_A) == true
		|| RuleBottun(Hard_5, GetPointMouse().x, GetPointMouse().y) == true) {
		NowMode = Hard_5;
	}
	else if (KeyClick(KEY_INPUT_S) == true
		|| RuleBottun(Hard_10, GetPointMouse().x, GetPointMouse().y) == true) {
		NowMode = Hard_10;
	}
	else return false;

	return true;
}

//出し手の選択 (選択処理の判定 に使用)
bool DasiteCheck(void)
{
	if (KeyClick(KEY_INPUT_1)		//グーの判定
		|| CircleBottunClick(340,560,140)) {		
		if(Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Gu;
		else if(Dasite_2 == Nonselect && (Dasite_1 != Gu || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Gu;
	}
	else if (KeyClick(KEY_INPUT_2)		//チョキの判定
		|| CircleBottunClick(640, 560, 140)) {
		if (Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Tyo;
		else if (Dasite_2 == Nonselect && (Dasite_1 != Tyo || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Tyo;
	}
	else if (KeyClick(KEY_INPUT_3)		//パーの判定
		|| CircleBottunClick(940, 560, 140)) {
		if (Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Pa;
		else if (Dasite_2 == Nonselect && (Dasite_1 != Pa || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Pa;
	};

	//ハードモードかつ異なる出し手の時
	//勝負ポイントの変更（同じ -> 異なる）
	if ((KeyClick(KEY_INPUT_RETURN) || BoxBottun(1150, 364, 1277, 386))
		&& Dasite_2 != Nonselect && Dasite_1 != Nonselect ){

		if (BoutPointCheck_You != 2 && Dasite_1 != Dasite_2) BoutPointCheck_You = 1;		
		return true;
	}
	//選択取り消し
	if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) {
		Dasite_1 = Nonselect;
		Dasite_2 = Nonselect;
		Misete_1 = Nonselect;
		Misete_2 = Nonselect;
	}

	return false;
}

//選んだ手の描画(またはクエスチョンマーク)(右上x座標,右上y座標,画像x幅,画像y幅)
//見せ手
void MiseteDraw_1(int x, int y, int xx, int yy)
{
	/*
	if (Misete_2 == Hatena) {
		DrawExtendGraph(x - 20, y + 20, x + xx + 20, y + yy - 20, GHandle_M, TRUE);
		return;
	}
	*/
	switch (Misete_1) {
	case Hatena:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//ブレンドモードにして透過させて描画
		DrawCircleAA(400, 500, 140, 64, GETCOLOR_BLACK_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了
		
		DrawExtendGraph(x - 20, y - 10, x + xx + 40, y + yy + 10, GHandle_QT, TRUE);
		break;
	case Gu:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_GuHa, TRUE);
		break;
	case Tyo:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_TyoHa, TRUE);
		break;
	case Pa:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_PaHa, TRUE);
		break;
	}
	return;
}
void MiseteDraw_2(int x, int y, int xx, int yy)
{
	/*
	if (Misete_1 == Hatena) {
		DrawExtendGraph(x - 20, y + 20, x + xx + 20, y + yy - 20, GHandle_M, TRUE);
		return;
	}
	*/
	switch (Misete_2) {
	case Hatena:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//ブレンドモードにして透過させて描画
		DrawCircleAA(880, 500, 140, 64, GETCOLOR_BLACK_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了

		DrawExtendGraph(x - 20, y - 10, x + xx + 40, y + yy + 10, GHandle_QT, TRUE);
		break;
	case Gu:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_GuHa, TRUE);
		break;
	case Tyo:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_TyoHa, TRUE);
		break;
	case Pa:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_PaHa, TRUE);
		break;
	}
	return;
}
//出し手
void DasiteDraw(int x,int y, int xx, int yy, Dasite Dasite_x)
{
	switch (Dasite_x) {
	case Hatena:
		DrawExtendGraph(x - 20, y - 10, x + xx + 40, y + yy + 10, GHandle_Q, TRUE);
		break;
	case Gu:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_GuHa, TRUE);
		break;
	case Tyo:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_TyoHa, TRUE);
		break;
	case Pa:
		DrawExtendGraph(x, y, x + xx, y + yy, GHandle_PaHa, TRUE);
		break;
	}
	return;
}

//見せる手を選択 (確認処理の判定 に使用)
bool ShowSelect(void)
{
	//どちらも選んでないときに選んだほうを Hatena にする
	if ((Misete_1 != Hatena && Misete_2 != Hatena)			//どちらも選んでない
		&& (KeyClick(KEY_INPUT_1) == true || CircleBottunClick(400, 500, 150) == true)) {
		Misete_2 = Hatena;
	}
	else if ((Misete_1 != Hatena && Misete_2 != Hatena)		//どちらも選んでない
		&& (KeyClick(KEY_INPUT_2) == true || CircleBottunClick(880, 500, 150) == true)) {
		Misete_1 = Hatena;
	}

	//選択取り消し
	if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) {
		Misete_1 = Dasite_1;
		Misete_2 = Dasite_2;
	}

	//相手と自分の手の確認
	if ((Misete_1 == Hatena || Misete_2 == Hatena)
		&& (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386))) {

		//確認画面の描写
		DrawStringToHandle(350, 300, "お互いの出し手を確認", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();
		WaitTimer(1500);

		int i;		//"お互いの出し手を確認!"の y 座標
		for (i = 300; i > 50; i -= 8) {

			DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
			DrawStringToHandle(350, i, "お互いの出し手を確認", GETCOLOR_WHITE_, FontHandle_2);

			ScreenFlip();
		}

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		DrawStringToHandle(350, i, "お互いの出し手を確認", GETCOLOR_WHITE_, FontHandle_2);
		
		ScreenFlip();

		//自分の出し手
		DrawStringToHandle(100, 500, "Yours", GETCOLOR_WHITE_,FontHandle_3);
		if (Misete_1 == Hatena) DasiteDraw(300, 440, 220, 200, Dasite_2);
		else if (Misete_2 == Hatena) DasiteDraw(300, 440, 220, 200, Dasite_1);
		DrawExtendGraph(550, 450, 810, 630, GHandle_Q, TRUE);

		//相手の出し手
		DrawStringToHandle(960, 220, "Enemy's", GETCOLOR_WHITE_,FontHandle_3);
		DasiteDraw(450, 160, 220, 200, Enemyte_1);
		DrawExtendGraph(700, 170, 960, 350, GHandle_QG, TRUE);

		DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
		DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
		DrawStringToHandle(1170, 362, "Next", GETCOLOR_BLACK_, FontHandle_0);

		ScreenFlip();

		//指定のキーを押すまで待つ
		while (true) {
			MouseUpdate();
			if (ProcessMessage() != 0) {
				break;
			}
			if (CheckHitKey(KEY_INPUT_RETURN) == true) break;
			else if (BoxBottun(1150, 364, 1277, 386) == true) break;
		}

		return true;
	}

	return false;
}

//敵の出し手 (確率を自由に決められるようするには、これ以上に簡素なプログラムが思いつかなかった)
void EnemyCheck(int Diff)
{
	//一つ目はランダムに決める(整数から列挙型にキャスト)
	Enemyte_1 = static_cast<Dasite>(0 + rand() % 3);

	//二つ目は　指定 の確立にする
	while (true) {
		Enemyte_2 = static_cast<Dasite>(0 + rand() % 3);

		if (Enemyte_1 == Enemyte_2 && 0 + rand() % RATIO_SAME(Diff) < 100 && BoutPointCheck_You != 2) break;		//出し手が同じ(1 / 3)、かつ、100 / DASITE_RAND_O(i)の確率で当たる(かつカジュアルでない)
		else if (Enemyte_1 != Enemyte_2 && 0 + rand() % RATIO_DIFF(Diff) < 100) break;		//出し手が異なる(2 / 3)、かつ、100 / DASITE_RAND_K(i)の確率で当たる
	}

	if (BoutPointCheck_Enemy != 2 && Enemyte_1 != Enemyte_2) BoutPointCheck_Enemy = 1;		//ハードかつ異なる手
}

//勝負する手の選択 (選択した方の Misete_ を hatena にする)
void BoutCheckYou(void)
{
	/*
	ここで、Dasite_ ではなく Misete_ を代入するのは、同じ手を選んでいた場合に初めに選んだ手なのか
	後に選んだ手なのか区別できないから。
	どちらを選んでも同じ手だが、演出上は区別する必要がある。
	*/
	if (Syoubute_You == Nonselect) {
		if (KeyClick(KEY_INPUT_1) == true || CircleBottunClick(400, 500, 150)) Syoubute_You = Misete_1;
		else if (KeyClick(KEY_INPUT_2) == true || CircleBottunClick(880, 500, 150)) Syoubute_You = Misete_2;
	}
	else if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) Syoubute_You = Nonselect;

	return;
}
/*
敵側の勝負手を決める
引数1 : 見せての勝ち・負け・あいこを0.1.2で判断
引数2 : 人間側が同じ手を出す確率が高ければ　0、異なる出を出す確率が高ければ　1
		判断材料は、人間側のポイントで5点先取の時
			0か1点のときは同じ手を出して多くのポイントをとる可能性が高いので0
			2点の時も3点とるために同じ手を出す可能性が高いので0
			3点の時は2点とればよいので、勝つ確率の高い異なる出し手を出す可能性が高いので1
		のような感じ
*/
void BoutCheckEnemy(int VoD, int OoK, int ratio1, int ratio2)
{
	int n;
	if (VoD == 1 || (VoD == 0 && OoK== 1)) {
		n = ratio1;
		ratio1 = ratio2;
		ratio2 = n;
	}
	while (1) {
		if (1 + rand() % 10 <= ratio1) {
			Syoubute_Enemy = Enemyte_1;
			break;
		}
		else if (1 + rand() % 10 <= ratio2) {
			Syoubute_Enemy = Enemyte_2;
			break;
		}
	}

	return;
}

//勝負結果の描画 (勝負処理の判定 に使用)
bool BoutResult(void)
{
	if (Syoubute_You != Nonselect					//勝負する手が選ばれている
		&& (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386))) {

		//描画
		DrawStringToHandle(530, 300, "BOUT！！", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();
		WaitTimer(1500);

		int i;	 //"BOUT!!"の y 座標
		for (i = 300; i > 100; i -= 8) {

			DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
			DrawStringToHandle(530, i, "BOUT！！", GETCOLOR_WHITE_, FontHandle_2);

			ScreenFlip();
		}

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		DrawStringToHandle(530, i, "BOUT！！", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();

		DrawCircleAA(320, 460, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(320, 460, 140, 64, GETCOLOR_BLACK_);
		DrawCircleAA(960, 460, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(960, 460, 140, 64, GETCOLOR_BLACK_);

		DrawStringToHandle(270, 425, "You", GETCOLOR_WHITE_, FontHandle_3);
		DrawStringToHandle(880, 425, "Enemy", GETCOLOR_WHITE_, FontHandle_3);

		ScreenFlip();
		WaitTimer(1000);

		DrawStringToHandle(550, 425, "ジャン", GETCOLOR_WHITE_, FontHandle_2);
		ScreenFlip();
		WaitTimer(700);

		DrawBox(540, 410, 760, 500, GETCOLOR_BLACK_, true);
		DrawStringToHandle(580, 425, "ケン", GETCOLOR_WHITE_, FontHandle_2);
		ScreenFlip();
		WaitTimer(900);

		DrawBox(540, 410, 760, 500, GETCOLOR_BLACK_, true);
		DrawStringToHandle(580, 425, "ポン", GETCOLOR_WHITE_, FontHandle_2);

		//自分の出し手
		DrawCircleAA(320, 460, 140, 64, GETCOLOR_BLACK_);
		if (Syoubute_You == Misete_1) DasiteDraw(200, 350, 240, 220, Dasite_1);
		else if (Syoubute_You == Misete_2) DasiteDraw(200, 350, 240, 220, Dasite_2);
		//相手の出し手
		DrawCircleAA(960, 460, 140, 64, GETCOLOR_BLACK_);
		DasiteDraw(840, 350, 240, 220, Syoubute_Enemy);

		ScreenFlip();
		WaitTimer(1000);

		//徐々に黒画面に代わる (引数はWaitTimerに入る)
		Blend_Black(5);

		return true;
	}

	return false;
}

//ポイント処理 (勝負処理で実行)
bool AddPoint(int* point, int Bp, Dasite a, Dasite b)
{
	//ポイントの加算
	int VoD;
	VoD = Victory_or_Defeat[a][b];
	*point += BoutPoint[Bp][VoD];

	//ゼロ未満にさせない
	if (*point < 0) *point = 0;

	return false;
}

//切り替え
//どちらかが先取点以上でリザルトへ
bool ScoreCheck(void)
{
	switch (NowMode) {
	case Hard_10:
		if (Point_You >= 10
			|| Point_Enemy >= 10) {
			return true;
		}
		break;
	case Hard_5:
		if (Point_You >= 5
			|| Point_Enemy >= 5) {
			return true;
		}
		break;
	case Casual_5:
		if (Point_You >= 5
			|| Point_Enemy >= 5) {
			return true;
		}
		break;
	case Casual_3:
		if (Point_You >= 3
			|| Point_Enemy >= 3) {
			return true;
		}
		break;
	case Casual_1:
		if (Point_You >= 1
			|| Point_Enemy >= 1) {
			return true;
		}
	}
	return false;
}
