#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjRevolutionBullet : public CObj
{
public:
	CObjRevolutionBullet(float x, float y);
	~CObjRevolutionBullet() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	float m_x;	//�I�u�W�F�N�g�̈ʒu
	float m_y;
	float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��
	float m_vy;

	float Angle;
	float R;
	float Cx, Cy;

	int second;

	float x;
	float y;
	short int pos;

	bool flag; //�e�ۃo�E���h����p�t���O

	float pl_x;//���݂̃v���C���[X�̈ʒu��ۑ��p�ϐ�
	float pl_y;//���݂̃v���C���[Y�̈ʒu��ۑ��p�ϐ�

	bool button;

	float m_r;  //�ړ�����p�x
	float m_speed;  //���x

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//�������Ă���block�̎�ނ��m�F�p
	int m_block_type;

};


