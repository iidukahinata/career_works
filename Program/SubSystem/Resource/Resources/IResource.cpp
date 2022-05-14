/**
* @file    IResource.cpp
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "IResource.h"

IResource::IResource(const IResource& resource)
{
	m_filePath = resource.m_filePath;
	m_referenceCount = resource.m_referenceCount;
}

IResource& IResource::operator=(const IResource& resource)
{
	m_filePath = resource.m_filePath;
	m_referenceCount = resource.m_referenceCount;
	return *this;
}

bool IResource::Load(std::string_view filePath) noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_filePath = filePath;
	lock.unlock();

	// ���ۂɓǂݍ���
	return Do_Load(filePath);
}

const std::string& IResource::GetName() const noexcept
{
	return m_filePath;
}

void IResource::AddRefreneceCount() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	++m_referenceCount;
}

void IResource::SubReneceCount() noexcept
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_referenceCount > 0)
		--m_referenceCount;
}

size_t IResource::GetRefreneceCount() const noexcept
{
	return m_referenceCount;
}