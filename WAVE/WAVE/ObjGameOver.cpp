//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "SceneMain.h"
#include "ObjTitle.h"
#include "GameHead.h"
#include "ObjGameOver.h"

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
	if (m_mou_x > 300 && m_mou_x < 460 && m_mou_y>260 && m_mou_y < 310)
	{
		//�}�E�X�̃{�^���������ꂽ�烊�X�^�[�g
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneMain());

		}
	}

	//�}�E�X�̈ʒu�ƃN���b�N����ꏊ�œ����蔻��
	if (m_mou_x > 230 && m_mou_x < 450 && m_mou_y>330 && m_mou_y < 350)
	{

		//�}�E�X�̃{�^���������ꂽ��^�C�g�����
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneTitle());

		}
	}






	/*
	if (Input::GetMouButtonL() == true)
	{
		Scene::SetScene()
	}*/
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


}