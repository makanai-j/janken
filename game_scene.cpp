//ゲーム処理のソースファイル

//ゲームシーン切替関係のヘッダファイル
#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"
//ゲームシーン
GameScene NowGameScene;		//現在のゲームシーン
GameScene OldGameScene;		//直前のゲームシーン

//ゲームシーンの名前
char GameSceneName[GAMESCENECOUNT][GAMESCENENAMEMAX]
{
	"タイトル画面",
	"ルール画面",
	"選択画面",
	"確認画面",
	"勝負画面",
	"スコア画面",
	"リザルト画面"
};

//シーン切替関数
//タイトル初期化
void TitleInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(177, 210, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

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
	//シーン切り替え（マウス左またはキーのどれかが押されたとき）
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(497, 507, 783, 543) == true) {

		//切り替え
		NowGameScene = RuleScene;

		//ルール画面初期化
		RuleInit();

		return;
	}

	return;
}

//タイトル描画
void TitleDraw(void)
{
	static int titlecount = 0;
	static int subcount = 0;
	if (GAMEDEBUG == true && NowGameScene == TitleScene) {
		
		//画像表示
		DrawExtendGraph(0,0, 1280, 720, GHandle_Title, TRUE);

		DrawBox(497, 507, 783, 543, GETCOLOR_WHITE_, true);
		titlecount++;
		titlecount % 30 == 0 ? subcount++ : 0 ;
		if (subcount % 2 == 0) { 
			DrawBox(500, 510, 780, 540, GETCOLOR_WHITE_, true); 
			DrawStringToHandle(570, 510, "Go to Janken", GETCOLOR_BLACK_, FontHandle_0);
		}
		else {
			DrawBox(500, 510, 780, 540, GETCOLOR_BLACK_, true);
			DrawStringToHandle(570, 510, "Go to Janken", GETCOLOR_WHITE_, FontHandle_0);
		}
	}

	return;
}

