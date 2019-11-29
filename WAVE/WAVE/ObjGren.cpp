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
	Hits::SetHitBox(this, m_x, m_y, 36, 36, ELEMENT_PLAYER, OBJ_GRENADE, 1);



}


//�C�j�V�����C�Y
void CObjGren::Init()
{
	m_vx = 2;
	m_vy = -17;

	flag = true;

	
	

}


//�A�N�V����
void CObjGren::Action()
{


	//�e�ۂɑ��x����
	m_vx += 1.0f;
	m_vy += 0.8f;

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
	if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
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



