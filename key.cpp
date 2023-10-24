//キーボード処理のソースファイル

//ヘッダフィル読み込み
#include "key.h"

//グローバル変数

//現在のキーを押しているフレーム数
int NowKeyPressFrame[KEYKINDMAX];

//1つ前のキーを押しているフレーム数
int OldKeyPressFrame[KEYKINDMAX];

//関数


//キーボード処理の初期化
void KeyInit(void)
{
	//配列の初期化
	for (int i = 0; i < KEYKINDMAX; i++) {
		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;
	}

	return;
}

//キーボード処理の更新
void KeyUpdate(void)
{
	//一時的に保持するキー情報
	char KeyState[KEYKINDMAX];

	//全てのキー情報を一度に取得
	GetHitKeyStateAll(KeyState);

	//キー情報を更新
	for (int i = 0; i < KEYKINDMAX; i++) {
		//1つ前のキー入力を保存
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//現在、キーが押されているとき
		if (KeyState[i] != 0) {
			//押されているフレーム数をカウントアップ
			NowKeyPressFrame[i]++;
		}
		else if (KeyState[i] == 0) {
			//押されていないなら、フレーム数をゼロクリア
			NowKeyPressFrame[i] = 0;
		}

	}

	return;
}

//特定のキーを押したか
//引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
bool KeyDown(int KEY_INPUT_)
{
	//現在押されているキーのフレーム数が0よりも上なら
	if (NowKeyPressFrame[KEY_INPUT_] > 0) {
		return true;		//押した
	}

	return FALSE;			//押してない
}


//特定のキーを押したか
//引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
//説明：「キーを押す→キーを上げる」がセットで行われた時が、クリック
bool KeyClick(int KEY_INPUT_)
{
	//現在キーは押されている
	//ひとつ前のキーは押されていない
	if (NowKeyPressFrame[KEY_INPUT_] == 1			//今押して、
		&& OldKeyPressFrame[KEY_INPUT_] == 0) {		//その寸前は押してない
		return true;		//押した
	}

	return FALSE;			//押してない
}

//特定のキーを押したフレーム数
//引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
//戻り値はフレーム数
int KeyPressFrame(int KEY_INPUT_)
{
	return NowKeyPressFrame[KEY_INPUT_];
}

//特定のキーを押すまでその画面で待つ
void WaitInputKey(int KEY_INPUT_)
{
	while (true) {
		if (ProcessMessage() != 0) {
			break;
		}
		if (CheckHitKey(KEY_INPUT_) == true) break;
	}
}