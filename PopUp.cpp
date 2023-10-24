//ポップアップやフォントスタイル等、細かな処理のソースファイル

//ヘッダファイル読み込み
#include "game_scene.h"
#include "game_sistem.h"
#include "key.h"
#include "mouse.h"
#include "PopUp.h"


char ModeName[MODECOUNT][MODENAMEMAX]
{
	"Casual 1",
	"Casual 3",
	"Casual 5",
	"Hard   5",
	"Hard  10"
};

char StringBuffer[2048];	        //テキストデータ用のバッファ

//関数定義
//フォントデータ
int FontHandle_0;
int FontHandle_1;
int FontHandle_2;
int FontHandle_3;
int FontHandle_4;
int FontHandle_5;
int FontHandle_6;
int FontHandle_7;
int FontHandle_8;
//画像データ
int GHandle_Title;					//画像データ(タイトル)
int GHandle_GuHa;					//画像データ(グー:ハード)
int GHandle_TyoHa;					//画像データ(チョキ:ハード)
int GHandle_PaHa;					//画像データ(パー:ハード)
int GHandle_GuKa;					//画像データ(グー:カジュアル)
int GHandle_TyoKa;					//画像データ(チョキ:カジュアル)
int GHandle_PaKa;					//画像データ(パー:カジュアル)
int GHandle_Q;						//画像データ(クエスチョンマーク)
int GHandle_QG;						//画像データ(グレークエスチョンマーク)
int GHandle_QT;						//画像データ(透明クエスチョンマーク)
int GHandle_M;						//画像データ(目玉)
int GHandle_MG;						//画像データ(グレー目玉)
int GHandle_HN;						//画像データ(手　次へ)
int GHandle_HB;						//画像データ(手　取り消し)
int GHandle_HF;						//画像データ(手　降りる)
//ファイルデータ
int FileHandle_Rule;

