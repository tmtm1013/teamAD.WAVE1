#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�O���l�[�h
class CObjGre : public CObj
{
public :
	CObjGre(float x, float y);
	~CObjGre() {};
	void Init();
	void Action();
	void Draw();
	
private :
	float m_vx; //���x�ϐ�
	float m_vy;

	int m_bx; //�ʒu�ϐ�
	int m_by;

	float m_x; //�e�ۂ�X�����̈ʒu�p�ϐ�
	float m_y; //�e�ۂ�Y�����̈ʒu�p�ϐ�

	float vx; //�x�N�g����X����
	float vy; //�x�N�g����Y����

	float x;
	float y;

	bool flag;


	int	   m_ani;	  //���e�A�j���[�V�����p
	int    m_ani_time;//���e�A�j���[�V�����Ԋu�^�C��
	bool   m_del;	  //�폜�`�F�b�N
};