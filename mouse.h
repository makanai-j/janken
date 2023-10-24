//�}�E�X�����̃w�b�_�t�@�C��
#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game_sistem.h"

//�}�N����`
#define MOUSEKINDMAX 8					//�}�E�X�̃{�^���̎��
#define MOUSECODEERRINDEX 999			//�}�E�X�R�[�h��ϊ������v�f�ԍ��̃G���[�l

#define CASUALMOUSE_1(x,y)  720 - y - 0.8 * x - 102			//float�^ (�J�W���A���̓����蔻��)
#define CASUALMOUSE_2(x,y)  720 - y + 0.8 * x - 1083.6		//float�^ (�J�W���A���̓����蔻��)
#define CASUALMOUSE_3(x,y)  720 - y - 0.8 * x + 231.6		//float�^ (�J�W���A���̓����蔻��)
#define CASUALMOUSE_4(x,y)  720 - y + 0.8 * x - 1418		//float�^ (�J�W���A���̓����蔻��)

#define HARDMOUSE_1(x,y)  720 - y - 0.8 * x + 128		//float�^ (�n�[�h�̓����蔻��)
#define HARDMOUSE_2(x,y)  720 - y + 0.8 * x - 937.6		//float�^ (�n�[�h�̓����蔻��)
#define HARDMOUSE_3(x,y)  720 - y - 0.8 * x + 628		//float�^ (�n�[�h�̓����蔻��)

//�\�z��
typedef struct _MousePoint{
	int x;		//�}�E�X��X�̈ʒu
	int y;		//�}�E�X��Y�̈ʒu
}MousePoint;

//�O���̃v���g�^�C�v�錾
extern void MouseNowIntoOld(void);					//Now�����n�̕ϐ��̒l��Old�����n�̕ϐ��֓����
extern int MouseCodeToIndex(int MOUSE_INPUT_);		//�}�E�X�̃{�^���R�[�h��z��̗v�f�ԍ��ɕϊ�����


extern void MouseInit(void);						//�}�E�X�����̏�����
extern void MouseUpdate(void);						//�}�E�X�����̍X�V
extern bool MouseDown(int MOUSE_INPUT_);				//����̃{�^������������
extern bool MouseClick(int MOUSE_INPUT_);				//����̃{�^�����N���b�N������
extern bool MouseHere(void);							//�͈͓����𔻒�
extern int  MousePressFrame(int MOUSE_INPUT_);		//����̃{�^�����������t���[����


extern MousePoint GetPointMouse(void);				//�}�E�X�̌��݈ʒu���擾����
extern MousePoint GetOldPointMouse(void);			//�}�E�X�̑O�̈ʒu���擾����
extern MousePoint GetDiffPointMouse(void);			//�}�E�X�̑O�ƌ��݂̍����擾����

extern int GetWheelMouse(void);						//�}�E�X�̌��݂̃z�C�[���ʂ��擾����

//�����蔻��
extern bool RuleBottun(Mode Bottun, int x, int y);			//���[����ʃ{�^��
extern bool BoxBottun(int rx, int ry, int lx, int ly);		//�l�p�̃{�^��
extern bool CircleBottunClick(int x, int y, int r);			//�}���̃{�^���N���b�N
extern bool CircleBottunOn(int x, int y, int r);			//�}���̃{�^������