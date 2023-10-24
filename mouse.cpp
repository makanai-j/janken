//�}�E�X�����̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "mouse.h"
#include "PopUp.h"
#include "game_scene.h"
#include "game_sistem.h"
#include <math.h>

//�O���[�o���ϐ�
MousePoint NowPoint;				//���݂̃}�E�X�̈ʒu
MousePoint OldPoint;				//�ȑO�̃}�E�X�̈ʒu

int NowMousePressFrame[MOUSEKINDMAX];	//���݂̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�
int OldMousePressFrame[MOUSEKINDMAX];	//�ȑO�̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�

int NowWheelValue;					//���݂̃}�E�X�̃z�C�[����]��
int OldWheelValue;				//�ȑO�̃}�E�X�̃z�C�[����]��

//�}�E�X�̃{�^���R�[�h�ƃt���[�������Ǘ����Ă���z��̗v�f����R�Â���
int MouseCodeIndex[MOUSEKINDMAX]{
	MOUSE_INPUT_LEFT,				//�z��̗v�f��0�ɂ̓}�E�X�̃{�^������0x0001�̏�������
	MOUSE_INPUT_RIGHT,				//�z��̗v�f��1�ɂ̓}�E�X�̃{�^������0x0002�̏�������
	MOUSE_INPUT_MIDDLE,				//�z��̗v�f��2�ɂ̓}�E�X�̃{�^������0x0004�̏�������
	MOUSE_INPUT_4,					//�z��̗v�f��3�ɂ̓}�E�X�̃{�^������0x0008�̏�������
	MOUSE_INPUT_5,					//�z��̗v�f��4�ɂ̓}�E�X�̃{�^������0x0010�̏�������
	MOUSE_INPUT_6,					//�z��̗v�f��5�ɂ̓}�E�X�̃{�^������0x0020�̏�������
	MOUSE_INPUT_7,					//�z��̗v�f��6�ɂ̓}�E�X�̃{�^������0x0040�̏�������
	MOUSE_INPUT_8,					//�z��̗v�f��7�ɂ̓}�E�X�̃{�^������0x0080�̏�������
};

//Now�����n�̕ϐ��̒l��Old�����n�̕ϐ��֓����
void MouseNowIntoOld(void)
{
	OldPoint = NowPoint;		//�}�E�X�̈ʒu
	
	//�t���[����
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}

	//�z�C�[����
	OldWheelValue = NowWheelValue;

	return;
}

//�}�E�X�̃{�^���R�[�h��z��̗v�f���ɕϊ�����
int MouseCodeToIndex(int MOUSE_INPUT_)
{
	for (int i = 0; i < MOUSEKINDMAX; i++) {

		//�}�E�X�R�[�h���R�Â�����Ă���Ȃ�
		if (MouseCodeIndex[i] == MOUSE_INPUT_) {

			return i;
		}
	}
	//�}�E�X�R�[�h���Ȃ��Ȃ�G���[
	return MOUSECODEERRINDEX;
}

//�}�E�X�����̏����̏�����
void MouseInit(void)
{
	//�}�E�X�����̏�����
	NowPoint.x = 0;
	NowPoint.y = 0;

	//�t���[����
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		NowMousePressFrame[i] = 0;
	}

	//�z�C�[����
	NowWheelValue = 0;

	//old�n��������
	MouseNowIntoOld();

	return;
}

