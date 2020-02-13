#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�G
class CObjBoss :public CObj
{
public:
	CObjBoss(float x, float y);
	   ~CObjBoss() {};
	   void Init();   //�C�j�V�����C�Y
	   void Action(); //�A�N�V����
	   void Draw();   //�h���[

	   float GetEX();//�ʒu��񂘎擾�p
	   float GetEY();//�ʒu���Y�擾�p
	   void SetXX(float x);//�ʒu���X�ύX�p
	   void SetYY(float y);//�ʒu���Y�ύX�p


private:
	float m_px;    //�ʒu
	float m_py;
	float m_vx;    //�ړ��x�N�g��
	float m_vy;
	float m_posture;  //�p��

	int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame; //�`��t���[��
	int m_time_a;
	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l

	int Boss_hp_max;//ENEMY��HP
	int Boss_hp_now;

	//�ړ��̌�������p
	bool m_move;

	//ENEMY��HP
	int m_hp;

	//�e�ۗp�v���O����
	int m_time;
	int m_time2;
	
	//�}�b�v�ړ��p���l
	int kazu;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool m_attack;//�P���U���A�j���[�V�����t���O
	bool m_attack2;//�͈͍U���A�j���[�V�����t���O
	int m_ani_frame2;//�U���A�j���[�V�����p�^�C��
	float m_ani_max_time2; //�A�j���[�V��������Ԋu�ő�l
	float m_ani_max_time3; //�A�j���[�V��������Ԋu�ő�l
};