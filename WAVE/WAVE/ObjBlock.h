#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#include "GameL/DrawTexture.h"

//�I�u�W�F�N�g:�u���b�N&�w�i
class CObjBlock :public CObj
{

public:
	CObjBlock(int map[10][100]);
	~CObjBlock() {};
	void Init();
	void Action();
	void Draw();

	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
		float *x, float *y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//�u���b�N�Ƃ̓����蔻��
	void BlockHit(
		float x, float y, float vx, float vy,
		float *out_px, float *out_py, float*out_len
	);

	void BlockBulletHit(
		float *x, float *y, bool scroll_on, float *m_sx, float *m_sy,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//��l���ƕǂ̌�������
	bool HeroBlockCrossPoint(
		float x, float y, float vx, float vy,
		float *out_px, float *out_py, float*out_len
	);

private:
	void BlockDraw(float x, float y, RECT_F *dst, float c[]);

	int m_map[10][100];

	float m_scroll;

	float Dot(float ax, float ay, float bx, float by);
	float Cross(float ax, float ay, float bx, float by);

	//���Ɛ��ƌ�������
	bool LineCrossPoint(
		float a1x, float a1y, float a2x, float a2y,
		float b1x, float b1y, float b2x, float b2y,
		float*out_px, float*out_py
	);

};