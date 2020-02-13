/*#pragma once
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

};*/

#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjDiffusionBullet : public CObj
{
public:
	CObjDiffusionBullet(float x, float y, float r);
	~CObjDiffusionBullet() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	float m_bx;//�I�u�W�F�N�g�̈ʒu
	float m_by;
	float m_vx;//X�x�N�g���ۑ��p�ϐ�
	float m_vy;//Y�x�N�g���ۑ��p�ϐ�
	float m_r; //�p�x�ۑ��p�ϐ�
	float m_s; //�e�X�s�[�h�p�ϐ�

	float m_sx, m_sy;

	int m_time;

	float x;
	float y;

	//�u���b�N�Ƃ̓����蔻��p�t���O
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//�������Ă���block�̎�ނ��m�F�p
	int m_block_type;


	bool flag; //�e�ۃo�E���h����p�t���O

	float pl_x;//���݂̃v���C���[X�̈ʒu��ۑ��p�ϐ�
	float pl_y;//���݂̃v���C���[Y�̈ʒu��ۑ��p�ϐ�

	float m_bxp;

	bool button;
};
