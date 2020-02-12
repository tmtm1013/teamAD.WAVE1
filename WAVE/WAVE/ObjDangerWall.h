
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�G
class CObjDangerWall :public CObj
{
public:CObjDangerWall() {};
	   ~CObjDangerWall() {};
	   void Init();   //�C�j�V�����C�Y
	   void Action(); //�A�N�V����
	   void Draw();   //�h���[

	   float GetEX();//�ʒu��񂘎擾�p
	   float GetEY();//�ʒu���Y�擾�p
	   void SetXX(float x);//�ʒu���X�ύX�p
	   void SetYY(float y);//�ʒu���Y�ύX�p


private:
	float m_px;    //�I�u�W�F�N�g�̈ʒu
	float m_py;

	float m_vx;    //�ړ��x�N�g��
	float m_vy;

	int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame; //�`��t���[��
	int m_ani_move;

	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l

	//�ړ��̌�������p
	bool m_move;

	float m_f;

	int m_ani;//���e�A�j���[�V�����p
	int m_ani_time2;//�G�t�F�N�g�A�j���[�V�����p�Ԋu�p�^�C��
	bool m_del;//�����`�F�b�N
	RECT_F m_eff;//���e�G�t�F�N�g�`��p

	
};
