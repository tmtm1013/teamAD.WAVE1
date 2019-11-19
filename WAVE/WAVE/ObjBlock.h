#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock :public CObj
{
public:
	CObjBlock(int map[30][30]) ;
	~CObjBlock() {};
	void Init();
	void Action();
	void Draw();

	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
		float *x, float *y,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);


private:
	int m_map[30][30];//�}�b�v���i���j

	float len;
	int r;
	float bx;
	float by;

};