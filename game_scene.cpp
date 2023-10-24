//�Q�[�������̃\�[�X�t�@�C��

//�Q�[���V�[���ؑ֊֌W�̃w�b�_�t�@�C��
#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"
//�Q�[���V�[��
GameScene NowGameScene;		//���݂̃Q�[���V�[��
GameScene OldGameScene;		//���O�̃Q�[���V�[��

//�Q�[���V�[���̖��O
char GameSceneName[GAMESCENECOUNT][GAMESCENENAMEMAX]
{
	"�^�C�g�����",
	"���[�����",
	"�I�����",
	"�m�F���",
	"�������",
	"�X�R�A���",
	"���U���g���"
};

//�V�[���ؑ֊֐�
//�^�C�g��������
void TitleInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(177, 210, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

	}

	return;
}
//�^�C�g���Ǘ�
void TitleCtrl(void)
{
	TitleProc();	//���������Ă���
	TitleDraw();	//�`�悷��

	return;
}
//�^�C�g������
void TitleProc(void)
{
	//�V�[���؂�ւ��i�}�E�X���܂��̓L�[�̂ǂꂩ�������ꂽ�Ƃ��j
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(497, 507, 783, 543) == true) {

		//�؂�ւ�
		NowGameScene = RuleScene;

		//���[����ʏ�����
		RuleInit();

		return;
	}

	return;
}

