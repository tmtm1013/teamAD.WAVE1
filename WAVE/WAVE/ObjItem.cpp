// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



//�C�j�V�����C�Y
void CObjItem::Init()
{
	
	
	

}


//�A�N�V����
void CObjItem::Action()
{
	

	

	
}


//�h���[
void CObjItem::Draw()
{

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 64.0f;
	dst.m_bottom = 64.0f;


	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);


	//Draw::LoadImage(L"Item.png", 0, TEX_SIZE_512);

	//Draw::LoadImage(L"dannyaku.png", 0, TEX_SIZE_512);

	CObjItem*obju = new CObjItem();
	Objs::InsertObj(obju, OBJ_ITEM, 4);

}