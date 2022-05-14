/**
* @file    IResource.h
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <string>
#include <mutex>

/**
* ���̃N���X�ł̓f�[�^�����������N�����Ȃ��B
* ���ۃN���X�Ƃ��ē�������ł͂��邪�A����ł̃A�N�Z�X�ɑΉ��o����悤�r��������s���B
* �܂��A�h����� mutex �̃R�s�[�֎~�̉e���𖳂������߂ɑ�����Z�q���I�[�o�[���[�h���Ă���B
*/
class IResource
{
public:

	virtual ~IResource() {}

	IResource() = default;

	IResource(const IResource&);
	IResource& operator=(const IResource&);

	/** �ǂݍ��ݑO�������s�� */
	bool Load(std::string_view filePath) noexcept;

	const std::string& GetName() const noexcept;

	void AddRefreneceCount() noexcept;
	void SubReneceCount() noexcept;
	size_t GetRefreneceCount() const noexcept;

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

	// * ���̃N���X���ł̔r����������p
	std::mutex m_mutex;
};