//ルール初期化
void RuleInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

		//ルールに関する各変数の初期化
		NowMode = NonMode;

	}

	return;
}
//ルール管理
void RuleCtrl(void)
{
	RuleProc();	//処理をしてから
	RuleDraw();	//描画する

	return;
}
//ルール処理
void RuleProc(void)
{
	//シーン切り替え（モード選択されたとき）
	if (ModeSelect() == true) {

		//BoutPointCheck_へモードを代入
		switch (NowMode) {
		case Casual_1:
		case Casual_3:
		case Casual_5:
			BoutPointCheck_You = 2;
			BoutPointCheck_Enemy = 2;

			//画面切り替わり前の確認描画
			RuletoSelection(GETCOLOR_GREEN_);
			break;
		case Hard_5:
		case Hard_10:
			BoutPointCheck_You = 0;
			BoutPointCheck_Enemy = 0;

			//画面切り替わり前の確認描画
			RuletoSelection(GETCOLOR_DARKRED_);
		}

		//Blend_Black(0);

		ClearDrawScreen();
		DrawStringToHandle(455, 300, "出し手を選択", GETCOLOR_WHITE_, FontHandle_2);
		
		ScreenFlip();
		WaitTimer(1500);
		Blend_Black(0);


		//切り替え
		NowGameScene = SelectionScene;

		//選択画面初期化
		SelectionInit();

		return;
	}

	return;
}
//ルール描画
void RuleDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == RuleScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
	
		//描画
		DrawStringToHandle(100, 180, "  Casual", GETCOLOR_WHITE_, FontHandle_3);		// "カジュアル"
		DrawBox(560, 170, 665, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(560, 170, 460, 250, 560, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(665, 170, 665, 250, 765, 250, GETCOLOR_WHITE_, true);
		DrawStringToHandle(600, 180, "1", GETCOLOR_BLACK_, FontHandle_2);

		DrawBox(770, 170, 875, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(670, 170, 770, 170, 770, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(875, 170, 975, 170, 875, 250, GETCOLOR_WHITE_, true);
		DrawStringToHandle(810, 180, "3", GETCOLOR_BLACK_, FontHandle_2);

		DrawBox(980, 170, 1085, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(980, 170, 880, 250, 980, 250, GETCOLOR_WHITE_, true);
		DrawTriangle(1085, 170, 1085, 250, 1185, 250, GETCOLOR_WHITE_, true);
		DrawStringToHandle(1020, 180, "5", GETCOLOR_BLACK_, FontHandle_2);

		DrawStringToHandle(100, 410, "   Hard", GETCOLOR_WHITE_, FontHandle_3);			// "ハード"
		DrawBox(560, 400, 770, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(560, 400, 460, 480, 560, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(770, 400, 770, 480, 870, 480, GETCOLOR_WHITE_, true);
		DrawStringToHandle(650, 410, "5", GETCOLOR_BLACK_, FontHandle_2);

		DrawBox(875, 400, 1085, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(775, 400, 875, 400, 875, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(1085, 400, 1185, 400, 1085, 480, GETCOLOR_WHITE_, true);
		DrawStringToHandle(950, 410, "10", GETCOLOR_BLACK_, FontHandle_2);

		//数字の色変更用
		ModeSelect();
	}

	return;
}

//選択初期化
void SelectionInit(void)
{

	//変数を初期化しなおす
	Dasite_1 = Nonselect;					//初めの出し手
	Dasite_2 = Nonselect;					//次の出し手 
	Misete_1 = Nonselect;					//初めの見せ手
	Misete_2 = Nonselect;					//次の見せ手 
	Syoubute_You = Nonselect;				//勝負する手 
	Enemyte_1 = Nonselect;				//敵の初めの出し手
	Enemyte_2 = Nonselect;				//　　次の出し手
	Syoubute_Enemy = Nonselect;			//勝負する手 

	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");
	}

	return;
}
//選択管理
void SelectionCtrl(void)
{
	SelectionProc();	//処理をしてから
	SelectionDraw();	//描画する

	return;
}
//選択処理
void SelectionProc(void)
{
	//シーン切り替え（出し手が二つ選ばれて K を押されたとき）
	if (DasiteCheck() == true) {

		//コンピュータの手をランダムで決める
		switch (Point_Enemy) {		//人間側のポイントによって判断
		case 0:
		case 1:
			EnemyCheck(6);
			break;
		case 2:
			EnemyCheck(4);
			break;
		case 3:
		case 4:
			EnemyCheck(9);
			break;
		case 5:
		case 6:
			EnemyCheck(5);
			break;
		case 7:
			EnemyCheck(3);
			break;
		case 8:
		case 9:
			EnemyCheck(9);
		}

		//切り替え
		NowGameScene = CheckScene;

		//確認画面初期化
		CheckInit();

		return;
	}

	return;
}
//選択描画
void SelectionDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == SelectionScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//描画
		DrawCircleAA(340, 560, 140, 64, GETCOLOR_WHITE_);
		DrawCircleAA(640, 560, 140, 64, GETCOLOR_WHITE_);
		DrawCircleAA(940, 560, 140, 64, GETCOLOR_WHITE_);
		DrawExtendGraph(220, 450, 460, 670, GHandle_GuHa, TRUE);
		DrawExtendGraph(520, 450, 760, 670, GHandle_TyoHa, TRUE);
		DrawExtendGraph(820, 450, 1060, 670, GHandle_PaHa, TRUE);

		if (BoutPointCheck_You == 2 && Dasite_2 == Nonselect) {
			switch (Dasite_1) {
			case Gu:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//ブレンドモードにして透過させて描画
				DrawCircleAA(340, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了
				break;
			case Tyo:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//ブレンドモードにして透過させて描画
				DrawCircleAA(640, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了
				break;
			case Pa:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//ブレンドモードにして透過させて描画
				DrawCircleAA(940, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンドモード終了
				break;
			}
		}
		
		DrawCircleAA(470, 220, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(470, 220, 140, 64, GETCOLOR_BLACK_);
		DasiteDraw(350, 110, 240, 220, Dasite_1);
		DrawCircleAA(810, 220, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(810, 220, 140, 64, GETCOLOR_BLACK_);
		DasiteDraw(690, 110, 240, 220, Dasite_2);

		if (Dasite_1 != Nonselect && Dasite_2 != Nonselect) {
			DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
			DrawStringToHandle(1170, 362, "Next", GETCOLOR_BLACK_, FontHandle_0);

			DrawBox(1140, 390, 1230, 412, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1105, 383, 1138, 421, GHandle_HB, TRUE);
			DrawStringToHandle(1145, 388, "Cancel", GETCOLOR_BLACK_, FontHandle_0);
		}

	}

	return;
}

//確認初期化
void CheckInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

	}

	return;
}
//確認管理
void CheckCtrl(void)
{
	CheckProc();	//処理をしてから
	CheckDraw();	//描画する

	return;
}
//確認処理
void CheckProc(void)
{
	//シーン切り替え（スペースキーが押されたとき）
	if (ShowSelect() == true) {

		if (BoutPointCheck_You == 2) {						//カジュアルモードの時
			Syoubute_Enemy = 0 + rand() % 2 == 0 ? Enemyte_1 : Enemyte_2;
		}
		else {												//ハードモードの時
			/*
			敵側の勝負手を決める
			引数1 : 敵側の見せての勝ち・負け・あいこを0.1.2で判断
			引数2 : 人間側が同じ手を出す確率が高ければ　0、異なる出を出す確率が高ければ　1
					判断材料は、人間側のポイントで5点先取の時
						0か1点のときは同じ手を出して多くのポイントをとる可能性が高いので0
						2点の時も3点とるために同じ手を出す可能性が高いので0
						3点の時は2点とればよいので、勝つ確率の高い異なる出し手を出す可能性が高いので1
					のような感じ　
			引数3 : 高いほうの確立
			引数3 : 低いほうの確立
			*/
			int VoD = Victory_or_Defeat[Enemyte_1][Misete_1 == Hatena ? Dasite_2 : Dasite_1];
			switch (Point_You) {		//人間側のポイントによって判断
			case 0:
			case 1:
				BoutCheckEnemy(VoD, 0, 8, 2);
				break;
			case 2:
				BoutCheckEnemy(VoD, 0, 8, 2);
				break;
			case 3:
			case 4:
				BoutCheckEnemy(VoD, 1, 8, 2);
				break;
			case 5:
			case 6:
				BoutCheckEnemy(VoD, 1, 5, 5);
				break;
			case 7:
				BoutCheckEnemy(VoD, 0, 8, 2);
				break;
			case 8:
			case 9:
				BoutCheckEnemy(VoD, 1, 8, 2);
			}
		}

		//切り替え
		NowGameScene = BoutScene;

		//勝負画面初期化
		BoutInit();

		return;
	}

	return;
}
//確認描画
void CheckDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == CheckScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//描画
		DrawStringToHandle(340, 150, "相手に見せる手を選択", GETCOLOR_WHITE_, FontHandle_2);

		DrawCircleAA(400, 500, 150, 64, GETCOLOR_WHITE_);

		if (Misete_2 == Hatena) {
			DrawCircleAA(400, 500, 140, 64, GETCOLOR_WHITE_);
		}
		else DrawCircleAA(400, 500, 140, 64, GETCOLOR_BLACK_);

		DasiteDraw(280, 390, 240, 220, Dasite_1);
		MiseteDraw_1(280, 390, 240, 220);

		DrawCircleAA(880, 500, 150, 64, GETCOLOR_WHITE_);

		if (Misete_1 == Hatena) {
			DrawCircleAA(880, 500, 140, 64, GETCOLOR_WHITE_);
		}
		else DrawCircleAA(880, 500, 140, 64, GETCOLOR_BLACK_);

		DasiteDraw(760, 390, 240, 220, Dasite_2);
		MiseteDraw_2(760, 390, 240, 220);

		if (Misete_1 == Hatena || Misete_2 == Hatena) {
			DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
			DrawStringToHandle(1170, 362, "Next", GETCOLOR_BLACK_, FontHandle_0);

			DrawBox(1140, 390, 1230, 412, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1105, 383, 1138, 421, GHandle_HB, TRUE);
			DrawStringToHandle(1145, 388, "Cancel", GETCOLOR_BLACK_, FontHandle_0);
		}
	/*
		DrawFormatString(0, 100, GETCOLOR_WHITE_, "%s", Enemyte_1 != Gu ? (Enemyte_1 == Pa ? "パー" : "チョキ") : "グー" );
		DrawFormatString(0, 120, GETCOLOR_WHITE_, "%s", Enemyte_2 != Gu ? (Enemyte_2 == Pa ? "パー" : "チョキ") : "グー");
	*/
	}

	return;
}

//勝負初期化
void BoutInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

	}

	return;
}
//勝負管理
void BoutCtrl(void)
{
	BoutProc();	//処理をしてから
	BoutDraw();	//描画する

	return;
}
//勝負処理
void BoutProc(void)
{
	//シーン切り替え（勝負結果描画後）
	if (BoutResult() == true) {

		//切替前にポイント加算
		AddPoint(&Point_You, BoutPointCheck_You, Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2, Syoubute_Enemy);
		AddPoint(&Point_Enemy, BoutPointCheck_Enemy, Syoubute_Enemy, Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2);

		//切り替え
		NowGameScene = ScoreScene;

		//スコア画面初期化
		ScoreInit();

		return;
	}

	//勝負を降りた時
	if (BoutPointCheck_You != 2 && (KeyClick(KEY_INPUT_DELETE) == true || BoxBottun(1108, 427, 1235, 449) == true)) {
		
		Syoubute_You = Gu;			  //リザルトのポイント判断用 何でも良い
		Syoubute_Enemy = Hatena;      //リザルトのポイント判断用に 3 にする
		
		AddPoint(&Point_You, BoutPointCheck_You, Syoubute_You, Syoubute_Enemy);
		AddPoint(&Point_Enemy, BoutPointCheck_Enemy, Syoubute_Enemy, Syoubute_You);
		
		NowGameScene = ScoreScene;
	}

	return;
}
//勝負描画
void BoutDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == BoutScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//勝負手の選択
		BoutCheckYou();

		//描画
		DrawCircleAA(400, 500, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(400, 500, 140, 64, GETCOLOR_BLACK_);
		DrawCircleAA(880, 500, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(880, 500, 140, 64, GETCOLOR_BLACK_);

		//選ばれた方の後ろを塗る
		if (Syoubute_You == Misete_1) DrawCircleAA(400, 500, 142, 64, GETCOLOR_WHITE_);
	    else if (Syoubute_You == Misete_2) DrawCircleAA(880, 500, 142, 64, GETCOLOR_WHITE_);
		DasiteDraw(280, 390, 240, 220, Dasite_1);
		DasiteDraw(760, 390, 240, 220, Dasite_2);

		DrawStringToHandle(405, 150, "勝負する手を選択", GETCOLOR_WHITE_, FontHandle_2);

		if (Syoubute_You == Misete_1 || Syoubute_You == Misete_2) {
			DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
			DrawStringToHandle(1170, 362, "Bout!", GETCOLOR_BLACK_, FontHandle_0);

			DrawBox(1140, 390, 1230, 412, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1105, 383, 1138, 421, GHandle_HB, TRUE);
			DrawStringToHandle(1145, 388, "Cancel", GETCOLOR_BLACK_, FontHandle_0);
		}
		if (BoutPointCheck_You != 2) {
			DrawBox(1145, 427, 1235, 449, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1104, 422, 1143, 462, GHandle_HF, TRUE);
			DrawStringToHandle(1160, 425, "Fold", GETCOLOR_BLACK_, FontHandle_0);
		}
	}

	return;
}

//スコア初期化
void ScoreInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");

	}

	return;
}
//スコア管理
void ScoreCtrl(void)
{
	ScoreProc();	//処理をしてから
	ScoreDraw();	//描画する

	return;
}
//スコア処理
void ScoreProc(void)
{

	//シーン切り替え
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386)) {


		//切り替え
		//どちらかが先取点以上でリザルトへ
		if (ScoreCheck() == true) {

			//切り替わり前の画面
			DrawStringToHandle(580, 300, "Final", GETCOLOR_WHITE_, FontHandle_3);
			ScreenFlip();
			WaitTimer(1000);
			Blend_Black(0);

			NowGameScene = ResultScene;
			ResultInit();

			return;
		}
		else {
			//両方先取点以下で再度出し手選択へ移行
			//BoutPointCheck_に0を再代入しないと増え続ける
			if (BoutPointCheck_You != 2) {
				BoutPointCheck_You = 0;
				BoutPointCheck_Enemy = 0;
			}
			NowGameScene = SelectionScene;
			SelectionInit();
			return;
		}
	}
}
//スコア描画
void ScoreDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == ScoreScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//描画
		switch (Victory_or_Defeat[Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2][Syoubute_Enemy]) {
		case 0: //勝ち
			DrawStringToHandle(450, 80, "V i c t o r y", GETCOLOR_ORANGE_, FontHandle_4);
			break;
		case 1: //負け
		case 4: //負け
			DrawStringToHandle(468, 80, "D e f e a t", GETCOLOR_BLUE_, FontHandle_4);
			break;
		case 2: //あいこ
			DrawStringToHandle(515, 80, "D r a w", GETCOLOR_CYAN_, FontHandle_4);
			break;
		}

		int s_sen = 5;	//線の幅
		int s_sen2 = 90;	//線の幅2
		int s_haba = 300;	//横幅
		int s_taka = 300;	//高さ

		int sx_rr = 250;			//右の四角の右上x
		int sy_rr = 350;			//右の四角の右上y
		int sx_rl = sx_rr + s_haba;	//右の四角の幅
		int sy_rl = sy_rr + s_taka;	//右の四角の高さ

		int sx_lr = 1280 - (s_haba + sx_rr);	//左の四角の右上x
		int sy_lr = sy_rr;						//左の四角の右上y
		int sx_ll = sx_lr + s_haba;				//左の四角の幅
		int sy_ll = sy_rr + s_taka;				//左の四角の高さ
		//右の四角
		DrawBox(sx_rr, sy_rr, sx_rl, sy_rl - s_taka - s_sen2, GETCOLOR_WHITE_, true);		//　￣
		DrawBox(sx_rr + s_haba - s_sen, sy_rr, sx_rl, sy_rl, GETCOLOR_WHITE_, true);		//　　｜
		DrawBox(sx_rr, sy_rr, sx_rl - s_haba + s_sen, sy_rl, GETCOLOR_WHITE_, true);		//｜
		DrawBox(sx_rr, sy_rr + s_taka - s_sen, sx_rl, sy_rl, GETCOLOR_WHITE_, true);		//　＿
		DrawStringToHandle(305, sy_rr - 60, "Your point", GETCOLOR_BLACK_, FontHandle_1);
		//左の四角
		DrawBox(sx_lr, sy_lr, sx_ll, sy_ll - s_taka - s_sen2, GETCOLOR_WHITE_, true);	//　￣
		DrawBox(sx_lr + s_haba - s_sen, sy_lr, sx_ll, sy_ll, GETCOLOR_WHITE_, true);	//　　｜
		DrawBox(sx_lr, sy_lr, sx_ll - s_haba + s_sen, sy_ll, GETCOLOR_WHITE_, true);	//｜
		DrawBox(sx_lr, sy_lr + s_taka - s_sen, sx_ll, sy_ll, GETCOLOR_WHITE_, true);	//　＿
		DrawStringToHandle(753, sy_rr - 60, "Enemy's point", GETCOLOR_BLACK_, FontHandle_1);

		//ポイント描写
		int PointWidth;
		int VoD;
		//自分ポイント
		PointWidth = (GetDrawFormatStringWidth("%d",Point_You) / 9) - 1;		//文字数 - 1
		DrawFormatStringToHandle(
			sx_rr + 105 - (45 * PointWidth),	//右上 x 座標 (2桁の時は45px左にずらす)
			sy_rr + 85,							//右上 y 座標			
			GETCOLOR_WHITE_,
			FontHandle_5,
			"%d", Point_You
		); 
		VoD = Victory_or_Defeat[Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2][Syoubute_Enemy];
		DrawFormatStringToHandle(
			sx_rr + 93, sy_rr + 10, GETCOLOR_WHITE_, FontHandle_1, 
			BoutPoint[BoutPointCheck_You][VoD] < 0 ? "[ %d ]" : "[ +%d ]",  // + の時に「+」が付く
			BoutPoint[BoutPointCheck_You][VoD]
		);

		//敵ポイント
		PointWidth = (GetDrawFormatStringWidth("%d",Point_Enemy) / 9) - 1;		//文字数 - 1
		DrawFormatStringToHandle(
			sx_lr + 105 - (45 * PointWidth),	//右上 x 座標 (2桁の時は45px左にずらす)
			sy_lr + 85,							//右上 y 座標			
			GETCOLOR_WHITE_,
			FontHandle_5,
			"%d", Point_Enemy
		);
		VoD = Victory_or_Defeat[Syoubute_Enemy][Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2];
		DrawFormatStringToHandle(
			sx_lr + 93, sy_lr + 10, GETCOLOR_WHITE_, FontHandle_1,
			BoutPoint[BoutPointCheck_Enemy][VoD] < 0 ? "[ %d ]" : "[ +%d ]",  // + の時に「+」が付く
			BoutPoint[BoutPointCheck_Enemy][VoD]
		);

		if (ScoreCheck() == true) {
			DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
			DrawStringToHandle(1160, 362, "Final", GETCOLOR_BLACK_, FontHandle_0);
		}
		else {
			DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
			DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
			DrawStringToHandle(1170, 362, "Next", GETCOLOR_BLACK_, FontHandle_0);
		}
	}

	return;
}

