//�Q�[���V�[���ؑ֊֌W�̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

//�}�N����`
#define GAMEWIDTH 1280  //��ʂ̕�
#define GAMEHEIGHT 720  //��ʂ̍���
#define GAMECOLOR 32   //��ʂ̐F
#define GAMEICON 1001  //��ʃA�C�R��

#define GAMEDEBUG true	//�f�o�b�O���[�h

#define GAMESCENECOUNT 7 //�Q�[���V�[���̐�
#define GAMESCENENAMEMAX 20 //�Q�[���V�[�����̕���MAX

#define GETCOLOR_BLACK_ GetColor(0,0,0)		    //���F
#define GETCOLOR_WHITE_ GetColor(255,255,255)   //���F
#define GETCOLOR_RED_ GetColor(255,0,0)		    //�ԐF(���邢)
#define GETCOLOR_DARKRED_ GetColor(180,0,0)		//�ԐF(�Â�)
#define GETCOLOR_GREEN_ GetColor(0,150,0)       //�ΐF
#define GETCOLOR_BLUE_ GetColor(0,0,255)	    //�F
#define GETCOLOR_PURPLE_ GetColor(255,0,255)    //���F
#define GETCOLOR_ORANGE_ GetColor(255,100,0)    //�I�����W�F
#define GETCOLOR_YELLOW_ GetColor(255,215,0)    //���F
#define GETCOLOR_CYAN_ GetColor(0,149,141)      //�V�A��

//�Q�[���V�[��
typedef enum {
	TitleScene,		//�^�C�g���V�[��
	RuleScene,		//���[���V�[��
	SelectionScene,	//�I���V�[��
	CheckScene,		//�m�F�V�[��
	BoutScene,		//�����V�[��
	ScoreScene,		//�X�R�A�V�[��
	ResultScene		//���U���g�V�[��
}GameScene;
//�O���̃O���[�o���ϐ�
extern GameScene NowGameScene;		//���݂̃Q�[���V�[��
extern GameScene OldGameScene;		//���O�̃Q�[���V�[��
//�O���̃v���g�^�C�v�錾
extern void TitleInit(void);		//�^�C�g��������
extern void TitleCtrl(void);		//�^�C�g���Ǘ�
extern void TitleProc(void);		//�^�C�g������
extern void TitleDraw(void);		//�^�C�g���`��

extern void RuleInit(void);		    //�I��������
extern void RuleCtrl(void);		    //�I���Ǘ�
extern void RuleProc(void);		    //�I������
extern void RuleDraw(void);		    //�I��`��

extern void SelectionInit(void);		//�I��������
extern void SelectionCtrl(void);		//�I���Ǘ�
extern void SelectionProc(void);		//�I������
extern void SelectionDraw(void);		//�I��`��

extern void CheckInit(void);		//�m�F������
extern void CheckCtrl(void);		//�m�F�Ǘ�
extern void CheckProc(void);		//�m�F����
extern void CheckDraw(void);		//�m�F�`��

extern void BoutInit(void);		//����������
extern void BoutCtrl(void);		//�����Ǘ�
extern void BoutProc(void);		//��������
extern void BoutDraw(void);		//�����`��

extern void ScoreInit(void);		//�X�R�A������
extern void ScoreCtrl(void);		//�X�R�A�Ǘ�
extern void ScoreProc(void);		//�X�R�A����
extern void ScoreDraw(void);		//�X�R�A�`��

extern void ResultInit(void);		//���U���g������
extern void ResultCtrl(void);		//���U���g�Ǘ�
extern void ResultProc(void);		//���U���g����
extern void ResultDraw(void);		//���U���g�`��
