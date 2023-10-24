//�Q�[���V�X�e���̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include <stdlib.h>

#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"

//�ϐ�
Mode NowMode = NonMode;

Dasite Dasite_1 = Nonselect;		//�@���߂̏o����	�@( Nonselect�ŏ����� )
Dasite Dasite_2 = Nonselect;		//�@���̏o���� �@	�@( Nonselect�ŏ����� )
Dasite Misete_1 = Nonselect;		//�@���߂̌�����	�@( Nonselect�ŏ����� )
Dasite Misete_2 = Nonselect;		//�@���̌����� �@	�@( Nonselect�ŏ����� )
Dasite Syoubute_You = Nonselect;	//�@�����̏��������@( Nonselect�ŏ����� )
Dasite Enemyte_1 = Nonselect;		//�@���߂̌����� �@   ( Nonselect�ŏ����� )
Dasite Enemyte_2 = Nonselect;		//�@���̌����� �@     ( Nonselect�ŏ����� )
Dasite Syoubute_Enemy = Nonselect;	//�@�G�̏�������� �@ ( Nonselect�ŏ����� )

int Point_You = 0;  	//�����̃|�C���g
int Point_Enemy = 0;	//�G�̃|�C���g

int BoutPointCheck_You = 999;							//�����|�C���g���f�̕ϐ�(�J�W���A�����n�[�h���̔��f�ɂ��g����)
int BoutPointCheck_Enemy = 999;							//�����|�C���g���f�̕ϐ�(�J�W���A�����n�[�h���̔��f�ɂ��g����)

//���������̔��f�\
int Victory_or_Defeat[TEKAZU][TEKAZU]{
	//�O�[�A�`���L�A�p�[
	   2,     0,     1,    4,   //�O�[
	   1,     2,     0,    4,	  //�`���L
	   0,     1,     2,    4,	  //�p�[
	   3,     3,     3,    0
};
//���[�h�ɂ��|�C���g�\
int BoutPoint[TEKAZU1][TEKAZU2]{
	//�����A�����A������
	   3,    -1,    0,    1,   -1,	  //�����o����
	   2,    -1,    0,    1,   -1,	  //�قȂ�o����
	   1,     0,    0,    1,   -1,	  //�J�W���A�����[�h
};

//�֐�
//���[�h�I�� (���[�������̔��� �Ɏg�p)
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

