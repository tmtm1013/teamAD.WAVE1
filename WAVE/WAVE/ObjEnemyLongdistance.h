
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�I�u�W�F�N�g�F�G
class CObjEnemyLongdistance :public CObj
{
public:CObjEnemyLongdistance(float x,float y) ;
	   ~CObjEnemyLongdistance() {};
	   void Init();   //�C�j�V�����C�Y
	   void Action(); //�A�N�V����
	   void Draw();   //�h���[

private:
	float m_px;    //�ʒu
	float m_py;
	float m_vx;    //�ړ��x�N�g��
	float m_vy;
	float m_posture;  //�p��

	float m_sx;  //�摜�T�C�Y��BlockHit�ɓn���p
	float m_sy;


	int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame; //�`��t���[��

	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l
	int m_ani_move; //���[�V������ސ���


	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//�ړ��̌�������p
	bool m_move;

	//ENEMY��HP
	int m_hp;

	//�e�ۗp���Ԑ����^�C���ϐ�
	int m_time;


};