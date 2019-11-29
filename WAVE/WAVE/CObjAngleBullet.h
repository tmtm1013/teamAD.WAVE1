#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FBOSS�g�U�e
class CObjAngleBullet : public CObj
{
public:
	CObjAngleBullet(float x, float y,float r,float speed);
	~CObjAngleBullet() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up ;
	bool m_hit_down ;
	bool m_hit_left ;
	bool m_hit_right ;

	//�������Ă���block�̎�ނ��m�F�p
	int m_block_type;


	float m_x;	//�I�u�W�F�N�g�̈ʒuX
	float m_y;  //�I�u�W�F�N�g�̈ʒuY
	float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y
	float m_sx; //�T�C�Y�p
	float m_sy;

	float m_r;  //�ړ�����p�x
	float m_speed;  //���x
	
};
