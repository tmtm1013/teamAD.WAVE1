#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:���C��
class CSceneBlock3 :public CScene
{
public:CSceneBlock3();
	   ~CSceneBlock3();
	   void InitScene();//���������\�b�h
	   void Scene();    //���s�����\�b�h
private:
	int m_time;//�G�̕\���p�^�C��
	int m_time2;//�G�̕\���^�C��
	int m_time3;
	int m_time4;
	int m_time5;
	int m_time6;
	int m_time7;
	int m_time8;
	int m_time9;
	int m_time10;



	int Enemy;//�ʏ�G�̐��p�ϐ�
	int Enemyleft;//�ʏ�E�G�̐��p�ϐ�
	int EnemyJump;//�W�����v�p�̓G���p�ϐ�
	int EnemyJumpleft;//�W�����v�p�̓G�E�̐��p�ϐ�
	int EnemyRecovery;//��l���񕜗p�̓G�̐��p�ϐ�
	int EnemyRecoveryleft;//��l���񕜗p�̓G�̐��p�ϐ�
	int EnemyAmmunition;//�G�e�ۏ����p�G�ϐ�
	int EnemyAmmunitionleft;//�G�e�ۏ����E�p�G�ϐ�
	int EnemyLongdistance;//�������U���^�G�p�ϐ�
	int EnemyLongdistanceleft;//�������U���^�G�p�ϐ�
};

/*
if (movesecond >= 21 && m_hit_down == true)
{
	Audio::Start(8);
	movesecond = 0;
}

//�_���[�W�u���b�N
if (m_block_type == 5)
hp -= 0.5;


	}
	else if (Action_ani_flag != true)//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
	{
	m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
	m_ani_move = 0;//�Î~�A�j���[�V�����f�[�^���w��

	movesecond = 100;

	}
	if (m_hit_down == false)//�W�����v�A�j���[�V����
	{
		m_ani_move = 2;//�W�����v�A�j���[�V�����f�[�^���w��

		if (jumpsecond >= 10)
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			if (SE_flag == false)
				Audio::Start(10);//SE�Đ�(�~��)

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//������Block�ƐڐG���ɒ��n����炷
	{
		Audio::Stop(10);
		SE_flag = false;
		Audio::Start(9);
*/