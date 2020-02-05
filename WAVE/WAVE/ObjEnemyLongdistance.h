
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�I�u�W�F�N�g�F�G
class CObjEnemyLongdistance :public CObj
{
public:CObjEnemyLongdistance(float x, float y);
	   ~CObjEnemyLongdistance() {};
	   void Init();   //�C�j�V�����C�Y
	   void Action(); //�A�N�V����
	   void Draw();   //�h���[]


	   float GetEX();//�ʒu��񂘎擾�p
	   float GetEY();//�ʒu���Y�擾�p
	   void SetXX(float x);//�ʒu���X�ύX�p
	   void SetYY(float y);//�ʒu���Y�ύX�p


private:
	float m_px;    //�ʒu
	float m_py;
	float m_vx;    //�ړ��x�N�g��
	float m_vy;
	float ScrollEnemy;//�G�̈ʒu���ɃX�N���[���̉e����^���邽�ߍ�����ϐ��B
	float Scrollplayer;

	float m_posture;  //�p��

	float m_sx;  //�摜�T�C�Y��BlockHit�ɓn���p
	float m_sy;


	int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame; //�`��t���[��

	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l



	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//�ړ��̌�������p
	bool m_move;
	bool elevator_flag;

	//ENEMY��HP
	int m_hp;

	//�e�ۗp���Ԑ����^�C���ϐ�
	int m_time;

	float flag;

	bool m_attack;//�U���A�j���[�V�����t���O
	int m_ani_frame2;//�U���A�j���[�V�����p�^�C��
	float m_ani_max_time2; //�A�j���[�V��������Ԋu�ő�l



	int m_ani;//���e�A�j���[�V�����p
	int m_ani_time2;//�G�t�F�N�g�A�j���[�V�����p�Ԋu�p�^�C��
	bool m_del;//�����`�F�b�N
	RECT_F m_eff;//���e�G�t�F�N�g�`��p


};