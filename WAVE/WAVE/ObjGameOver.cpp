//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL/Audio.h"

#include "SceneMain.h"
#include "ObjTitle.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
}

//�A�N�V����
void CObjGameOver::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonL();

	//�}�E�X�̈ʒu�ƃN���b�N����ꏊ�œ����蔻��
	if (m_mou_x > 205 && m_mou_x < 325 && m_mou_y>490 && m_mou_y < 525)
	{
		//�}�E�X�̃{�^���������ꂽ�烊�X�^�[�g
		if (m_mou_r == true)
		{
			if (((UserData*)Save::GetData())->Scenecontinue == 1)
			{
				Scene::SetScene(new CSceneMain());
				Audio::Stop(24); //BGM�X�g�b�v
			}
			else if(((UserData*)Save::GetData())->Scenecontinue == 2)
			{
				Scene::SetScene(new CSceneBlock2());
				Audio::Stop(24); //BGM�X�g�b�v
			}
			else if(((UserData*)Save::GetData())->Scenecontinue == 3)
			{
				Scene::SetScene(new CSceneBlock3());
				Audio::Stop(24); //BGM�X�g�b�v
			}
			else if (((UserData*)Save::GetData())->Scenecontinue == 4)
			{
				Scene::SetScene(new SceneBossStage());
				Audio::Stop(24); //BGM�X�g�b�v
			}
			

			
		}
	}

	//�}�E�X�̈ʒu�ƃN���b�N����ꏊ�œ����蔻��
	if (m_mou_x > 505 && m_mou_x < 590 && m_mou_y>490 && m_mou_y < 525)
	{

		//�}�E�X�̃{�^���������ꂽ��^�C�g�����
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneDescription());
			Audio::Stop(24); //BGM�X�g�b�v
		}
	}






	
	
}



//�h���[
void CObjGameOver::Draw()
{

	

	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
	Draw::Draw(11, &src, &dst, c, 0.0f);

	/*//���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x = %f, y = %f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
	//���}�E�X�̃{�^���̏��
	if (m_mou_r == true)
		Font::StrDraw(L"R=�����Ă���", 20, 30, 12, c);
	else
		Font::StrDraw(L"R=�����Ă��Ȃ�", 20, 30, 12, c);
	if (m_mou_l == true)
		Font::StrDraw(L"L=�����Ă���", 20, 40, 12, c);
	else
		Font::StrDraw(L"L=�����Ă��Ȃ�", 20, 40, 12, c);
		*/

}