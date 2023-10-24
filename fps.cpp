//fps処理のソースファイル

//ヘッダファイル
#include "fps.h"

//グローバル変数
FPS fps;

//初期化
void FPSInit(void)
{
	//windowsが起動してからの時間（マイクロ秒）
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//	ほかの値も初期化
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.Deltatime = 0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return;
}

//計測
void FPSCheck(void)
{
	//現在の時刻を取得
	fps.NowTakeTime = GetNowHiPerformanceCount();

	//デルタタイムを計測
	fps.Deltatime = (fps.NowTakeTime - fps.OldTakeTime) / MICROSECOND;

	//現在の時刻を保存
	fps.OldTakeTime = fps.NowTakeTime;

	//現在がMAXフレーム目なら
	if (fps.FrameCount == GAMEFPS) {
		//１フレーム目～MAXフレーム目までの合計時間を継続
		float TotalFrameTime = fps.NowTakeTime - fps.FirstTakeTime;

		//合計時間を理想のfps値で割って平均を計測
		float CalcAverage = TotalFrameTime / GAMEFPS;

		//1秒あたりのフレーム数に変換
		fps.Average = MICROSECOND / CalcAverage;

		//1フレーム目の時刻を取得
		fps.FirstTakeTime = GetNowHiPerformanceCount();

		//フレーム数を1に戻す
		fps.FrameCount = 1;
	}
	else {
		//フレーム数をカウントアップ
		fps.FrameCount++;
	}

	return;
}

//描画
void FPSDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "fps:%3.1f", fps.Average);
	
	return;
}

//待機
void FPSWait(void)
{
	//早すぎた時に待機するミリ秒
	int wait = 0;

	//待ち時間を計測
	wait =
		MICROSECOND / GAMEFPS * fps.FrameCount		//理想の時間
		- (fps.NowTakeTime - fps.FirstTakeTime);	//実際の時間

	//マイクロ秒をミリ秒に変換
	wait /= MILISECOND;

	//待ち時間があるならば
	if (wait > 0 && wait <= WAITTIMEMILL) {
		//「メッセージ」を処理しながら待つ
		WaitTimer(wait);
	}

	return;
}