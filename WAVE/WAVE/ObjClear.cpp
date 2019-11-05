// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClear::Init()
{
	m_Key_flag = false;//�L�[�t���O
}
//�A�N�V����
void CObjClear::Action()
{
	//�G���^�[�L�[�������ăV�[���F�Q�[��Title�Ɉڍs����
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_Key_flag == true)
		{
			Scene::SetScene(new CSceneTitle());
			m_Key_flag = false;

		}
	}
	else
	{
		m_Key_flag = true;

	}

	

	
}

//�h���[
void CObjClear::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	/*//�X�R�A
	Font::StrDraw(L"score", 200, 250, 30, c);
	for (int i = 0; i < 15; i++)
	{

	}*/


	Font::StrDraw(L"GameClear", 250, 100, 70, c);

	//�^�C�g���ɖ߂�L�[
	Font::StrDraw(L"Enter to title",220,500,50, c);

}