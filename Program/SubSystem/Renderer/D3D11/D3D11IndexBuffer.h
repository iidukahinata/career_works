/**
* @file    D3D11IndexBuffer.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"

class D3D11IndexBuffer : public D3D11DeviceChild
{
public:

	/** 
	* @param indices [����] �����C���f�b�N�X�f�[�^
	* @param usage [����] D3D11_USAGE_DYNAMIC �ȊO�̒l�̏ꍇ�� D3D11_USAGE_DEFAULT �ɂȂ�܂��B
	*/
	bool Create(const std::vector<UINT>& indices, D3D11_USAGE usage = D3D11_USAGE_DEFAULT) noexcept;

	/** GPU �f�[�^���X�V���܂��B */
	void Update(const std::vector<UINT>& indices) noexcept;

	/** DXGI_FORMAT_R32_UINT �Ńf�o�C�X�ݒ肳��܂��B*/
	void IASet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};