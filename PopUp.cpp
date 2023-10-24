//�|�b�v�A�b�v��t�H���g�X�^�C�����A�ׂ��ȏ����̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
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

char StringBuffer[2048];	        //�e�L�X�g�f�[�^�p�̃o�b�t�@

//�֐���`
//�t�H���g�f�[�^
int FontHandle_0;
int FontHandle_1;
int FontHandle_2;
int FontHandle_3;
int FontHandle_4;
int FontHandle_5;
int FontHandle_6;
int FontHandle_7;
int FontHandle_8;
//�摜�f�[�^
int GHandle_Title;					//�摜�f�[�^(�^�C�g��)
int GHandle_GuHa;					//�摜�f�[�^(�O�[:�n�[�h)
int GHandle_TyoHa;					//�摜�f�[�^(�`���L:�n�[�h)
int GHandle_PaHa;					//�摜�f�[�^(�p�[:�n�[�h)
int GHandle_GuKa;					//�摜�f�[�^(�O�[:�J�W���A��)
int GHandle_TyoKa;					//�摜�f�[�^(�`���L:�J�W���A��)
int GHandle_PaKa;					//�摜�f�[�^(�p�[:�J�W���A��)
int GHandle_Q;						//�摜�f�[�^(�N�G�X�`�����}�[�N)
int GHandle_QG;						//�摜�f�[�^(�O���[�N�G�X�`�����}�[�N)
int GHandle_QT;						//�摜�f�[�^(�����N�G�X�`�����}�[�N)
int GHandle_M;						//�摜�f�[�^(�ڋ�)
int GHandle_MG;						//�摜�f�[�^(�O���[�ڋ�)
int GHandle_HN;						//�摜�f�[�^(��@����)
int GHandle_HB;						//�摜�f�[�^(��@������)
int GHandle_HF;						//�摜�f�[�^(��@�~���)
//�t�@�C���f�[�^
int FileHandle_Rule;

void Data_Teigi(void)
{
	//�t�H���g�f�[�^��`
	FontHandle_0 = CreateFontToHandle("Constantia", 27, 3);
	FontHandle_1 = CreateFontToHandle("BIZ UD���� Medium", 40, 3);
	FontHandle_2 = CreateFontToHandle("BIZ UDP�S�V�b�N �W��", 60, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_3 = CreateFontToHandle("Constantia", 60, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_4 = CreateFontToHandle("Impact", 100, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_5 = CreateFontToHandle("Impact", 200, 3, DX_FONTTYPE_ANTIALIASING);
	FontHandle_6 = CreateFontToHandle("Constantia", 150, 50, DX_FONTTYPE_ANTIALIASING);
	FontHandle_7 = CreateFontToHandle("������ Demibold", 250, 50, DX_FONTTYPE_ANTIALIASING);
	FontHandle_8 = CreateFontToHandle("Californian FB", 100, 50, DX_FONTTYPE_ANTIALIASING);
	//�摜�f�[�^��`
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

//���[�h�\��
void ModeView(void)
{
	int PointWidth;
	PointWidth = GetDrawFormatStringWidth("%s", ModeName[NowMode]);		//���[�h��px��
	//�J�W���A��
	if (NowGameScene != TitleScene						//�^�C�g���V�[���łȂ�
		&& NowGameScene != RuleScene){				//���[���V�[���ł��Ȃ�
		if (NowMode == Casual_1 || NowMode == Casual_3 || NowMode == Casual_5) { //���[�h����i�J�W���A���j
			DrawBox(585, 0, 695, 30, GETCOLOR_GREEN_, true);
			DrawTriangle(555, 0, 585, 0, 585, 30, GETCOLOR_GREEN_, true);
			DrawTriangle(695, 0, 725, 0, 695, 30, GETCOLOR_GREEN_, true);
			DrawBox(587, 0, 693, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(558, 0, 587, 0, 587, 28, GETCOLOR_BLACK_, true);
			DrawTriangle(693, 0, 722, 0, 693, 28, GETCOLOR_BLACK_, true);
			//���[�h�����S�ɗ���悤�ɒ���
			DrawFormatString(((1280 - PointWidth) / 2) + 5, 7, GETCOLOR_WHITE_, "%s", ModeName[NowMode]);
		}
		else if (NowMode == Hard_5 || NowMode == Hard_10) {			//���[�h����i�n�[�h�j
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

//�|�b�v�A�b�v�\��
void PopUpView(void)
{
	static int EscCount;				//Esc�������ꂽ��

	if (NowGameScene != TitleScene){						//�^�C�g���V�[���łȂ�

		EscCount =  NowGameScene != OldGameScene ? 0 : EscCount;	    //�Q�[���V�[�����ς������|�b�v�����

		if (EscCount % 2 == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
			DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			FileHandle_Rule = FileRead_open("assembly\\Rule.txt");		//FileRead_eof�ŏI�[�𒲂ׂ邽�߂ɖ��x �ǂݍ���
			TxtDraw(FileHandle_Rule);
		}

		if (KeyClick(KEY_INPUT_ESCAPE) == true || BoxBottun(9,7,56,32) == true) EscCount += 1;		//Esc������邽�т� 1 ���Z

		DrawBox(9, 7, 56, 32, GETCOLOR_WHITE_, true);
		DrawBox(11, 9, 54, 30, GETCOLOR_BLACK_, true);
		DrawString(15, 12, "Rule", GETCOLOR_WHITE_);
	}
}

//�t�@�C���f�[�^�`��
void TxtDraw(int FileHandle)
{
	int yy = 60;							//�e�L�X�g�̏��� y ���W

	// �t�@�C���̏I�[������܂ŕ\������
	while (FileRead_eof(FileHandle) == 0) {

		// ��s�ǂݍ���
		FileRead_gets(StringBuffer, sizeof(StringBuffer), FileHandle);

		// ��ʂɕ`��
		DrawString(400, yy, StringBuffer, GETCOLOR_WHITE_);

		// �\���x���W�����ɂ��炷
		yy += 16;
	}
}

//�؂�ւ��`��
void RuletoSelection(unsigned int getcolor_)
{
	DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);
	int PointWidth;
	PointWidth = GetDrawFormatStringWidth("%s", ModeName[NowMode]);			//���[�h��px��
	//fonthandle�Ŋg�債�Ă���̂�3���|���Ē���
	DrawFormatStringToHandle((1280 - PointWidth * 5) / 2, 280, getcolor_, FontHandle_8, "%s", ModeName[NowMode]);

	ScreenFlip();
	WaitTimer(2000);
}

//���X�ɍ���ʂɑ���
void Blend_Black(int spead)
{
	int kosa;	//��ʂ̔Z��
	for (kosa = 0; kosa < 120; kosa++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, kosa);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
		DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);

		ScreenFlip();
		WaitTimer(spead);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��
	DrawBox(0, 0, 1280, 720, GETCOLOR_BLACK_, true);
}