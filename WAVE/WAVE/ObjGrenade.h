#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjGrenade: public CObj
{
public:
	CObjGrenade(float x, float y);
	~CObjGrenade() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	float m_x;	//�I�u�W�F�N�g�̈ʒu
	float m_y;
	float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��
	float m_vy;
	float leng;

	float m_sx ;  //�摜�T�C�YBlockHit�֐��ɓn���p
	float m_sy ;

	float x;
	float y;

	bool flag; //�e�ۃo�E���h����p�t���O

	float pl_x;//���݂̃v���C���[X�̈ʒu��ۑ��p�ϐ�
	float pl_y;//���݂̃v���C���[Y�̈ʒu��ۑ��p�ϐ�


	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;


	//�������Ă���block�̎�ނ��m�F�p
	int m_block_type;

	bool HitCheck;//���茋�ʕۑ��p�ϐ�

	bool button;
};

