#pragma once
//使用するヘッダーファイル
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：クリア
class CSceneItem :public CScene
{
public:
	CSceneItem();
	~CSceneItem();
	void InitScene();
	void Scene();
private:
	

};