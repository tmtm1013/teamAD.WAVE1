#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�A�C�e��
class CObjAitem :public CObj
{
public:
	CObjAitem(float x, float y);
	~CObjAitem() {};
	void Init();	 //�C�j�V�����C�Y
	void Action();	 //�A�N�V����
	void Draw();	 //�h���[
private:
	

	float m_vx;
	float m_vy;

	float m_sx;  //�摜�T�C�Y�p
	float m_sy;


	float m_ix;
	float m_iy;

	float  m_posture;


	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	bool flag;

	float top;
	float left;
	float right;
	float bottom;

	int m_block_type;

};
