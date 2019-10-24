#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "CObjBullet.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBullet::CObjBullet(float x, float y)
{
	m_px = x;
	m_py = y;
	
}


//�C�j�V�����C�Y
void CObjBullet::Init()
{
	m_vx = 0.0f;
}

//�A�N�V����
void CObjBullet::Action()
{
	m_vx += 1.0f;

	m_px += m_vx;

	//�̈�O�ɏo����e�ۂ�j������
	if (m_px>800.0f)
	{
		this->SetStatus(false);
	}

}

//�h���[
void CObjBullet::Draw()
{
	/*//�����A�j���[�V��������o�^
	int AniData[4] =
	{
		1 , 0 , 2 , 0,
	};w
	*/

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 64.0f;
	src.m_left   = 256.0f;
	src.m_right  = 320.0f;
	src.m_bottom = 128.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top    = 0.0f  + m_py;
	dst.m_left   = 0.0f  + m_px;
	dst.m_right  = 16.0f + m_px;
	dst.m_bottom = 16.0f + m_py;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
	
}