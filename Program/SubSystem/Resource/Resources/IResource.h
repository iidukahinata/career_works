/**
* @file    IResource.h
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/06/29 2022�N�x����
*/
#pragma once


#include <string_view>
#include "SubSystem/Core/Context.h"

class RefCounter
{
public:
	void AddRef() noexcept { ++m_referenceCount; }
	void Release() noexcept { --m_referenceCount; }
	size_t GetRef() const noexcept { return m_referenceCount; }

private:

	// * �Q�ƃJ�E���g�ŉ�������s�����߂̕ϐ��B�h����ł͂Ȃ��g�p�ґ��ŃJ�E���g����K�v������B
	size_t m_referenceCount = 0;
};

class IResource : public RefCounter
{
public:

	virtual ~IResource() {}

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B*/
	virtual void SaveToFile(std::string_view filePath);

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
	virtual bool LoadFromFile(std::string_view filePath);

	/**
	* �ǂݍ��ݑO�������s�� 
	* ���̍X�V���A�����ł͓ǂݍ��݂͍s�킸�ɃR�}���h�Ƃ��đ��M�݂̂���悤�ɕύX����B
	*/
	bool Load(std::string_view filePath) noexcept;

	const std::string& GetName() const noexcept;

	Context* GetContext() const noexcept;

protected:

	/**
	* �h����Ŏ��ۂɃf�[�^��ǂݍ��ޏ�������������K�v������B
	* Load �֐����ŌĂяo�����悤�ɐ݌v����Ă���B
	*/
	virtual bool Do_Load(std::string_view filePath) = 0;

private:

	// * �������\�[�X�������\�[�X�����画�f���邽��
	std::string m_filePath;
};