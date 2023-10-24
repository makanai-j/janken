//fps�����̃w�b�_�[�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DXLib.h"

//�}�N����`
#define GAMEFPS		 60			//�ݒ肵����FPS

#define MICROSECOND  1000000.0f	//1�}�C�N���b
#define MILISECOND   1000.0f	//1�~���b
#define WAITTIMEMILL 3000		//�ő�Ŏ��Ă�~���b

//�\���̂̒�`�����O�̍Ē�`
typedef struct _FPS {
	LONGLONG FirstTakeTime = 0;			//1�t���[���ڂ̌v������
	LONGLONG NowTakeTime = 0;			//���݂̌v������
	LONGLONG OldTakeTime = 0;			//�ȑO�̌v������

	float Deltatime = 0.000001f;		//�f���^�^�C���i�o�ߎ��ԁj
	int FrameCount = 1;					//���݂̃t���[�����i1�t���[���`MAX�t���[���ڂ܂Łj
	float Average = 0.0f;				//����FPS�l
}FPS;

//�O���O���[�o���ϐ�
extern FPS fps;

//�O���v���g�^�C�v�錾
extern void FPSInit(void);				//FPS������
extern void FPSCheck(void);				//FPS�v��
extern void FPSDraw(void);				//FPS�`��
extern void FPSWait(void);				//FPS�ҋ@