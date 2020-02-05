#include "GameHead.h"
#include <math.h>  //���w�v�Z�w�b�_�[
#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//---UnitVec�֐�
//�����P�@float* vx :�x�N�g����X�����̃|�C���^
//�����Q�@float* vy :�x�N�g����Y�����̃|�C���^
//�߂�l�@bool      :trur=�v�Z�����@flase=�v�Z���s
//���e
//�����̃x�N�g���𐳋K�����A���̒l��vx,vy�ɕύX���܂��B
bool UnitVec(float* vx, float * vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
	float r = 0.0f;
	r = (*vx) * (*vx) + (*vy) * (*vy);

	r = sqrt(r);

	//�������O���ǂ������ׂ�
	if (r == 0.0f)
	{
		;//�O�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K�����s��
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);
	}

	//�v�Z����
	return true;
}

//---CheckWindow�֐�
//����1 float pos_x    :�̈�O���ǂ������ׂ邘�ʒu
//����2 float pos_y    :�̈�O���ǂ������ׂ邙�ʒu
//����3 float window_x :�̈��top�ʒu
//����4 float window_y :�̈��left�ʒu
//����5 float window_w :�̈��right�ʒu
//����6 float window_h :�̈��bottom�ʒu
//�߂�l bool       :true=�̈��  flase=�̈�O
//���e
//�̈�����ǂ������ׂ�ʒupos_(x,y)��window_(xywh)�̓����O���𒲂ׂ�

bool CheckWindow(float pos_x, float pos_y, float window_x, float window_y, float window_w, float window_h)
{
	//�̈�`�F�b�N
	if (pos_x < window_x)
	{
		return false;   //�̈�O
	}
	if (pos_x > window_w)
	{
		return false;   //�̈�O
	}
	if (pos_y < window_y)
	{
		return false;   //�̈�O
	}
	if (pos_y > window_h)
	{
		return false;   //�̈�O
	}
	return true;       //�̈��
}

//---GetAtan2Angle�֐�
//�����P float w        :��
//�����Q float h        :����
//�߂�l float          :�p�x(0���`360��)
//���e
//�����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�B
float GetAtan2Angle(float w, float h)
{
	//atan2�Ŋp�x�����߂�
	float r = atan2(h, w)*180.0f / 3.14;

	//-180���`-0����180���`360���ɕϊ�
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}


//int* m_ani_time      �A�j���[�V�����`��^�C����ۑ��p
//int* m_ani_max_time  �A�j���[�V�����`��܂ł̒l���w��p
//int* m_ani_frame     �A�j���[�V�����t���[����i�߂邽�߂̒l���w��p
//float* m_posture     �`��̌������w��p    0.0=�E  1.0=��

//int ani_time        �A�j���[�V�����`��^�C�������Z����l
//int ani_frame       �A�j���[�V�����t���[���̐��̎w��
//float posture       �`��̌������w��
void Anime(int* m_ani_time, float* m_ani_max_time, int* m_ani_frame, float* m_posture,
	int ani_time, int ani_frame, float posture)
{
	*m_ani_time += ani_time;

	if (*m_ani_time > *m_ani_max_time)//���������������� 1 �t���[���i��
	{
		*m_ani_frame +=1;
		*m_ani_time = 0;
	}
	//�A�j���[�V����
	if (*m_ani_frame == ani_frame)
	{
		*m_ani_frame = 0;

	}

	//�A�j���[�V���������ύX
	*m_posture = posture;
}

//�m�b�N�o�b�N�v���O����
//��l����X��       : m_px
//�I�u�W�F�N�g��X�� : ex
float KnockBack(float m_px, float ex)
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_px > ex + block->GetScroll())//�X�N���[���l���Z
	{
		return 5.0f;
	}
	else
	{
		return -5.0f;
	}
}


//CheckHit�֐��̒�`
//float m_x = �I�u�W�F�N�gA�� X ���W
//float m_y = �I�u�W�F�N�gA�� Y ���W

//float e_x = �I�u�W�F�N�gB�� X ���W
//float e_y = �I�u�W�F�N�gB�� Y ���W

bool CheckHit(float m_x, float m_y, float e_x, float e_y)
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	if (
		//�I�u�W�F�N�g�ƃI�u�W�F�N�g��X���̓����蔻��
		e_x - block->GetScroll() <= m_x + 100.0 && m_x <= e_x - block->GetScroll() + 100.0

		&&

		//�I�u�W�F�N�g�ƃI�u�W�F�N�g��Y���̓����蔻��
		m_y <= e_y + 500.0&& e_y <= m_y + 100.0)
	{
		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else
	{
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
	}
}