//�o����̑I�� (�I�������̔��� �Ɏg�p)
bool DasiteCheck(void)
{
	if (KeyClick(KEY_INPUT_1)		//�O�[�̔���
		|| CircleBottunClick(340,560,140)) {		
		if(Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Gu;
		else if(Dasite_2 == Nonselect && (Dasite_1 != Gu || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Gu;
	}
	else if (KeyClick(KEY_INPUT_2)		//�`���L�̔���
		|| CircleBottunClick(640, 560, 140)) {
		if (Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Tyo;
		else if (Dasite_2 == Nonselect && (Dasite_1 != Tyo || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Tyo;
	}
	else if (KeyClick(KEY_INPUT_3)		//�p�[�̔���
		|| CircleBottunClick(940, 560, 140)) {
		if (Dasite_1 == Nonselect) Dasite_1 = Misete_1 = Pa;
		else if (Dasite_2 == Nonselect && (Dasite_1 != Pa || BoutPointCheck_You != 2)) Dasite_2 = Misete_2 = Pa;
	};

	//�n�[�h���[�h���قȂ�o����̎�
	//�����|�C���g�̕ύX�i���� -> �قȂ�j
	if ((KeyClick(KEY_INPUT_RETURN) || BoxBottun(1150, 364, 1277, 386))
		&& Dasite_2 != Nonselect && Dasite_1 != Nonselect ){

		if (BoutPointCheck_You != 2 && Dasite_1 != Dasite_2) BoutPointCheck_You = 1;		
		return true;
	}
	//�I��������
	if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) {
		Dasite_1 = Nonselect;
		Dasite_2 = Nonselect;
		Misete_1 = Nonselect;
		Misete_2 = Nonselect;
	}

	return false;
}

//�I�񂾎�̕`��(�܂��̓N�G�X�`�����}�[�N)(�E��x���W,�E��y���W,�摜x��,�摜y��)
//������
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
		DrawCircleAA(400, 500, 140, 64, GETCOLOR_BLACK_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��
		
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
		DrawCircleAA(880, 500, 140, 64, GETCOLOR_BLACK_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��

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
//�o����
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

//��������I�� (�m�F�����̔��� �Ɏg�p)
bool ShowSelect(void)
{
	//�ǂ�����I��łȂ��Ƃ��ɑI�񂾂ق��� Hatena �ɂ���
	if ((Misete_1 != Hatena && Misete_2 != Hatena)			//�ǂ�����I��łȂ�
		&& (KeyClick(KEY_INPUT_1) == true || CircleBottunClick(400, 500, 150) == true)) {
		Misete_2 = Hatena;
	}
	else if ((Misete_1 != Hatena && Misete_2 != Hatena)		//�ǂ�����I��łȂ�
		&& (KeyClick(KEY_INPUT_2) == true || CircleBottunClick(880, 500, 150) == true)) {
		Misete_1 = Hatena;
	}

	//�I��������
	if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) {
		Misete_1 = Dasite_1;
		Misete_2 = Dasite_2;
	}

	//����Ǝ����̎�̊m�F
	if ((Misete_1 == Hatena || Misete_2 == Hatena)
		&& (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386))) {

		//�m�F��ʂ̕`��
		DrawStringToHandle(350, 300, "���݂��̏o������m�F", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();
		WaitTimer(1500);

		int i;		//"���݂��̏o������m�F!"�� y ���W
		for (i = 300; i > 50; i -= 8) {

			DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
			DrawStringToHandle(350, i, "���݂��̏o������m�F", GETCOLOR_WHITE_, FontHandle_2);

			ScreenFlip();
		}

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		DrawStringToHandle(350, i, "���݂��̏o������m�F", GETCOLOR_WHITE_, FontHandle_2);
		
		ScreenFlip();

		//�����̏o����
		DrawStringToHandle(100, 500, "Yours", GETCOLOR_WHITE_,FontHandle_3);
		if (Misete_1 == Hatena) DasiteDraw(300, 440, 220, 200, Dasite_2);
		else if (Misete_2 == Hatena) DasiteDraw(300, 440, 220, 200, Dasite_1);
		DrawExtendGraph(550, 450, 810, 630, GHandle_Q, TRUE);

		//����̏o����
		DrawStringToHandle(960, 220, "Enemy's", GETCOLOR_WHITE_,FontHandle_3);
		DasiteDraw(450, 160, 220, 200, Enemyte_1);
		DrawExtendGraph(700, 170, 960, 350, GHandle_QG, TRUE);

		DrawBox(1150, 364, 1240, 386, GETCOLOR_WHITE_, true);
		DrawExtendGraph(1240, 355, 1280, 395, GHandle_HN, TRUE);
		DrawStringToHandle(1170, 362, "Next", GETCOLOR_BLACK_, FontHandle_0);

		ScreenFlip();

		//�w��̃L�[�������܂ő҂�
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

//�G�̏o���� (�m�������R�Ɍ��߂���悤����ɂ́A����ȏ�Ɋȑf�ȃv���O�������v�����Ȃ�����)
void EnemyCheck(int Diff)
{
	//��ڂ̓����_���Ɍ��߂�(��������񋓌^�ɃL���X�g)
	Enemyte_1 = static_cast<Dasite>(0 + rand() % 3);

	//��ڂ́@�w�� �̊m���ɂ���
	while (true) {
		Enemyte_2 = static_cast<Dasite>(0 + rand() % 3);

		if (Enemyte_1 == Enemyte_2 && 0 + rand() % RATIO_SAME(Diff) < 100 && BoutPointCheck_You != 2) break;		//�o���肪����(1 / 3)�A���A100 / DASITE_RAND_O(i)�̊m���œ�����(���J�W���A���łȂ�)
		else if (Enemyte_1 != Enemyte_2 && 0 + rand() % RATIO_DIFF(Diff) < 100) break;		//�o���肪�قȂ�(2 / 3)�A���A100 / DASITE_RAND_K(i)�̊m���œ�����
	}

	if (BoutPointCheck_Enemy != 2 && Enemyte_1 != Enemyte_2) BoutPointCheck_Enemy = 1;		//�n�[�h���قȂ��
}

//���������̑I�� (�I���������� Misete_ �� hatena �ɂ���)
void BoutCheckYou(void)
{
	/*
	�����ŁADasite_ �ł͂Ȃ� Misete_ ��������̂́A�������I��ł����ꍇ�ɏ��߂ɑI�񂾎�Ȃ̂�
	��ɑI�񂾎�Ȃ̂���ʂł��Ȃ�����B
	�ǂ����I��ł������肾���A���o��͋�ʂ���K�v������B
	*/
	if (Syoubute_You == Nonselect) {
		if (KeyClick(KEY_INPUT_1) == true || CircleBottunClick(400, 500, 150)) Syoubute_You = Misete_1;
		else if (KeyClick(KEY_INPUT_2) == true || CircleBottunClick(880, 500, 150)) Syoubute_You = Misete_2;
	}
	else if (KeyClick(KEY_INPUT_BACK) == true || BoxBottun(1107, 390, 1230, 412)) Syoubute_You = Nonselect;

	return;
}
/*
�G���̏���������߂�
����1 : �����Ă̏����E�����E��������0.1.2�Ŕ��f
����2 : �l�ԑ�����������o���m����������΁@0�A�قȂ�o���o���m����������΁@1
		���f�ޗ��́A�l�ԑ��̃|�C���g��5�_���̎�
			0��1�_�̂Ƃ��͓�������o���đ����̃|�C���g���Ƃ�\���������̂�0
			2�_�̎���3�_�Ƃ邽�߂ɓ�������o���\���������̂�0
			3�_�̎���2�_�Ƃ�΂悢�̂ŁA���m���̍����قȂ�o������o���\���������̂�1
		�̂悤�Ȋ���
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

//�������ʂ̕`�� (���������̔��� �Ɏg�p)
bool BoutResult(void)
{
	if (Syoubute_You != Nonselect					//��������肪�I�΂�Ă���
		&& (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386))) {

		//�`��
		DrawStringToHandle(530, 300, "BOUT�I�I", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();
		WaitTimer(1500);

		int i;	 //"BOUT!!"�� y ���W
		for (i = 300; i > 100; i -= 8) {

			DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
			DrawStringToHandle(530, i, "BOUT�I�I", GETCOLOR_WHITE_, FontHandle_2);

			ScreenFlip();
		}

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		DrawStringToHandle(530, i, "BOUT�I�I", GETCOLOR_WHITE_, FontHandle_2);

		ScreenFlip();

		DrawCircleAA(320, 460, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(320, 460, 140, 64, GETCOLOR_BLACK_);
		DrawCircleAA(960, 460, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(960, 460, 140, 64, GETCOLOR_BLACK_);

		DrawStringToHandle(270, 425, "You", GETCOLOR_WHITE_, FontHandle_3);
		DrawStringToHandle(880, 425, "Enemy", GETCOLOR_WHITE_, FontHandle_3);

		ScreenFlip();
		WaitTimer(1000);

		DrawStringToHandle(550, 425, "�W����", GETCOLOR_WHITE_, FontHandle_2);
		ScreenFlip();
		WaitTimer(700);

		DrawBox(540, 410, 760, 500, GETCOLOR_BLACK_, true);
		DrawStringToHandle(580, 425, "�P��", GETCOLOR_WHITE_, FontHandle_2);
		ScreenFlip();
		WaitTimer(900);

		DrawBox(540, 410, 760, 500, GETCOLOR_BLACK_, true);
		DrawStringToHandle(580, 425, "�|��", GETCOLOR_WHITE_, FontHandle_2);

		//�����̏o����
		DrawCircleAA(320, 460, 140, 64, GETCOLOR_BLACK_);
		if (Syoubute_You == Misete_1) DasiteDraw(200, 350, 240, 220, Dasite_1);
		else if (Syoubute_You == Misete_2) DasiteDraw(200, 350, 240, 220, Dasite_2);
		//����̏o����
		DrawCircleAA(960, 460, 140, 64, GETCOLOR_BLACK_);
		DasiteDraw(840, 350, 240, 220, Syoubute_Enemy);

		ScreenFlip();
		WaitTimer(1000);

		//���X�ɍ���ʂɑ��� (������WaitTimer�ɓ���)
		Blend_Black(5);

		return true;
	}

	return false;
}

//�|�C���g���� (���������Ŏ��s)
bool AddPoint(int* point, int Bp, Dasite a, Dasite b)
{
	//�|�C���g�̉��Z
	int VoD;
	VoD = Victory_or_Defeat[a][b];
	*point += BoutPoint[Bp][VoD];

	//�[�������ɂ����Ȃ�
	if (*point < 0) *point = 0;

	return false;
}

//�؂�ւ�
//�ǂ��炩�����_�ȏ�Ń��U���g��
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
