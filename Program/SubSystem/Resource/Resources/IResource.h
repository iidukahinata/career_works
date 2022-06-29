/**
* @file    IResource.h
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/06/29 2022�N�x����
*/
#pragma once


#include "SubSystem/Core/Context.h"

enum ResourceType
{
	STATIC,

	DYNAMIC,
};

class IResource
{
	SUPER_CLASS(IResource)
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