#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:��l��
class CObjWeaponType :public CObj
{
public:
	CObjWeaponType(int type);
	~CObjWeaponType() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	short int weapontype;
	
};