//�}�E�X�����̍X�V
void MouseUpdate(void)
{
	//�}�E�X�̃{�^���������ׂĎ擾����ϐ�
	int Input;

	//���݂̏����ȑO�̏��Ƃ��ĕۑ�
	MouseNowIntoOld();

	//���݂̃}�E�X�̃N���C�A���g���W�̈ʒu���擾�@
	GetMousePoint(&NowPoint.x, &NowPoint.y);		
	//GetMousePoint(&NowPoint.x�̃A�h���X, &NowPoint.y�̃A�h���X)
	//NowPoint.x��X���W�̒l�������Ė߂��Ă���By�����l�B

	//�����A�}�E�X�̍��W���Q�[����ʊO�ɂ���Ȃ�A�Q�[����ʓ��Ɏ��߂�
	if (NowPoint.x < 0) { NowPoint.x = 0;} //��
	else if (NowPoint.x > GAMEWIDTH) { NowPoint.x = GAMEWIDTH; } //�E
	if (NowPoint.y < 0) { NowPoint.y = 0; } //��
	else if (NowPoint.y > GAMEHEIGHT) { NowPoint.y = GAMEHEIGHT; } //��

	//�}�E�X�̃{�^��������C�Ɏ擾
	Input = GetMouseInput();

	//�e�{�^���������Ă��邩�`�F�b�N
	for (int i = 0; i < MOUSEKINDMAX; i++) {
		/* [if���̏�������]
		   �܂��@�W�V�U�T�S���E��
				 �P�P�P�P�P�P�P�P�@�@�Ƃ������悤�ɁA2�i����
				 ���ꂼ��̌��Ƀ}�E�X�e�{�^��������U���Ă���B�i���̓z�C�[���j

				 �����&���Z�Ń}�X�N�������邱�Ƃ�
				 �ǂ��̃{�^���������ꂽ�̂��𔻒f���邱�Ƃ��\�B

				 �i��j�E�{�^���������ꂽ�Ƃ�
				 00000010 & 00000001 = 00000000   ������Ȃ��ȁ[
				 00000010 & 00000010 = 00000010   �E���I
		 */
		if ((Input & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			//���݉����Ă���{�^���̃t���[�������J�E���g�A�b�v
			NowMousePressFrame[i]++;
		}
		else if ((Input & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			//���݉����Ă���{�^���̃t���[�������[���N���A
			NowMousePressFrame[i] = 0;
		}
	}

	//�z�C�[����]�ʂ��擾
	NowWheelValue = GetMouseWheelRotVol();

	return;
}

//����̃}�E�X����������
//�����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
bool MouseDown(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MOUSECODEERRINDEX) {
		//���݉����Ă���Ȃ�
		if (NowMousePressFrame[index] > 0) {

			return true;		//�����Ă���
		}
	}


	return FALSE;			//�����ĂȂ�
}


//����̃}�E�X����������
//�����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
//�����F�u�}�E�X�{�^�����������}�E�X�{�^�����グ��v���Z�b�g�ōs��ꂽ�����A�N���b�N
bool MouseClick(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MOUSECODEERRINDEX) {
		//���݉����Ă���Ȃ�
		if (NowMousePressFrame[index]  == 0			//���݂͉����Ă��Ȃ���
			&& OldMousePressFrame[index] > 0) {		//�O�͉����Ă���

			return true;		//�����Ă���
		}
	}

	return FALSE;			//�����ĂȂ�
}

//�}�E�X�̌��݈ʒu���w��̏ꏊ�ɂ��邩(�{�^���p)
bool MouseHere(void)
{
	if (NowPoint.x > 590 && NowPoint.x < 690				//x�͈͓̔�����
		&& NowPoint.y > 500 && NowPoint.y < 550) {			//y�͈͓̔�
		
		return true;
	}
	
	return false;
}

//����̃}�E�X�{�^�����������t���[����
//�����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
//�߂�l�̓t���[����
int MousePressFrame(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h��z��̗v�f���ɕϊ�
	int index = MouseCodeToIndex(MOUSE_INPUT_);

	//���݂���}�E�X�R�[�h�Ȃ�
	if (index != MOUSECODEERRINDEX) {

		return NowMousePressFrame[index];
	}


	return 0;
}

//�}�E�X�̌��݈ʒu���擾����
MousePoint GetPointMouse(void)
{
	return NowPoint;
}

//�}�E�X�̑O�̈ʒu���擾����
MousePoint GetOldPointMouse(void)
{
	return OldPoint;
}

//�}�E�X�̌��݈ʒu���擾����
MousePoint GetDiffPointMouse(void)
{
	MousePoint diff;
	diff.x = OldPoint.x - NowPoint.x;
	diff.y = OldPoint.y - NowPoint.y;
	return diff;
}

//�}�E�X�̌��݂̃z�C�[���ʂ��擾����
int GetWheelMouse(void)
{
	return NowWheelValue;
}

