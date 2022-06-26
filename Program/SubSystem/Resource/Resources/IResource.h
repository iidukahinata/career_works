/**
* @file    IResource.h
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <string_view>

/**
* ���̃N���X�ł̓f�[�^�����������N�����Ȃ��B
* ���ۃN���X�Ƃ��ē�������ł͂��邪�A����ł̃A�N�Z�X�ɑΉ��o����悤�r��������s���B
* �܂��A�h����� mutex �̃R�s�[�֎~�̉e���𖳂������߂ɑ�����Z�q���I�[�o�[���[�h���Ă���B
*/
class IResource
{
public:

	virtual ~IResource() {}

	/** �Ǝ����f���f�[�^�Ƃ��ĕۑ�������B */
	virtual void SaveToFile(std::string_view filePath);

	/** �Ǝ����f���f�[�^��ǂݍ��݂���B */
	virtual bool LoadFromFile(std::string_view filePath);

	/**
	* �ǂݍ��ݑO�������s�� 
	* ���̍X�V���A�����ł͓ǂݍ��݂͍s�킸�ɃR�}���h�Ƃ��đ��M�݂̂���悤�ɕύX����B
	*/
	bool Load(std::string_view filePath) noexcept;

	std::string_view GetName() const noexcept;

	void AddRef() noexcept;
	void SubRef() noexcept;
	size_t GetRef() const noexcept;

protected:

	/**
	* �h����Ŏ��ۂɃf�[�^��ǂݍ��ޏ�������������K�v������B
	* Load �֐����ŌĂяo�����悤�ɐ݌v����Ă���B
	*/
	virtual bool Do_Load(std::string_view filePath) = 0;

private:

	// * �������\�[�X�������\�[�X�����画�f���邽��
	std::string m_filePath;

	// * �Q�ƃJ�E���g�ŉ�������s�����߂̕ϐ��B�h����ł͂Ȃ��g�p�ґ��ŃJ�E���g����K�v������B
	size_t m_referenceCount = 0;
};