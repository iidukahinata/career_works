/**
* @file    IResource.h
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


class Context;

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
	virtual void SaveToFile(String_View filePath);

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B*/
	virtual bool LoadFromFile(String_View filePath);

	/**
	* �ǂݍ��ݑO�������s�� 
	* ���̍X�V���A�����ł͓ǂݍ��݂͍s�킸�ɃR�}���h�Ƃ��đ��M�݂̂���悤�ɕύX����B
	*/
	bool Load(String_View filePath) noexcept;

	const String& GetName() const noexcept;

	Context* GetContext() const noexcept;

protected:

	/**
	* �h����Ŏ��ۂɃf�[�^��ǂݍ��ޏ�������������K�v������B
	* Load �֐����ŌĂяo�����悤�ɐ݌v����Ă���B
	*/
	virtual bool Do_Load(String_View filePath) = 0;

private:

	// * �������\�[�X�������\�[�X�����画�f���邽��
	String m_filePath;
};