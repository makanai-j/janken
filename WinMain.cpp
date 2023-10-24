#include <time.h>
#include "DxLib.h"
#include "fps.h"
#include "game_scene.h"
#include "game_sistem.h"
#include "PopUp.h"
#include "key.h"
#include "mouse.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				 // Log.txt���o�͂��Ȃ�
	ChangeWindowMode(true);								 // �E�B���h�E���[�h�ύX
	SetGraphMode(GAMEWIDTH, GAMEHEIGHT, GAMECOLOR);		//�𑜓x�ݒ�
	SetWindowSize(GAMEWIDTH, GAMEHEIGHT);				//�E�B���h�E�̑傫����ݒ�
	SetMainWindowText("���დ����Q�[��");				//�E�B���h�E�̃^�C�g��
	SetBackgroundColor(0, 0, 0);						//�E�B���h�E�̔w�i�F
	SetWaitVSyncFlag(true);								//���������̐ݒ�
	SetAlwaysRunFlag(true);								//��A�N�e�B�u�ł����s����


	SetWindowIconID(GAMEICON);								//�A�C�R����ݒ�


	// �c�w���C�u��������������
	if (DxLib_Init() == -1) {
		return -1;   // �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);			//����ʂɕ`�悷��i�_�u���o�b�t�@�����O�j

	FPSInit();								//FPS������
	
	KeyInit();								//�L�[�{�[�h������

	MouseInit();							//�}�E�X������

	NowGameScene = TitleScene;				//�^�C�g������X�^�[�g
	//NowGameScene = BoutScene;				//�^�C�g������X�^�[�g

	TitleScene();							//�^�C�g��������

	Data_Teigi();							//�f�[�^��`

	SetDrawMode(DX_DRAWMODE_BILINEAR);		// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���

	srand((unsigned int)time(NULL));		//�����̎�̕ύX

	while (true) {

		//���b�Z�[�W����������
		if (ProcessMessage() != 0) {
			break;							//�������[�v����o��i�Q�[���I���j
		}

		//��ʂ���������i1���[�v������������j
		if (ClearDrawScreen() != 0) {		//�������[�v����o��i�Q�[���I���j
			break;
		}

		//�Q�[������
		{
			FPSCheck();			//FPS�v��
			KeyUpdate();		//�L�[�{�[�h�X�V
			MouseUpdate();		//�}�E�X�X�V

			//�V�[���؂�ւ�
			switch (NowGameScene)
			{
			case TitleScene:
				TitleCtrl();
				break;
			case RuleScene:
				RuleCtrl();
				break;
			case SelectionScene:
				SelectionCtrl();
				break;
			case CheckScene:
				CheckCtrl();
				break;
			case BoutScene:
				BoutCtrl();
				break;
			case ScoreScene:
				ScoreCtrl();
				break;
			case ResultScene:
				ResultCtrl();
				break;
			default:
				break;
			}

			ModeView();			//�����ヂ�[�h�\��
			PopUpView();		//����|�b�v�A�b�v�\��

			OldGameScene = NowGameScene;    //���O�̃Q�[���V�[���̂ۍX�V

			FPSWait();			//FPS�ҋ@
		}



		//���O�ʂ���ʂɕ`��
		ScreenFlip();
	}
	InitFontToHandle();		//�S�t�H���g�f�[�^�̏���
	InitGraph();			//�S�摜�f�[�^����
	FileRead_close(FileHandle_Rule);

	DxLib_End();    // �c�w���C�u�����g�p�̏I������

	return 0;    // �\�t�g�̏I�� 
}