//ポップアップやフォントスタイル等、細かな処理のヘッダファイル
#pragma once

//ヘッダファイル読み込み
#include "DxLib.h"

//マクロ定義
#define MODECOUNT 5						//モードの数
#define MODENAMEMAX 20					//モード名の文字MAX
 
//グローバル変数
extern int FontHandle_0;			//フォントNo0
extern int FontHandle_1;			//フォントNo1
extern int FontHandle_2;			//フォントNo2
extern int FontHandle_3;			//フォントNo3
extern int FontHandle_4;			//フォントNo4
extern int FontHandle_5;			//フォントNo5
extern int FontHandle_6;			//フォントNo6
extern int FontHandle_7;			//フォントNo7
extern int FontHandle_8;			//フォントNo7

extern int GHandle_Title;					//画像データ(タイトル)
extern int GHandle_GuHa;					//画像データ(グー:ハード)
extern int GHandle_TyoHa;					//画像データ(チョキ:ハード)
extern int GHandle_PaHa;					//画像データ(パー:ハード)
extern int GHandle_GuKa;					//画像データ(グー:カジュアル)
extern int GHandle_TyoKa;					//画像データ(チョキ:カジュアル)
extern int GHandle_PaKa;					//画像データ(パー:カジュアル)
extern int GHandle_Q;						//画像データ(クエスチョンマーク)
extern int GHandle_QG;						//画像データ(グレークエスチョンマーク)
extern int GHandle_QT;						//画像データ(透明クエスチョンマーク)
extern int GHandle_M;						//画像データ(目玉)
extern int GHandle_MG;						//画像データ(グレー目玉)
extern int GHandle_HN;						//画像データ(手　次へ)
extern int GHandle_HB;						//画像データ(手　取り消し)
extern int GHandle_HF;						//画像データ(手　降りる)

extern int FileHandle_Rule;					//ファイルデータ

extern char StringBuffer[2048];	        //テキストデータ用のバッファ


//外部プロトタイプ宣言
extern void PopUpView(void);			//左上ポップアップ
extern void ModeView(void);				//中央モード表示

extern void Data_Teigi(void);			//データの定義

extern void RuletoSelection(unsigned int getcolor_);		//切り替わり描画

extern void Blend_Black(int spead);			//徐々に黒に代わる

extern void TxtDraw(int FileHandle);	//テキストデータ描画
