#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�A�C�e��
class CObjGrenade :public CObj
{
public:
	CObjGrenade(float x,float y);
	~CObjGrenade() {};
	void Init();	 //�C�j�V�����C�Y
	void Action();	 //�A�N�V����
	void Draw();	 //�h���[
private:
	float  m_x;       //�e�ۂ�X�����̈ʒu�p�ϐ�
	float  m_y;       //�e�ۂ�Y�����̈ʒu�p�ϐ�
	float  m_vx;      //�e�ۂ�x�����̑��x�p�ϐ� 
	float  m_vy;      //�e�ۂ�Y�����̑��x�p�ϐ�

	int	   m_ani;	  //���e�A�j���[�V�����p
	int    m_ani_time;//���e�A�j���[�V�����Ԋu�^�C��
	bool   m_del;	  //�폜�`�F�b�N
	//RECT_F m_eff;	  //���e�G�t�F�N�g�`��p

	float bx;      //�e�ۂ� X �x�N�g���l���[�p�ϐ� 
	float by;      //�e�ۂ� Y �x�N�g���l���[�p�ϐ�

	float m_bx;    //�e�ۂ� X �����̈ʒu�p�ϐ�
	float m_by;    //�e�ۂ� Y �����̈ʒu�p�ϐ�

	bool flag;     //���ˊp�x����t���O

	bool W;//��
	bool H;//����

	float m_px;
	float m_py;

	float x, y;
	float vx, vy;

	float m_mou_bx;//�}�E�X�� X �����̈ʒu�p�ϐ�
	float m_mou_by;//�}�E�X�� Y �����̈ʒu�p�ϐ�

	float m_vv;
};
