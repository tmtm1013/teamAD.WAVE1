#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

using namespace GameL;

//シーンゲームタイトル
class Ctitle:public CScene
{
public:
	Ctitle();
	~Ctitle();
	void InitScene();
	void Scene();
private:
};