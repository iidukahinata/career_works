#pragma once


#include "SubSystem/Math/MathCore.h"
#include <vector>
#include <list>
#include <memory>

template<class T>
class Octree
{
public:

	/**
	* @param level [����] �����l�� MaxLevel �ȉ��ł���K�v������܂��B
	* @param min [����] 0 level ��Ԃ̋��E�}�`�̍ŏ��l�̒l���Ӗ����܂��B
	* @param max [����] 0 level ��Ԃ̋��E�}�`�̍ő�l�̒l���Ӗ����܂��B
	*/
	bool Init(uint32_t level, const Math::Vector3& min, const Math::Vector3& max) noexcept;

	/** �����l�����Ԃ̑傫����ύX���܂��B */
	void Resize(const Math::Vector3& min, const Math::Vector3& max) noexcept;

	/**
	* @param min [����] �o�^�I�u�W�F�N�g�������E�}�`�̍ŏ��l���Ӗ����܂��B
	* @param max [����] �o�^�I�u�W�F�N�g�������E�}�`�̍ő�l���Ӗ����܂��B
	* @param obj [����] null �ȊO�̒l�ł���K�v������܂��B
	* @param id1 [�o��] �o�^��̔z��ԍ����������ARemove �֐��Ŏg�p�o���܂��B
	*					null �w��\�ł��B
	* @param id2 [�o��] �o�^��̃��X�g�ԍ����������ARemove �֐��Ŏg�p�o���܂��B
	*					null �w��\�ł��B
	*/
	bool Register(const Math::Vector3& min, const Math::Vector3& max, T* obj, int* id1, int* id2) noexcept;

	/**
	* @param vectorNum [�o��] �o�^���Ɏ擾�����z��ԍ����w�肷��K�v������܂��B
	* @param listNum [�o��] �o�^���Ɏ擾�������X�g�ԍ����w�肷��K�v������܂��B
	*/
	void Remove(int vectorNum, int listNum) noexcept;

	/** �z����̑S�Ă� list �f�[�^�݂̂��N���A���܂��B */
	void Clear() noexcept;

private:

	/** �����l�����ɏ��������Ԕԍ������ߕԂ��܂��B */
	uint32_t GetMortonOrder(uint8_t x, uint8_t y, uint8_t z) const noexcept;

	/**
	* ��ԏ������� bit ���琮���̋�ԃ��x���ɕϊ�������B
	* @param spatialInfo [����] 3bit ���Ƃɋ�ԏ���ێ����Ă���K�v������܂��B
	* @return bit ��񂩂�擾�����A���������ԃ��x����Ԃ��܂��B
	*/
	uint32_t ExtractSpatialLevels(uint8_t spatialInfo) const noexcept;

	/** ���̊֐��͊O���ł��g����\�������邽��Tools�ɒu�������������Ǝv���B*/
	uint32_t DivideIntoThreeByte(uint8_t value) const noexcept;

private:

	static const uint32_t MaxLevel = 8;

	// * ������Ԕz��
	std::vector<std::unique_ptr<std::list<T*>>> m_cells;

	// * ��ԃ��x��
	uint32_t m_level;

	// * �ő��Ԃ̍ŏ��l
	Math::Vector3 m_min;

	// * �ő��Ԃ̍ő�l
	Math::Vector3 m_max;

	// * �ŏ���Ԃł̃T�C�Y
	Math::Vector3 m_soaceWide;

	// * �ő��Ԃł̃T�C�Y
	Math::Vector3 m_worldWide;
};

template<class T>
inline bool Octree<T>::Init(uint32_t level, const Math::Vector3& min, const Math::Vector3& max) noexcept
{
	if (level < MaxLevel)
		return false;

	m_level = level;

	// �w�� level �̋�Ԑ����v�Z
	int size = (std::pow(8, level + 1) - 1) / 7;
	m_cells.resize(size);

	Resize(min, max);
	return true;
}

template<class T>
inline void Octree<T>::Resize(const Math::Vector3& min, const Math::Vector3& max) noexcept
{
	m_min = min;
	m_max = max;
	m_worldWide = max - min;
	m_soaceWide = m_worldWide / std::pow(2, m_level);
}

template<class T>
inline bool Octree<T>::Register(const Math::Vector3& min, const Math::Vector3& max, T* obj, int* id1, int* id2) noexcept
{
	const auto minBelongBit = (min - m_min) / m_soaceWide;
	const auto maxBelongBit = (max - m_min) / m_soaceWide;

	const auto numMin = GetMortonOrder(minBelongBit.x, minBelongBit.y, minBelongBit.z);
	const auto numMax = GetMortonOrder(maxBelongBit.x, maxBelongBit.y, maxBelongBit.z);

	const auto spatialLevel = ExtractSpatialLevels(numMax ^ numMin);
	auto numSpace = numMax >> (spatialLevel * 3);
	numSpace += (std::pow(8, spatialLevel) - 1) / 7;

	if (numSpace > m_cells.size())
		return false;

	// Remove �֐��Ŏg�p���邽�ߓo�^�ʒu���L�^���Ă����B
	if (id1) *id1 = numSpace;
	if (id2) *id2 = m_cells[numSpace]->size();

	// �������ߖ�̂��߁A�v�f����������Ă��Ȃ��\�������邽�߁B
	if (!m_cells[numSpace])
	{
		m_cells[numSpace] = std::make_unique<std::list<T*>>();
	}
	m_cells[numSpace]->push_back(obj);

	return true;
}

template<class T>
inline void Octree<T>::Remove(int vectorNum, int listNum) noexcept
{
	m_cells[vectorNum]->erase(m_cells[vectorNum]->begin() + listNum);
}

template<class T>
inline void Octree<T>::Clear() noexcept
{
	for (int i = 0; i < m_cells.size(); ++i)
	{
		m_cells[i]->clear();
	}
}

template<class T>
inline uint32_t Octree<T>::GetMortonOrder(uint8_t x, uint8_t y, uint8_t z) const noexcept
{
	return DivideIntoThreeByte(x) | DivideIntoThreeByte(y) << 1 | DivideIntoThreeByte(z) << 2;
}

template<class T>
inline uint32_t Octree<T>::ExtractSpatialLevels(uint8_t spatialInfo) const noexcept
{
	int level = -1;
	for (int i = 0; i < m_level; ++i)
	{
		// 3bit���Ƃɋ�ԏ�񂪊i�[����Ă��邽�� 3bit ���Ƃɒl���������Ă���
		int chack = spatialInfo & (0b111 << (i * 3));
		if (chack != 0)
		{
			level = i + 1;
		}
	}
	return level;
}

template<class T>
inline uint32_t Octree<T>::DivideIntoThreeByte(uint8_t value) const noexcept
{
	uint32_t result = value;
	result = (result | result << 8) & 0x00f00f;
	result = (result | result << 4) & 0x0c30c3;
	result = (result | result << 2) & 0x249249;
	return result;
}