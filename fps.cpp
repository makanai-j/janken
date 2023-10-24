//fps�����̃\�[�X�t�@�C��

//�w�b�_�t�@�C��
#include "fps.h"

//�O���[�o���ϐ�
FPS fps;

//������
void FPSInit(void)
{
	//windows���N�����Ă���̎��ԁi�}�C�N���b�j
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//	�ق��̒l��������
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.Deltatime = 0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return;
}

//�v��
void FPSCheck(void)
{
	//���݂̎������擾
	fps.NowTakeTime = GetNowHiPerformanceCount();

	//�f���^�^�C�����v��
	fps.Deltatime = (fps.NowTakeTime - fps.OldTakeTime) / MICROSECOND;

	//���݂̎�����ۑ�
	fps.OldTakeTime = fps.NowTakeTime;

	//���݂�MAX�t���[���ڂȂ�
	if (fps.FrameCount == GAMEFPS) {
		//�P�t���[���ځ`MAX�t���[���ڂ܂ł̍��v���Ԃ��p��
		float TotalFrameTime = fps.NowTakeTime - fps.FirstTakeTime;

		//���v���Ԃ𗝑z��fps�l�Ŋ����ĕ��ς��v��
		float CalcAverage = TotalFrameTime / GAMEFPS;

		//1�b������̃t���[�����ɕϊ�
		fps.Average = MICROSECOND / CalcAverage;

		//1�t���[���ڂ̎������擾
		fps.FirstTakeTime = GetNowHiPerformanceCount();

		//�t���[������1�ɖ߂�
		fps.FrameCount = 1;
	}
	else {
		//�t���[�������J�E���g�A�b�v
		fps.FrameCount++;
	}

	return;
}

//�`��
void FPSDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "fps:%3.1f", fps.Average);
	
	return;
}

//�ҋ@
void FPSWait(void)
{
	//�����������ɑҋ@����~���b
	int wait = 0;

	//�҂����Ԃ��v��
	wait =
		MICROSECOND / GAMEFPS * fps.FrameCount		//���z�̎���
		- (fps.NowTakeTime - fps.FirstTakeTime);	//���ۂ̎���

	//�}�C�N���b���~���b�ɕϊ�
	wait /= MILISECOND;

	//�҂����Ԃ�����Ȃ��
	if (wait > 0 && wait <= WAITTIMEMILL) {
		//�u���b�Z�[�W�v���������Ȃ���҂�
		WaitTimer(wait);
	}

	return;
}