void Data_Teigi(void)
{
	//フォントデータ定義
	FontHandle_0 = CreateFontToHandle("Constantia", 27, 3);
	FontHandle_1 = CreateFontToHandle("BIZ UD明朝 Medium", 40, 3);
	FontHandle_2 = CreateFontToHandle("BIZ UDPゴシック 標準", 60, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_3 = CreateFontToHandle("Constantia", 60, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_4 = CreateFontToHandle("Impact", 100, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_5 = CreateFontToHandle("Impact", 200, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_6 = CreateFontToHandle("Constantia", 150, 50, DX_FONTTYPE_ANTIALIASING);
	FontHandle_7 = CreateFontToHandle("游明朝 Demibold", 250, 50, DX_FONTTYPE_ANTIALIASING);
	FontHandle_8 = CreateFontToHandle("Californian FB", 100, 50, DX_FONTTYPE_ANTIALIASING);
	//画像データ定義
	GHandle_Title = LoadGraph("picture_sample\\Title_simple.png");
	GHandle_GuHa = LoadGraph("picture_sample\\freejanken_gu_t.png");
	GHandle_TyoHa = LoadGraph("picture_sample\\freejanken_tyo_t.png");
	GHandle_PaHa = LoadGraph("picture_sample\\freejanken_pa_t.png");
	GHandle_GuKa = LoadGraph("picture_sample\\sazaejanken_gu_t.png");
	GHandle_TyoKa = LoadGraph("picture_sample\\sazaejanken_tyo_t.png");
	GHandle_PaKa = LoadGraph("picture_sample\\sazaejanken_pa_t.png");
	GHandle_Q = LoadGraph("picture_sample\\hatena.png");
	GHandle_QG = LoadGraph("picture_sample\\hatena_g.png");
	GHandle_QT = LoadGraph("picture_sample\\hatena_t.png");
	GHandle_M = LoadGraph("picture_sample\\medama_t.png");
	GHandle_MG = LoadGraph("picture_sample\\medama_g.png");
	GHandle_HN = LoadGraph("picture_sample\\hand_next.png");
	GHandle_HB = LoadGraph("picture_sample\\hand_back.png");
	GHandle_HF = LoadGraph("picture_sample\\hand_fold.png");
}

//モード表示
void ModeView(void)
{
	int PointWidth;
	PointWidth = GetDrawFormatStringWidth("%s", ModeName[NowMode]);		//モードのpx数
	//カジュアル
	if (NowGameScene != TitleScene						//タイトルシーンでなく
		&& NowGameScene != RuleScene){				//ルールシーンでもなく
		if (NowMode == Casual_1 || NowMode == Casual_3 || NowMode == Casual_5) { //モード判定（カジュアル）
			DrawBox(585, 0, 695, 30, GETCOLOR_GREEN_, true);
			DrawTriangle(555, 0, 585, 0, 585, 30, GETCOLOR_GREEN_, true);
			DrawTriangle(695, 0, 725, 0, 695, 30, GETCOLOR_GREEN_, true);
			DrawBox(587, 0, 693, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(558, 0, 587, 0, 587, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(693, 0, 722, 0, 693, 28, GETCOLOR_BLACK_, true);
			//モードが中心に来るように調整
			DrawFormatString(((1280 - PointWidth) / 2) + 5, 7, GETCOLOR_WHITE_, "%s", ModeName[NowMode]);
		}
		else if (NowMode == Hard_5 || NowMode == Hard_10) {			//モード判定（ハード）
			DrawBox(590, 0, 690, 30, GETCOLOR_DARKRED_, true);
			DrawTriangle(560, 0, 590, 0, 590, 30, GETCOLOR_DARKRED_, true);
			DrawTriangle(690, 0, 720, 0, 690, 30, GETCOLOR_DARKRED_, true);
			DrawBox(592, 0, 688, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(563, 0, 592, 0, 592, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(688, 0, 717, 0, 688, 28, GETCOLOR_BLACK_, true);

			DrawFormatString(((1280 - PointWidth) / 2) + 5, 7, GETCOLOR_WHITE_, "%s", ModeName[NowMode]);
		}
	}
	/*
			DrawBox(590, 0, 690, 30, GETCOLOR_DARKRED_, true);
		DrawTriangle(560, 0, 590, 0, 590, 30, GETCOLOR_DARKRED_, true);
		DrawTriangle(690, 0, 720, 0, 690, 30, GETCOLOR_DARKRED_, true);
		DrawBox(592, 0, 688, 28, GETCOLOR_BLACK_, true);
		DrawTriangle(563, 0, 592, 0, 592, 28, GETCOLOR_BLACK_, true);
		DrawTriangle(688, 0, 717, 0, 688, 28, GETCOLOR_BLACK_, true);
		DrawFormatString(615, 7, GETCOLOR_WHITE_, "%s", ModeName[NowMode]);
		*/
}
/*
	DrawBox(500, 510, 780, 540, GETCOLOR_WHITE_, true); 
	DrawStringToHandle(570, 510, "Go to Janken", GETCOLOR_BLACK_, FontHandle_0);
*/

//ポップアップ表示
void PopUpView(void)
{
	static int EscCount;				//Escが押された回数

	if (NowGameScene != TitleScene){						//タイトルシーンでなく

		EscCount =  NowGameScene != OldGameScene ? 0 : EscCount;	    //ゲームシーンが変わったらポップを閉じる

		if (EscCount % 2 == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);			//ブレンドモードにして透過させて描画
			DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			FileHandle_Rule = FileRead_open("assembly\\Rule.txt");		//FileRead_eofで終端を調べるために毎度 読み込む
			TxtDraw(FileHandle_Rule);
		}

		if (KeyClick(KEY_INPUT_ESCAPE) == true || BoxBottun(9,7,56,32) == true) EscCount += 1;		//Esc押されるたびに 1 加算

		DrawBox(9, 7, 56, 32, GETCOLOR_WHITE_, true);
		DrawBox(11, 9, 54, 30, GETCOLOR_BLACK_, true);
		DrawString(15, 12, "Rule", GETCOLOR_WHITE_);
	}
}

//ファイルデータ描画
void TxtDraw(int FileHandle)
{
	int yy = 60;							//テキストの初期 y 座標

	// ファイルの終端が来るまで表示する
	while (FileRead_eof(FileHandle) == 0) {

		// 一行読み込み
		FileRead_gets(StringBuffer, sizeof(StringBuffer), FileHandle);

		// 画面に描画
		DrawString(400, yy, StringBuffer, GETCOLOR_WHITE_);

		// 表示Ｙ座標を下にずらす
		yy += 16;
	}
}

//切り替わり描画
void RuletoSelection(unsigned int getcolor_)
{
	DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);
	int PointWidth;
	PointWidth = GetDrawFormatStringWidth("%s", ModeName[NowMode]);			//モードのpx数
	//fonthandleで拡大しているので3を掛けて調整
	DrawFormatStringToHandle((1280 - PointWidth * 5) / 2, 280, getcolor_, FontHandle_8, "%s", ModeName[NowMode]);

	ScreenFlip();
	WaitTimer(2000);
}

//徐々に黒画面に代わる
void Blend_Black(int spead)
{
	int kosa;	//画面の濃さ
	for (kosa = 0; kosa < 120; kosa++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, kosa);			//ブレンドモードにして透過させて描画
		DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);

		ScreenFlip();
		WaitTimer(spead);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了
	DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);
}