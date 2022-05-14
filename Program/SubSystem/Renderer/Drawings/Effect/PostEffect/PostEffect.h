/**
* @file    PostEffect.h
* @brief   �|�X�g�G�t�F�N�g���ۃN���X
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
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