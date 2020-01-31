#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�G
class CObjIcicle :public CObj
{
public:CObjIcicle(float x, float y);
	   ~CObjIcicle() {};
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
	int m_ani_move;

	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l


	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	int m_block_type;

	//��l���Ƃ̓����蔻��p�t���O
	bool HitCheck;

	//�ړ��̌�������p
	bool m_move;



	//�A�C�e���t���O
	bool flag;


	//ENEMY��HP
	int m_hp;


	float m_f;

};
