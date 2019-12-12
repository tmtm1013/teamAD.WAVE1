#pragma once
//使用するヘッダーファイル
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：クリア
class CSceneDescription :public CScene
{
public:
	CSceneDescription();
	~CSceneDescription();
	void InitScene();
	void Action();
	void Scene();
private:


};