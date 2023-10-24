//ゲームシステムのソースファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"

//マクロ定義
#define TEKAZU 4		//出し手の種類
#define TEKAZU1 3		//出し手の種類
#define TEKAZU2 5		//出し手の種類
#define RATIO_SAME(x) (100 * x) / (2 * (10 - x))		//引数には出し手が異なる割合(１～９の整数)
#define RATIO_DIFF(x) (200 * (10 - x)) / x				//引数には出し手が異なる割合(１～９の整数)

//モードの種類
typedef enum {
	Casual_1,
	Casual_3,
	Casual_5,
	Hard_5,
	Hard_10,
	NonMode
}Mode;

typedef enum {
	Gu,
	Tyo,
	Pa,
	Hatena,
	Nonselect
}Dasite;

//勝ち,負け,あいこ　の配列
/*
int Victory_or_Defeat[TEKAZU][TEKAZU]{
	//グー、チョキ、パー
	   2,     0,     1,	  //グー
	   1,     2,     0,	  //チョキ
	   0,     1,     2,	  //パー
};
int BoutPoint[TEKAZU][TEKAZU]{
	//勝ち、負け、あいこ
	   2,    -1,    0,	  //同じ出して
	   1,    -2,   -1,	  //異なる出して
	   1,     0,    0,	  //カジュアルモード
};
*/

//グローバル変数
extern Mode NowMode;				    //今のモードと先取点判断
extern int BoutPointCheck_You;			    //勝負ポイント判断の変数(自分)
extern int BoutPointCheck_Enemy;			    //勝負ポイント判断の変数(敵)
extern Dasite Dasite_1;					//初めの出し手
extern Dasite Dasite_2;					//次の出し手 
extern Dasite Misete_1;					//初めの見せ手
extern Dasite Misete_2;					//次の見せ手 
extern Dasite Syoubute_You;				//勝負する手 
extern Dasite Enemyte_1;				//敵の初めの出し手
extern Dasite Enemyte_2;				//　　次の出し手
extern Dasite Syoubute_Enemy;			//勝負する手 
extern int Point_You;					//自分のポイント
extern int Point_Enemy;					//敵のポイント
extern int Victory_or_Defeat[TEKAZU][TEKAZU]; //勝ち負けの判断表
extern int BoutPoint[TEKAZU1][TEKAZU2];         //モードによるポイント表

//外部プロトタイプ宣言
extern bool ModeSelect(void);				//モードと先取点の選択
extern bool DasiteCheck(void);				//出し手の選択
extern void EnemyCheck(int Diff);			//敵の出し手
extern bool ShowSelect(void);				//見せる手を選択
extern void DasiteDraw(int x, int y, int xx, int yy,Dasite Dasite_x);		//出し手の描画
extern void MiseteDraw_1(int x, int y, int xx, int yy);						//見せ手の描画
extern void MiseteDraw_2(int x, int y, int xx, int yy);						//見せ手の描画
extern void BoutCheckYou(void);					//勝負する手の選択
extern void BoutCheckEnemy(void);					//勝負する手の選択
extern bool BoutResult(void);					//勝負結果の描画
extern bool AddPoint(int *point,int Bp, Dasite a,Dasite b);					//スコアの加算
extern bool ScoreCheck(void);					//ポイントが先取点以上か判断
extern void BoutCheckEnemy(int VorD, int OorK, int ratio1, int ratio2);

