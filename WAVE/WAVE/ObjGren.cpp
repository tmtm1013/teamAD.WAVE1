// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "ObjGren.h"
#include "CObjBullet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGren::CObjGren(float x, float y)
{

	m_bx = x;
	m_by = y;

	//�����蔻��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 36, 36, ELEMENT_PLAYER, OBJ_GREN, 1);



}


//�C�j�V�����C�Y
void CObjGren::Init()
{
	m_vx = 0;
	m_vy = -17;

	flag = true;

	
	

}


//�A�N�V����
void CObjGren::Action()
{
	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true, &m_bx, &m_by,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);



	m_mou_bx = (float)Input::GetPosX();

	if (m_mou_bx < m_bx)
	{
		m_vx -= 0.6f;
	}
	else
	{
		m_vx += 0.6f;
	}

	//�e�ۂɑ��x����
	m_vy += 1.0f;

	//�ړ��x�N�g�������W�ɉ��Z����

	m_bx += m_vx;
	m_by += m_vy;


	
	//���R�����^��
	//m_by += 9.8 / (16.0f);

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);


	//�G�@�I�u�W�F�N�g�ƐڐG������e�ۏ���
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}
	//�u���b�N�ɐڐG������e�ۍ폜
	/*if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}*/
	
	if (m_hit_up==true|| m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}
	
	
	//�̈�O�ɏo����e�ۂ�j������
	if (m_bx > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_bx < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_by < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_by > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

	//m_vx -= 0.1f;

	//m_x += m_vx;




}


//�h���[
void CObjGren::Draw()
{

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;




	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 36.0f + m_bx;
	dst.m_bottom = 36.0f + m_by;


	//�`��
	Draw::Draw(8, &src, &dst, c, 0.0f);


}



