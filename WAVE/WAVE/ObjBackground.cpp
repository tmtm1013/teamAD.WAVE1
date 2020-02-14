#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "SceneMain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackground::Init()
{
	if (((UserData*)Save::GetData())->Scenecontinue == 0) {
		Draw::LoadImageW(L"BackGround/village1.png", 9, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 1) {
		Draw::LoadImageW(L"BackGround/Background.png", 9, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 2) {
		Draw::LoadImageW(L"BackGround/stage2.png", 9, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 3) {
		Draw::LoadImageW(L"BackGround/hstage1.png", 9, TEX_SIZE_1024);

	}
	if (((UserData*)Save::GetData())->Scenecontinue == 4) {
		Draw::LoadImageW(L"BackGround/gc1.png", 9, TEX_SIZE_1024);
		backnum = 9;
	}
}

//�A�N�V����
void CObjBackground::Action()
{


}

//�h���[
void CObjBackground::Draw()
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
	Draw::Draw(9, &src, &dst, c, 0.0f);
}