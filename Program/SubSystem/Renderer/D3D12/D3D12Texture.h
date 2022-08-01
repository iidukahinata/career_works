/**
* @file    D3D12Texture.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include "D3D12View.h"
#include "D3D12Buffer.h"
#include "../directxtex/include/DirectXTex.h"

class D3D12Texture : public D3D12Buffer
{
public:

	bool Create(DXGI_FORMAT format, UINT width) noexcept;
	bool Create(DXGI_FORMAT format, UINT width, UINT height) noexcept;
	bool Create(DXGI_FORMAT format, UINT width, UINT height, UINT depth) noexcept;
	bool Create(const D3D12_RESOURCE_DESC* desc) noexcept;

	/**
	* @param images [����] �C���[�W�z��̐擪�|�C���^���w�肵�Ă��������B
	* @param imageSize [����] �C���[�W�z��T�C�Y���w�肵�Ă��������B
	* @param meta [����] �ǂݍ��܂ꂽ�e�N�X�`�� meta �f�[�^���w�肵�Ă��������B
	*/
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta) noexcept;

	void VSSet(UINT slot = 0) noexcept;
	void PSSet(UINT slot = 0) noexcept;
	void GSSet(UINT slot = 0) noexcept;

	/** �A�N�Z�X */
	D3D12ShaderResourceView& GetView() noexcept { return m_view; }

private:

	D3D12ShaderResourceView m_view;
};