#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "ObjLoading.h"
#include "GameHead.h"
#include "SceneMain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjLoading::Init()
{/*
	if (((UserData*)Save::GetData())->Scenecontinue == 0) {
		Draw::LoadImageW(L"village1.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 1) {
		Draw::LoadImageW(L"Background.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 2) {
		Draw::LoadImageW(L"stage2.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 3) {
		Draw::LoadImageW(L"hstage1.png", 37, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 4) {
		Draw::LoadImageW(L"hstage2.png", 37, TEX_SIZE_1024);
	}*/
}

//�A�N�V����
void CObjLoading::Action()
{


}

//�h���[
void CObjLoading::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 739.0f;
	src.m_bottom = 415.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(37, &src, &dst, c, 0.0f);
}