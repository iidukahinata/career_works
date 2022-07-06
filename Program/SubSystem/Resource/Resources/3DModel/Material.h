/**
* @file    Material.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "../IResource.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

class Texture;

class Material : public IResource
{
	SUB_CLASS(Material)
public:

	Material();

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B*/
	void SaveToFile(String_View filePath) override;

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
	bool LoadFromFile(String_View filePath) override;

	void AddTexture(Texture* texture) noexcept;

	/** �e�V�F�[�_�[�ݒ�̕ύX�B*/
	void SetVSShader(String_View name);
	void SetPSShader(String_View name);

	void ShaderSet() noexcept;

protected:

	bool Do_Load(String_View filePath) override { return true; };

	String ConvertProprietaryFormat(String_View filePath) const noexcept;

private:

	Vector<Texture*> m_textures;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};