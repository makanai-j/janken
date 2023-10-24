//�Q�[�������̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "game.h"
#include "key.h"

//�O���[�o���ϐ�

//�Q�[���V�[��
GameScene NowGameScene;		//���݂̃Q�[���V�[��

//�Q�[���V�[���̖��O
char GameSceneName[GAMESCENECOUNT][GAMESCENENAMEMAX]
{
	"�^�C�g�����",
	"�v���C���",
	"���U���g���"
};

//�֐�

//�^�C�g��������
void TitleInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

		ScreenFlip();
		WaitTimer(2000);
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
	//�V�[���؂�ւ��i�X�y�[�X�L�[�������ꂽ�Ƃ��j
	if (KeyClick(KEY_INPUT_SPACE) == true){

		//�؂�ւ�
		NowGameScene = PlayScene;

		//�v���C��ʏ�����
		PlayInit();

		return;
	}

	return;
}
//�^�C�g���`��
void TitleDraw(void)
{
	if (GAMEDEBUG == true && NowGameScene == TitleScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(255,123,15), true);

		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "�`�撆");
	}

	return;
}

//�v���C������
void PlayInit(void)
{
	if (GAMEDEBUG == true) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");


		ScreenFlip();
		WaitTimer(2000);
	}

	return;
}
//�v���C�Ǘ�
void PlayCtrl(void)
{
	PlayProc();	//���������Ă���
	PlayDraw();	//�`�悷��

	return;
}
//�v���C����
void PlayProc(void)
{
	//�V�[���؂�ւ��i�X�y�[�X�L�[�������ꂽ�Ƃ��j
	if (KeyClick(KEY_INPUT_SPACE) == true) {

		//�؂�ւ�
		NowGameScene = ResultScene;

		//���U���g��ʏ�����
		ResultInit();

		return;
	}

	return;
}
//�v���C�`��
VOID PlayDraw(VOID)
{
	if (GAMEDEBUG == TRUE && NowGameScene == PlayScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(177, 210, 25), TRUE);

		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "�`�撆");
	}

	return;
}

//���U���g������
VOID ResultInit(VOID)
{
	if (GAMEDEBUG == TRUE) {
		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "������");

		ScreenFlip();
		WaitTimer(2000);
	}

	return;
}
//���U���g�Ǘ�  
VOID ResultCtrl(VOID)
{
	ResultProc();	//���������Ă���
	ResultDraw();	//�`�悷��

	return;
}
//���U���g����  
VOID ResultProc(VOID)
{
	//�V�[���؂�ւ��i�X�y�[�X�L�[�������ꂽ�Ƃ��j
	if (KeyClick(KEY_INPUT_SPACE) == TRUE) {

		//�؂�ւ�
		NowGameScene = TitleScene;

		//�v���C��ʏ�����
		TitleInit();

		return;
	}

	return;
}
//���U���g�`��  
VOID ResultDraw(VOID)
{
	if (GAMEDEBUG == TRUE && NowGameScene == ResultScene) {

		DrawBox(0, 0, GAMEWIDTH, GAMEHEIGHT, GetColor(177, 21, 255), TRUE);

		//�V�[�����\��
		DrawFormatString(
			GAMEWIDTH - 200, 0,
			GetColor(255, 255, 255),
			"%s%s", GameSceneName[NowGameScene], "�`�撆");
	}

	return;
}