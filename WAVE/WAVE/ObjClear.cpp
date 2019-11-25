// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"

#include "GameL\UserData.h"
#include "GameHead.h"
#include "ObjClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClear::Init()
{
	
}
//�A�N�V����
void CObjClear::Action()
{
	//�G���^�[�L�[�������ăV�[���F�Q�[��Title�Ɉڍs����
	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}

//�h���[
void CObjClear::Draw()
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
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//���_��`��F�E��
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"���_ : %d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 650, 10, 20, cc);



	/*//�X�R�A
	Font::StrDraw(L"score", 200, 250, 30, c);
	for (int i = 0; i < 15; i++)
	{

	}*/
	Draw::LoadImage(L"Clear1.png", 0, TEX_SIZE_512);

	/*CObjClear*objr = new CObjClear();
	Objs::InsertObj(objr, OBJ_CLEAR, 2);
	*/

	/*Font::StrDraw(L"GameClear", 250, 100, 70, c);

	//�^�C�g���ɖ߂�L�[
	Font::StrDraw(L"Enter to title",220,500,50, c);
	*/

}