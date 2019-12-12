#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�A�C�e��
class CObjGren :public CObj
{
public:
	CObjGren(float x, float y);
	~CObjGren() {};
	void Init();	 //�C�j�V�����C�Y
	void Action();	 //�A�N�V����
	void Draw();	 //�h���[
private:
	float  m_x;       //�e�ۂ�X�����̈ʒu�p�ϐ�
	float  m_y;       //�e�ۂ�Y�����̈ʒu�p�ϐ�
	float  m_vx;      //�e�ۂ�x�����̑��x�p�ϐ� 
	float  m_vy;      //�e�ۂ�Y�����̑��x�p�ϐ�

	float bx;      //�e�ۂ� X �x�N�g���l���[�p�ϐ� 
	float by;      //�e�ۂ� Y �x�N�g���l���[�p�ϐ�

	float m_bx;    //�e�ۂ� X �����̈ʒu�p�ϐ�
	float m_by;    //�e�ۂ� Y �����̈ʒu�p�ϐ�

	float flag;

	float m_mou_by;
	float m_mou_bx;

	float x, y;
	float vx, vy;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	int m_block_type; //�u���b�N�̎��

};
