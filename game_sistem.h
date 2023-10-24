//�Q�[���V�X�e���̃\�[�X�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

//�}�N����`
#define TEKAZU 4		//�o����̎��
#define TEKAZU1 3		//�o����̎��
#define TEKAZU2 5		//�o����̎��
#define RATIO_SAME(x) (100 * x) / (2 * (10 - x))		//�����ɂ͏o���肪�قȂ銄��(�P�`�X�̐���)
#define RATIO_DIFF(x) (200 * (10 - x)) / x				//�����ɂ͏o���肪�قȂ銄��(�P�`�X�̐���)

//���[�h�̎��
typedef enum {
	Casual_1,
	Casual_3,
	Casual_5,
	Hard_5,
	Hard_10,
	NonMode
}Mode;

typedef enum {
	Gu,
	Tyo,
	Pa,
	Hatena,
	Nonselect
}Dasite;

//����,����,�������@�̔z��
/*
int Victory_or_Defeat[TEKAZU][TEKAZU]{
	//�O�[�A�`���L�A�p�[
	   2,     0,     1,	  //�O�[
	   1,     2,     0,	  //�`���L
	   0,     1,     2,	  //�p�[
};
int BoutPoint[TEKAZU][TEKAZU]{
	//�����A�����A������
	   2,    -1,    0,	  //�����o����
	   1,    -2,   -1,	  //�قȂ�o����
	   1,     0,    0,	  //�J�W���A�����[�h
};
*/

//�O���[�o���ϐ�
extern Mode NowMode;				    //���̃��[�h�Ɛ��_���f
extern int BoutPointCheck_You;			    //�����|�C���g���f�̕ϐ�(����)
extern int BoutPointCheck_Enemy;			    //�����|�C���g���f�̕ϐ�(�G)
extern Dasite Dasite_1;					//���߂̏o����
extern Dasite Dasite_2;					//���̏o���� 
extern Dasite Misete_1;					//���߂̌�����
extern Dasite Misete_2;					//���̌����� 
extern Dasite Syoubute_You;				//��������� 
extern Dasite Enemyte_1;				//�G�̏��߂̏o����
extern Dasite Enemyte_2;				//�@�@���̏o����
extern Dasite Syoubute_Enemy;			//��������� 
extern int Point_You;					//�����̃|�C���g
extern int Point_Enemy;					//�G�̃|�C���g
extern int Victory_or_Defeat[TEKAZU][TEKAZU]; //���������̔��f�\
extern int BoutPoint[TEKAZU1][TEKAZU2];         //���[�h�ɂ��|�C���g�\

//�O���v���g�^�C�v�錾
extern bool ModeSelect(void);				//���[�h�Ɛ��_�̑I��
extern bool DasiteCheck(void);				//�o����̑I��
extern void EnemyCheck(int Diff);			//�G�̏o����
extern bool ShowSelect(void);				//��������I��
extern void DasiteDraw(int x, int y, int xx, int yy,Dasite Dasite_x);		//�o����̕`��
extern void MiseteDraw_1(int x, int y, int xx, int yy);						//������̕`��
extern void MiseteDraw_2(int x, int y, int xx, int yy);						//������̕`��
extern void BoutCheckYou(void);					//���������̑I��
extern void BoutCheckEnemy(void);					//���������̑I��
extern bool BoutResult(void);					//�������ʂ̕`��
extern bool AddPoint(int *point,int Bp, Dasite a,Dasite b);					//�X�R�A�̉��Z
extern bool ScoreCheck(void);					//�|�C���g�����_�ȏォ���f
extern void BoutCheckEnemy(int VorD, int OorK, int ratio1, int ratio2);

