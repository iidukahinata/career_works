/**
* @file    D3D11Shader.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
* @note
*						 D3D11Shader
*						   	 ��
*		   -----------------------------------------
*	      ��	                 ��					   ��
*	D3D11VertexShader	D3D11PixelShader	D3D11ComputeShader
*/
#pragma once


#include "D3D11DeviceChild.h"

/**	�e�V�F�[�_�[�I�u�W�F�N�g���ۃN���X */
class D3D11Shader : public D3D11DeviceChild
{
public:

	/**
	* �w��V�F�[�_�[�̃R���p�C�����s��
	* @param shader [����] �R���p�C�����s���V�F�[�_�[�t�@�C����
	* @param entrypoint [����] �w��V�F�[�_�[�̊J�n�ʒu
	* @param traget [����] �V�F�[�_�[��ނ��w��
	*/
	bool CompileFromFile(StringView shader, D3D_SHADER_MACRO* macro, StringView entrypoint, StringView traget) noexcept;

	/** �A�N�Z�X */
	ID3DBlob* GetBlob() const noexcept;

protected:

	// * �R���p�C�������V�F�[�_�[�f�[�^��ێ�������
	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};

class D3D11VertexShader : public D3D11Shader
{
public:

	/**
	* @param shader [����] ��������̕�����ł���K�v������܂��B
	* @param entrypoint [����] ��������̕�����ł���K�v������܂��B
	* @param traget [����] ��������̕�����ł���K�v������܂��B
	*/
	bool Create(StringView shader, D3D_SHADER_MACRO* macro = nullptr, StringView entrypoint = "main", StringView target = "vs_5_0") noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void VSSet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
};

class D3D11PixelShader : public D3D11Shader
{
public:

	/**
	* @param shader [����] ��������̕�����ł���K�v������܂��B
	* @param entrypoint [����] ��������̕�����ł���K�v������܂��B
	* @param traget [����] ��������̕�����ł���K�v������܂��B
	*/
	bool Create(StringView shader, D3D_SHADER_MACRO* macro = nullptr, StringView entrypoint = "main", StringView target = "ps_5_0") noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void PSSet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
};

class D3D11ComputeShader : public D3D11Shader
{
public:

	/**
	* @param shader [����] ��������̕�����ł���K�v������܂��B
	* @param entrypoint [����] ��������̕�����ł���K�v������܂��B
	* @param traget [����] ��������̕�����ł���K�v������܂��B
	*/
	bool Create(StringView shader, D3D_SHADER_MACRO* macro = nullptr, StringView entrypoint = "main", StringView target = "cs_5_0") noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader;
};

class D3D11GeometryShader : public D3D11Shader
{
public:

	/**
	* @param shader [����] ��������̕�����ł���K�v������܂��B
	* @param entrypoint [����] ��������̕�����ł���K�v������܂��B
	* @param traget [����] ��������̕�����ł���K�v������܂��B
	*/
	bool Create(StringView shader, D3D_SHADER_MACRO* macro = nullptr, StringView entrypoint = "main", StringView target = "gs_5_0") noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
};