//�L�[�{�[�h�����̃\�[�X�t�@�C��

//�w�b�_�t�B���ǂݍ���
#include "key.h"

//�O���[�o���ϐ�

//���݂̃L�[�������Ă���t���[����
int NowKeyPressFrame[KEYKINDMAX];

//1�O�̃L�[�������Ă���t���[����
int OldKeyPressFrame[KEYKINDMAX];

//�֐�


//�L�[�{�[�h�����̏�����
void KeyInit(void)
{
	//�z��̏�����
	for (int i = 0; i < KEYKINDMAX; i++) {
		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;
	}

	return;
}

//�L�[�{�[�h�����̍X�V
void KeyUpdate(void)
{
	//�ꎞ�I�ɕێ�����L�[���
	char KeyState[KEYKINDMAX];

	//�S�ẴL�[������x�Ɏ擾
	GetHitKeyStateAll(KeyState);

	//�L�[�����X�V
	for (int i = 0; i < KEYKINDMAX; i++) {
		//1�O�̃L�[���͂�ۑ�
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//���݁A�L�[��������Ă���Ƃ�
		if (KeyState[i] != 0) {
			//������Ă���t���[�������J�E���g�A�b�v
			NowKeyPressFrame[i]++;
		}
		else if (KeyState[i] == 0) {
			//������Ă��Ȃ��Ȃ�A�t���[�������[���N���A
			NowKeyPressFrame[i] = 0;
		}

	}

	return;
}

//����̃L�[����������
//�����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
bool KeyDown(int KEY_INPUT_)
{
	//���݉�����Ă���L�[�̃t���[������0������Ȃ�
	if (NowKeyPressFrame[KEY_INPUT_] > 0) {
		return true;		//������
	}

	return FALSE;			//�����ĂȂ�
}


//����̃L�[����������
//�����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
//�����F�u�L�[���������L�[���グ��v���Z�b�g�ōs��ꂽ�����A�N���b�N
bool KeyClick(int KEY_INPUT_)
{
	//���݃L�[�͉�����Ă���
	//�ЂƂO�̃L�[�͉�����Ă��Ȃ�
	if (NowKeyPressFrame[KEY_INPUT_] == 1			//�������āA
		&& OldKeyPressFrame[KEY_INPUT_] == 0) {		//���̐��O�͉����ĂȂ�
		return true;		//������
	}

	return FALSE;			//�����ĂȂ�
}

//����̃L�[���������t���[����
//�����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
//�߂�l�̓t���[����
int KeyPressFrame(int KEY_INPUT_)
{
	return NowKeyPressFrame[KEY_INPUT_];
}

//����̃L�[�������܂ł��̉�ʂő҂�
void WaitInputKey(int KEY_INPUT_)
{
	while (true) {
		if (ProcessMessage() != 0) {
			break;
		}
		if (CheckHitKey(KEY_INPUT_) == true) break;
	}
}