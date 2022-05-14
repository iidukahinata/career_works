/**
* @file    ID3D11InputLayout.h
* @brief
*
* @date	   2022/04/29 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <wrl/client.h>
#include "D3D11DeviceChild.h"

class D3D11InputLayout : public D3D11DeviceChild
{
public:

	/**
	* @param layout [����] ���C�A�E�g�z��̐擪�|�C���^���w�肵�Ă��������B
	* @param layoutSize [����] ���C�A�E�g�z��T�C�Y���w�肵�Ă��������B
	* @param blobs [����] ���_�V�F�[�_�[�̃R���p�C���f�[�^���w�肵�Ă��������B
	*/
	bool Create(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3DBlob* blob) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void IASet() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};