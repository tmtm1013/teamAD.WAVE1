//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjMethod.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMethod::Init()
{

	flag = false; //���̏����Ɉڍs���Ȃ��t���O

}
//�A�N�V����
void CObjMethod::Action()
{

	if (flag == true)//���̏����Ɉڍs���Ȃ�����
		while (1) {//���̏����Ɉڍs���Ȃ����߂̖������[�v
		
			
			if (Input::GetVKey('Q') == true) {//�}�E�X�� ���������Ɛ^

				flag = false;//�������~�߂�t���O��؂�ւ���

			}
			if (Input::GetVKey('Q') == false && flag == false)
			{
				this->SetStatus(false);//��������폜

				break;//���[�v�𔲂���
			}
		}

}
//�h���[
void CObjMethod::Draw()
{
	
	flag = true;//�摜��\��������A���̏����Ɉڍs���Ȃ��t���O��^�ɂ���

	//���_��`��F�E��
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"Q�L�[�ŃQ�[���ɖ߂�");
	Font::StrDraw(str, 450, 400, 20, cc);

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 470.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 500.0f;


	//�`��
	Draw::Draw(38, &src, &dst, c, 0.0f);

	
}




