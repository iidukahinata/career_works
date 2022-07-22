/**
* @file    D3D12Texture.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

class D3D12Texture : public D3D12DeviceChild
{
public:

	/**
	* @param images [����] �C���[�W�z��̐擪�|�C���^���w�肵�Ă��������B
	* @param imageSize [����] �C���[�W�z��T�C�Y���w�肵�Ă��������B
	* @param meta [����] �ǂݍ��܂ꂽ�e�N�X�`�� meta �f�[�^���w�肵�Ă��������B
	*/
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta);
	
	void SetResource(ID3D12Resource* resource);

	/* �A�N�Z�X */
	ID3D12Resource* GetResource()	  const noexcept { return m_texture.Get(); }
	ID3D12Resource** GetAddressOfResource() noexcept { return m_texture.GetAddressOf(); }

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
};