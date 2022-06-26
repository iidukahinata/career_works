/**
* @file    D3D11Texture.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

class D3D11Texture : public D3D11DeviceChild
{
public:

	/**
	* @param images [����] �C���[�W�z��̐擪�|�C���^���w�肵�Ă��������B
	* @param imageSize [����] �C���[�W�z��T�C�Y���w�肵�Ă��������B
	* @param meta [����] �ǂݍ��܂ꂽ�e�N�X�`�� meta �f�[�^���w�肵�Ă��������B
	*/
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta);

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void PSSet(UINT slot = 0) const noexcept;

	void SetShaderResourceView(ID3D11ShaderResourceView* shaderResourceView) noexcept;

	/* �A�N�Z�X */
	ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;
	ID3D11ShaderResourceView** GetAddressOfShaderResourceView() noexcept;

private:
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
};