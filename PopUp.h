//�|�b�v�A�b�v��t�H���g�X�^�C�����A�ׂ��ȏ����̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

//�}�N����`
#define MODECOUNT 5						//���[�h�̐�
#define MODENAMEMAX 20					//���[�h���̕���MAX
 
//�O���[�o���ϐ�
extern int FontHandle_0;			//�t�H���gNo0
extern int FontHandle_1;			//�t�H���gNo1
extern int FontHandle_2;			//�t�H���gNo2
extern int FontHandle_3;			//�t�H���gNo3
extern int FontHandle_4;			//�t�H���gNo4
extern int FontHandle_5;			//�t�H���gNo5
extern int FontHandle_6;			//�t�H���gNo6
extern int FontHandle_7;			//�t�H���gNo7
extern int FontHandle_8;			//�t�H���gNo7

extern int GHandle_Title;					//�摜�f�[�^(�^�C�g��)
extern int GHandle_GuHa;					//�摜�f�[�^(�O�[:�n�[�h)
extern int GHandle_TyoHa;					//�摜�f�[�^(�`���L:�n�[�h)
extern int GHandle_PaHa;					//�摜�f�[�^(�p�[:�n�[�h)
extern int GHandle_GuKa;					//�摜�f�[�^(�O�[:�J�W���A��)
extern int GHandle_TyoKa;					//�摜�f�[�^(�`���L:�J�W���A��)
extern int GHandle_PaKa;					//�摜�f�[�^(�p�[:�J�W���A��)
extern int GHandle_Q;						//�摜�f�[�^(�N�G�X�`�����}�[�N)
extern int GHandle_QG;						//�摜�f�[�^(�O���[�N�G�X�`�����}�[�N)
extern int GHandle_QT;						//�摜�f�[�^(�����N�G�X�`�����}�[�N)
extern int GHandle_M;						//�摜�f�[�^(�ڋ�)
extern int GHandle_MG;						//�摜�f�[�^(�O���[�ڋ�)
extern int GHandle_HN;						//�摜�f�[�^(��@����)
extern int GHandle_HB;						//�摜�f�[�^(��@������)
extern int GHandle_HF;						//�摜�f�[�^(��@�~���)

extern int FileHandle_Rule;					//�t�@�C���f�[�^

extern char StringBuffer[2048];	        //�e�L�X�g�f�[�^�p�̃o�b�t�@


//�O���v���g�^�C�v�錾
extern void PopUpView(void);			//����|�b�v�A�b�v
extern void ModeView(void);				//�������[�h�\��

extern void Data_Teigi(void);			//�f�[�^�̒�`

extern void RuletoSelection(unsigned int getcolor_);		//�؂�ւ��`��

extern void Blend_Black(int spead);			//���X�ɍ��ɑ���

extern void TxtDraw(int FileHandle);	//�e�L�X�g�f�[�^�`��
