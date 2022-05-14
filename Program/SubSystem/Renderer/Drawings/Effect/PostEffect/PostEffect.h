/**
* @file    PostEffect.h
* @brief   ポストエフェクト抽象クラス
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Resource/Resources/3DModel/Texture.h"

class PostEffect
{
public:

	virtual bool Init(Texture* texture) = 0;

	virtual void Draw() = 0;

	virtual Texture* GetTexture() = 0;

	void SetPostprocessing(class Postprocessing* postprocessing) 
	{
		if (!m_postprocessing)
			m_postprocessing = postprocessing;
	}

protected:

	class Postprocessing* m_postprocessing = nullptr;
};