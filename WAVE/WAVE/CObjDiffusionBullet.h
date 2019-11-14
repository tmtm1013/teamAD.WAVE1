#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�g�U�e
class CObjDiffusionBullet :public CObj
{
public:
	CObjDiffusionBullet(float x, float y);  //�R���X�g���N�^
	~CObjDiffusionBullet() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	float m_bx;    //�e�ۂ� X �����̈ʒu�p�ϐ�
	float m_by;    //�e�ۂ� Y �����̈ʒu�p�ϐ�
	float m_vx;    //�e�ۂ� X �����̑��x�p�ϐ�
	float m_vy;    //�e�ۂ� Y �����̑��x�p�ϐ�

	float bx;      //�e�ۂ� X �x�N�g���l���[�p�ϐ� 
	float by;      //�e�ۂ� Y �x�N�g���l���[�p�ϐ�

	float m_time;  //�e�ۂ̎˒������̐���

	bool flag;     //���ˊp�x����t���O

	float m_mou_bx;//�}�E�X�� X �����̈ʒu�p�ϐ�
	float m_mou_by;//�}�E�X�� Y �����̈ʒu�p�ϐ�

};