//�^�C�g���`��
void TitleDraw(void)
{
	static int titlecount = 0;
	static int subcount = 0;
	if (GAMEDEBUG == true && NowGameScene == TitleScene) {
		
		//�摜�\��
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

//���[��������
void RuleInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

		//���[���Ɋւ���e�ϐ��̏�����
		NowMode = NonMode;

	}

	return;
}
//���[���Ǘ�
void RuleCtrl(void)
{
	RuleProc();	//���������Ă���
	RuleDraw();	//�`�悷��

	return;
}
//���[������
void RuleProc(void)
{
	//�V�[���؂�ւ��i���[�h�I�����ꂽ�Ƃ��j
	if (ModeSelect() == true) {

		//BoutPointCheck_�փ��[�h����
		switch (NowMode) {
		case Casual_1:
		case Casual_3:
		case Casual_5:
			BoutPointCheck_You = 2;
			BoutPointCheck_Enemy = 2;

			//��ʐ؂�ւ��O�̊m�F�`��
			RuletoSelection(GETCOLOR_GREEN_);
			break;
		case Hard_5:
		case Hard_10:
			BoutPointCheck_You = 0;
			BoutPointCheck_Enemy = 0;

			//��ʐ؂�ւ��O�̊m�F�`��
			RuletoSelection(GETCOLOR_DARKRED_);
		}

		//Blend_Black(0);

		ClearDrawScreen();
		DrawStringToHandle(455, 300, "�o�����I��", GETCOLOR_WHITE_, FontHandle_2);
		
		ScreenFlip();
		WaitTimer(1500);
		Blend_Black(0);


		//�؂�ւ�
		NowGameScene = SelectionScene;

		//�I����ʏ�����
		SelectionInit();

		return;
	}

	return;
}
//���[���`��
void RuleDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == RuleScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
	
		//�`��
		DrawStringToHandle(100, 180, "  Casual", GETCOLOR_WHITE_, FontHandle_3);		// "�J�W���A��"
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

		DrawStringToHandle(100, 410, "   Hard", GETCOLOR_WHITE_, FontHandle_3);			// "�n�[�h"
		DrawBox(560, 400, 770, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(560, 400, 460, 480, 560, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(770, 400, 770, 480, 870, 480, GETCOLOR_WHITE_, true);
		DrawStringToHandle(650, 410, "5", GETCOLOR_BLACK_, FontHandle_2);

		DrawBox(875, 400, 1085, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(775, 400, 875, 400, 875, 480, GETCOLOR_WHITE_, true);
		DrawTriangle(1085, 400, 1185, 400, 1085, 480, GETCOLOR_WHITE_, true);
		DrawStringToHandle(950, 410, "10", GETCOLOR_BLACK_, FontHandle_2);

		//�����̐F�ύX�p
		ModeSelect();
	}

	return;
}

//�I��������
void SelectionInit(void)
{

	//�ϐ������������Ȃ���
	Dasite_1 = Nonselect;					//���߂̏o����
	Dasite_2 = Nonselect;					//���̏o���� 
	Misete_1 = Nonselect;					//���߂̌�����
	Misete_2 = Nonselect;					//���̌����� 
	Syoubute_You = Nonselect;				//��������� 
	Enemyte_1 = Nonselect;				//�G�̏��߂̏o����
	Enemyte_2 = Nonselect;				//�@�@���̏o����
	Syoubute_Enemy = Nonselect;			//��������� 

	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");
	}

	return;
}
//�I���Ǘ�
void SelectionCtrl(void)
{
	SelectionProc();	//���������Ă���
	SelectionDraw();	//�`�悷��

	return;
}
//�I������
void SelectionProc(void)
{
	//�V�[���؂�ւ��i�o���肪��I�΂�� K �������ꂽ�Ƃ��j
	if (DasiteCheck() == true) {

		//�R���s���[�^�̎�������_���Ō��߂�
		switch (Point_Enemy) {		//�l�ԑ��̃|�C���g�ɂ���Ĕ��f
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

		//�؂�ւ�
		NowGameScene = CheckScene;

		//�m�F��ʏ�����
		CheckInit();

		return;
	}

	return;
}
//�I��`��
void SelectionDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == SelectionScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//�`��
		DrawCircleAA(340, 560, 140, 64, GETCOLOR_WHITE_);
		DrawCircleAA(640, 560, 140, 64, GETCOLOR_WHITE_);
		DrawCircleAA(940, 560, 140, 64, GETCOLOR_WHITE_);
		DrawExtendGraph(220, 450, 460, 670, GHandle_GuHa, TRUE);
		DrawExtendGraph(520, 450, 760, 670, GHandle_TyoHa, TRUE);
		DrawExtendGraph(820, 450, 1060, 670, GHandle_PaHa, TRUE);

		if (BoutPointCheck_You == 2 && Dasite_2 == Nonselect) {
			switch (Dasite_1) {
			case Gu:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
				DrawCircleAA(340, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��
				break;
			case Tyo:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
				DrawCircleAA(640, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��
				break;
			case Pa:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);			//�u�����h���[�h�ɂ��ē��߂����ĕ`��
				DrawCircleAA(940, 560, 140, 64, GETCOLOR_BLACK_);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h���[�h�I��
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

//�m�F������
void CheckInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

	}

	return;
}
//�m�F�Ǘ�
void CheckCtrl(void)
{
	CheckProc();	//���������Ă���
	CheckDraw();	//�`�悷��

	return;
}
//�m�F����
void CheckProc(void)
{
	//�V�[���؂�ւ��i�X�y�[�X�L�[�������ꂽ�Ƃ��j
	if (ShowSelect() == true) {

		if (BoutPointCheck_You == 2) {						//�J�W���A�����[�h�̎�
			Syoubute_Enemy = 0 + rand() % 2 == 0 ? Enemyte_1 : Enemyte_2;
		}
		else {												//�n�[�h���[�h�̎�
			/*
			�G���̏���������߂�
			����1 : �G���̌����Ă̏����E�����E��������0.1.2�Ŕ��f
			����2 : �l�ԑ�����������o���m����������΁@0�A�قȂ�o���o���m����������΁@1
					���f�ޗ��́A�l�ԑ��̃|�C���g��5�_���̎�
						0��1�_�̂Ƃ��͓�������o���đ����̃|�C���g���Ƃ�\���������̂�0
						2�_�̎���3�_�Ƃ邽�߂ɓ�������o���\���������̂�0
						3�_�̎���2�_�Ƃ�΂悢�̂ŁA���m���̍����قȂ�o������o���\���������̂�1
					�̂悤�Ȋ����@
			����3 : �����ق��̊m��
			����3 : �Ⴂ�ق��̊m��
			*/
			int VoD = Victory_or_Defeat[Enemyte_1][Misete_1 == Hatena ? Dasite_2 : Dasite_1];
			switch (Point_You) {		//�l�ԑ��̃|�C���g�ɂ���Ĕ��f
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

		//�؂�ւ�
		NowGameScene = BoutScene;

		//������ʏ�����
		BoutInit();

		return;
	}

	return;
}
//�m�F�`��
void CheckDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == CheckScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//�`��
		DrawStringToHandle(340, 150, "����Ɍ�������I��", GETCOLOR_WHITE_, FontHandle_2);

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
		DrawFormatString(0, 100, GETCOLOR_WHITE_, "%s", Enemyte_1 != Gu ? (Enemyte_1 == Pa ? "�p�[" : "�`���L") : "�O�[" );
		DrawFormatString(0, 120, GETCOLOR_WHITE_, "%s", Enemyte_2 != Gu ? (Enemyte_2 == Pa ? "�p�[" : "�`���L") : "�O�[");
	*/
	}

	return;
}

//����������
void BoutInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

	}

	return;
}
//�����Ǘ�
void BoutCtrl(void)
{
	BoutProc();	//���������Ă���
	BoutDraw();	//�`�悷��

	return;
}
//��������
void BoutProc(void)
{
	//�V�[���؂�ւ��i�������ʕ`���j
	if (BoutResult() == true) {

		//�֑ؑO�Ƀ|�C���g���Z
		AddPoint(&Point_You, BoutPointCheck_You, Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2, Syoubute_Enemy);
		AddPoint(&Point_Enemy, BoutPointCheck_Enemy, Syoubute_Enemy, Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2);

		//�؂�ւ�
		NowGameScene = ScoreScene;

		//�X�R�A��ʏ�����
		ScoreInit();

		return;
	}

	//�������~�肽��
	if (BoutPointCheck_You != 2 && (KeyClick(KEY_INPUT_DELETE) == true || BoxBottun(1108, 427, 1235, 449) == true)) {
		
		Syoubute_You = Gu;			  //���U���g�̃|�C���g���f�p ���ł��ǂ�
		Syoubute_Enemy = Hatena;      //���U���g�̃|�C���g���f�p�� 3 �ɂ���
		
		AddPoint(&Point_You, BoutPointCheck_You, Syoubute_You, Syoubute_Enemy);
		AddPoint(&Point_Enemy, BoutPointCheck_Enemy, Syoubute_Enemy, Syoubute_You);
		
		NowGameScene = ScoreScene;
	}

	return;
}
//�����`��
void BoutDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == BoutScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//������̑I��
		BoutCheckYou();

		//�`��
		DrawCircleAA(400, 500, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(400, 500, 140, 64, GETCOLOR_BLACK_);
		DrawCircleAA(880, 500, 150, 64, GETCOLOR_WHITE_);
		DrawCircleAA(880, 500, 140, 64, GETCOLOR_BLACK_);

		//�I�΂ꂽ���̌���h��
		if (Syoubute_You == Misete_1) DrawCircleAA(400, 500, 142, 64, GETCOLOR_WHITE_);
	    else if (Syoubute_You == Misete_2) DrawCircleAA(880, 500, 142, 64, GETCOLOR_WHITE_);
		DasiteDraw(280, 390, 240, 220, Dasite_1);
		DasiteDraw(760, 390, 240, 220, Dasite_2);

		DrawStringToHandle(405, 150, "����������I��", GETCOLOR_WHITE_, FontHandle_2);

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

//�X�R�A������
void ScoreInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

	}

	return;
}
//�X�R�A�Ǘ�
void ScoreCtrl(void)
{
	ScoreProc();	//���������Ă���
	ScoreDraw();	//�`�悷��

	return;
}
//�X�R�A����
void ScoreProc(void)
{

	//�V�[���؂�ւ�
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386)) {


		//�؂�ւ�
		//�ǂ��炩�����_�ȏ�Ń��U���g��
		if (ScoreCheck() == true) {

			//�؂�ւ��O�̉��
			DrawStringToHandle(580, 300, "Final", GETCOLOR_WHITE_, FontHandle_3);
			ScreenFlip();
			WaitTimer(1000);
			Blend_Black(0);

			NowGameScene = ResultScene;
			ResultInit();

			return;
		}
		else {
			//�������_�ȉ��ōēx�o����I���ֈڍs
			//BoutPointCheck_��0���đ�����Ȃ��Ƒ���������
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
//�X�R�A�`��
void ScoreDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == ScoreScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);

		//�`��
		switch (Victory_or_Defeat[Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2][Syoubute_Enemy]) {
		case 0: //����
			DrawStringToHandle(450, 80, "V i c t o r y", GETCOLOR_ORANGE_, FontHandle_4);
			break;
		case 1: //����
		case 4: //����
			DrawStringToHandle(468, 80, "D e f e a t", GETCOLOR_BLUE_, FontHandle_4);
			break;
		case 2: //������
			DrawStringToHandle(515, 80, "D r a w", GETCOLOR_CYAN_, FontHandle_4);
			break;
		}

		int s_sen = 5;	//���̕�
		int s_sen2 = 90;	//���̕�2
		int s_haba = 300;	//����
		int s_taka = 300;	//����

		int sx_rr = 250;			//�E�̎l�p�̉E��x
		int sy_rr = 350;			//�E�̎l�p�̉E��y
		int sx_rl = sx_rr + s_haba;	//�E�̎l�p�̕�
		int sy_rl = sy_rr + s_taka;	//�E�̎l�p�̍���

		int sx_lr = 1280 - (s_haba + sx_rr);	//���̎l�p�̉E��x
		int sy_lr = sy_rr;						//���̎l�p�̉E��y
		int sx_ll = sx_lr + s_haba;				//���̎l�p�̕�
		int sy_ll = sy_rr + s_taka;				//���̎l�p�̍���
		//�E�̎l�p
		DrawBox(sx_rr, sy_rr, sx_rl, sy_rl - s_taka - s_sen2, GETCOLOR_WHITE_, true);		//�@�P
		DrawBox(sx_rr + s_haba - s_sen, sy_rr, sx_rl, sy_rl, GETCOLOR_WHITE_, true);		//�@�@�b
		DrawBox(sx_rr, sy_rr, sx_rl - s_haba + s_sen, sy_rl, GETCOLOR_WHITE_, true);		//�b
		DrawBox(sx_rr, sy_rr + s_taka - s_sen, sx_rl, sy_rl, GETCOLOR_WHITE_, true);		//�@�Q
		DrawStringToHandle(305, sy_rr - 60, "Your point", GETCOLOR_BLACK_, FontHandle_1);
		//���̎l�p
		DrawBox(sx_lr, sy_lr, sx_ll, sy_ll - s_taka - s_sen2, GETCOLOR_WHITE_, true);	//�@�P
		DrawBox(sx_lr + s_haba - s_sen, sy_lr, sx_ll, sy_ll, GETCOLOR_WHITE_, true);	//�@�@�b
		DrawBox(sx_lr, sy_lr, sx_ll - s_haba + s_sen, sy_ll, GETCOLOR_WHITE_, true);	//�b
		DrawBox(sx_lr, sy_lr + s_taka - s_sen, sx_ll, sy_ll, GETCOLOR_WHITE_, true);	//�@�Q
		DrawStringToHandle(753, sy_rr - 60, "Enemy's point", GETCOLOR_BLACK_, FontHandle_1);

		//�|�C���g�`��
		int PointWidth;
		int VoD;
		//�����|�C���g
		PointWidth = (GetDrawFormatStringWidth("%d",Point_You) / 9) - 1;		//������ - 1
		DrawFormatStringToHandle(
			sx_rr + 105 - (45 * PointWidth),	//�E�� x ���W (2���̎���45px���ɂ��炷)
			sy_rr + 85,							//�E�� y ���W			
			GETCOLOR_WHITE_,
			FontHandle_5,
			"%d", Point_You
		); 
		VoD = Victory_or_Defeat[Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2][Syoubute_Enemy];
		DrawFormatStringToHandle(
			sx_rr + 93, sy_rr + 10, GETCOLOR_WHITE_, FontHandle_1, 
			BoutPoint[BoutPointCheck_You][VoD] < 0 ? "[ %d ]" : "[ +%d ]",  // + �̎��Ɂu+�v���t��
			BoutPoint[BoutPointCheck_You][VoD]
		);

		//�G�|�C���g
		PointWidth = (GetDrawFormatStringWidth("%d",Point_Enemy) / 9) - 1;		//������ - 1
		DrawFormatStringToHandle(
			sx_lr + 105 - (45 * PointWidth),	//�E�� x ���W (2���̎���45px���ɂ��炷)
			sy_lr + 85,							//�E�� y ���W			
			GETCOLOR_WHITE_,
			FontHandle_5,
			"%d", Point_Enemy
		);
		VoD = Victory_or_Defeat[Syoubute_Enemy][Syoubute_You == Misete_1 ? Dasite_1 : Dasite_2];
		DrawFormatStringToHandle(
			sx_lr + 93, sy_lr + 10, GETCOLOR_WHITE_, FontHandle_1,
			BoutPoint[BoutPointCheck_Enemy][VoD] < 0 ? "[ %d ]" : "[ +%d ]",  // + �̎��Ɂu+�v���t��
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

//���U���g������
void ResultInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");
	}
	return;
}
//���U���g�Ǘ�  
void ResultCtrl(void)
{
	ResultProc();	//���������Ă���
	ResultDraw();	//�`�悷��

	return;
}
//���U���g����  
void ResultProc(void)
{
	//�V�[���؂�ւ��i�X�y�[�X�L�[�������ꂽ�Ƃ��j
	if (KeyClick(KEY_INPUT_RETURN) == true || BoxBottun(1150, 364, 1277, 386)) {
		
		//�|�C���g�̏�����
		Point_You = 0;					//�����̃|�C���g
		Point_Enemy = 0;					//�G�̃|�C���g
		//���[�h��������
		NowMode = NonMode;
		//���[�h�`�F�b�N�̏�����
		BoutPointCheck_You = 999;			    //�����|�C���g���f�̕ϐ�(����)
		BoutPointCheck_Enemy = 999;			    //�����|�C���g���f�̕ϐ�(�G)

		//�؂�ւ�
		NowGameScene = RuleScene;

		//���[����ʏ�����
		RuleInit();

		return;
	}

	return;
}
//���U���g�`��  
void ResultDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == ResultScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GETCOLOR_BLACK_, true);
		//�`��
		if (Point_You > Point_Enemy) {
			DrawBox(0, 200, 1280, 270, GETCOLOR_ORANGE_, true);
			DrawStringToHandle(50, 100, "Congratulations!", GETCOLOR_YELLOW_, FontHandle_6);
		}
		else {
			DrawBox(0, 200, 1280, 270, GETCOLOR_BLUE_, true);
			DrawStringToHandle(370, 100, "Too bad", GETCOLOR_PURPLE_, FontHandle_6);
		}
		int PointWidth;
		PointWidth = (GetDrawFormatStringWidth("%d", Point_You) / 9) - 1;		//������ - 1
		DrawFormatStringToHandle(
			335 - (170 * PointWidth),	//�E�� x ���W (2���̎���45px���ɂ��炷)
			400,							//�E�� y ���W			
			GETCOLOR_WHITE_,
			FontHandle_7,
			"%d", Point_You
		);
		PointWidth = (GetDrawFormatStringWidth("%d", Point_Enemy) / 9) - 1;		//������ - 1
		DrawFormatStringToHandle(
			750 - (50 * PointWidth),	//�E�� x ���W (2���̎���45px���ɂ��炷)
			400,							//�E�� y ���W			
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