//�{�^���̓����蔻��
//���[�����
bool RuleBottun(Mode Bottun, int x, int y)
{
	switch (Bottun) {
	case Casual_1:
		if (720 - y - 0.8 * x - 102 < 0			//float�^ (�J�W���A���̓����蔻��)
		&& 720 - y + 0.8 * x - 1083.6 < 0	//float�^ (�J�W���A���̓����蔻��)
		&& 170 < y && y < 250) {			//�J�W���A��������
			DrawStringToHandle(600, 180, "1", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Casual_3:
		if (720 - y + 0.8 * x - 1083.6 > 0		//float�^ (�J�W���A���̓����蔻��)
		&& 720 - y - 0.8 * x + 231.6 > 0	//float�^ (�J�W���A���̓����蔻��)
		&& 170 < y && y < 250){				//�J�W���A��������
			DrawStringToHandle(810, 180, "3", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Casual_5:
		if (720 - y - 0.8 * x + 231.6 < 0		//float�^ (�J�W���A���̓����蔻��)
		&& 720 - y + 0.8 * x - 1418 < 0		//float�^ (�J�W���A���̓����蔻��)
		&& 170 < y && y < 250){				//�J�W���A��������
			DrawStringToHandle(1020, 180, "5", GETCOLOR_GREEN_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Hard_5:
		if (720 - y - 0.8 * x + 128	< 0			//float�^ (�J�W���A���̓����蔻��)
		&& 720 - y + 0.8 * x - 937.6 < 0	//float�^ (�J�W���A���̓����蔻��)
		&& 400 < y && y < 480){				//�n�[�h������
			DrawStringToHandle(650, 410, "5", GETCOLOR_DARKRED_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
		break;
	case Hard_10:
		if (720 - y + 0.8 * x - 937.6 > 0		//float�^ (�J�W���A���̓����蔻��)
		&& 720 - y - 0.8 * x + 628 > 0		//float�^ (�J�W���A���̓����蔻��)
		&& 400 < y && y < 480){				//�n�[�h������
			DrawStringToHandle(950, 410, "10", GETCOLOR_DARKRED_, FontHandle_2);
			if (MouseClick(MOUSE_INPUT_LEFT) == true) {
				return true;
			}
		}
	}
	return false;
	/*
	720 - y - 0.8 * x - 102			//float�^ (�J�W���A���̓����蔻��)
	720 - y + 0.8 * x - 1083.6		//float�^ (�J�W���A���̓����蔻��)
	720 - y - 0.8 * x + 231.6		//float�^ (�J�W���A���̓����蔻��)
	720 - y + 0.8 * x - 1418		//float�^ (�J�W���A���̓����蔻��)
	
	720 - y - 0.8 * x + 128		//float�^ (�n�[�h�̓����蔻��)
	720 - y + 0.8 * x - 937.6	//float�^ (�n�[�h�̓����蔻��)
	720 - y - 0.8 * x + 628		//float�^ (�n�[�h�̓����蔻��)
	*/
}
//�l�p�{�^��
bool BoxBottun(int rx, int ry, int lx, int ly)
{
	if (rx < GetPointMouse().x && GetPointMouse().x < lx
		&& ry < GetPointMouse().y && GetPointMouse().y < ly
		&& MouseClick(MOUSE_INPUT_LEFT) == true) {
		return true;
	}
	return false;
}
//�}���̃{�^��
//�N���b�N
bool CircleBottunClick(int x, int y, int r)
{
	double dis;		//���S�ƃ}�E�X�̋���
	int dis_x;		//���S x ���W�ƃ}�E�X x �̍�
	int dis_y;		//���S y ���W�ƃ}�E�X y �̍�

	dis_x = x - GetPointMouse().x;
	dis_y = y - GetPointMouse().y;
	dis = sqrt(pow(dis_x, 2) + pow(dis_y, 2));

	if (dis < r		//�w�肵�����a��������
		&& MouseClick(MOUSE_INPUT_LEFT) == true) {
		return true;
	}
	return false;
}
//�̂�
bool CircleBottunOn(int x, int y, int r)
{
	double dis;		//���S�ƃ}�E�X�̋���
	int dis_x;		//���S x ���W�ƃ}�E�X x �̍�
	int dis_y;		//���S y ���W�ƃ}�E�X y �̍�

	dis_x = x - GetPointMouse().x;
	dis_y = y - GetPointMouse().y;
	dis = sqrt(pow(dis_x, 2) + pow(dis_y, 2));

	if (dis < r) {	//�w�肵�����a��������
		return true;
	}
	return false;
}