//リザルト初期化
void ResultInit(void)
{
	if (GAMEDEBUG == true) {
		//シーン名表示
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "初期化");
	}
	return;
}
//リザルト管理  
void ResultCtrl(void)
{
	ResultProc();	//処理をしてから
	ResultDraw();	//描画する

	return;
}
//リザルト処理  
void ResultProc(void)
{
	//シーン切り替え（スペースキーが押されたとき）
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386)) {
		
		//ポイントの初期化
		Point_You = 0;					//自分のポイント
		Point_Enemy = 0;					//敵のポイント
		//モードも初期化
		NowMode = NonMode;
		//モードチェックの初期化
		BoutPointCheck_You = 999;			    //勝負ポイント判断の変数(自分)
		BoutPointCheck_Enemy = 999;			    //勝負ポイント判断の変数(敵)

		//切り替え
		NowGameScene = RuleScene;

		//ルール画面初期化
		RuleInit();

		return;
	}

	return;
}
//リザルト描画  
void ResultDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == ResultScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		//描画
		if (Point_You > Point_Enemy) {
			DrawBox(0, 200, 1280, 270, GETCOLOR_ORANGE_, true);
			DrawStringToHandle(50, 100, "Congratulations!", GETCOLOR_YELLOW_, FontHandle_6);
		}
		else {
			DrawBox(0, 200, 1280, 270, GETCOLOR_BLUE_, true);
			DrawStringToHandle(370, 100, "Too bad", GETCOLOR_PURPLE_, FontHandle_6);
		}
		int PointWidth;
		PointWidth = (GetDrawFormatStringWidth("%d", Point_You) / 9) - 1;		//文字数 - 1
		DrawFormatStringToHandle(
			335 - (170 * PointWidth),	//右上 x 座標 (2桁の時は45px左にずらす)
			400,							//右上 y 座標			
			GETCOLOR_WHITE_,
			FontHandle_7,
			"%d", Point_You
		);
		PointWidth = (GetDrawFormatStringWidth("%d", Point_Enemy) / 9) - 1;		//文字数 - 1
		DrawFormatStringToHandle(
			750 - (50 * PointWidth),	//右上 x 座標 (2桁の時は45px左にずらす)
			400,							//右上 y 座標			
			GETCOLOR_WHITE_,
			FontHandle_7,
			"%d", Point_Enemy
		);
		DrawFormatStringToHandle(570, 370, GETCOLOR_WHITE_, FontHandle_7, "-", 1, 1);

		DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
		DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
		DrawStringToHandle(1170, 362, "Home", GETCOLOR_BLACK_, FontHandle_0);

	}

	return;
}