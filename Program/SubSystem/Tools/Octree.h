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
	* @param level [入力] 引数値が MaxLevel 以下である必要があります。
	* @param min [入力] 0 level 空間の境界図形の最小値の値を意味します。
	* @param max [入力] 0 level 空間の境界図形の最大値の値を意味します。
	*/
	bool Init(uint32_t level, const Math::Vector3& min, const Math::Vector3& max) noexcept;

	/** 引数値から空間の大きさを変更します。 */
	void Resize(const Math::Vector3& min, const Math::Vector3& max) noexcept;

	/**
	* @param min [入力] 登録オブジェクトが持つ境界図形の最小値を意味します。
	* @param max [入力] 登録オブジェクトが持つ境界図形の最大値を意味します。
	* @param obj [入力] null 以外の値である必要があります。
	* @param id1 [出力] 登録先の配列番号が代入され、Remove 関数で使用出来ます。
	*					null 指定可能です。
	* @param id2 [出力] 登録先のリスト番号が代入され、Remove 関数で使用出来ます。
	*					null 指定可能です。
	*/
	bool Register(const Math::Vector3& min, const Math::Vector3& max, T* obj, int* id1, int* id2) noexcept;

	/**
	* @param vectorNum [出力] 登録時に取得した配列番号を指定する必要があります。
	* @param listNum [出力] 登録時に取得したリスト番号を指定する必要があります。
	*/
	void Remove(int vectorNum, int listNum) noexcept;

	/** 配列内の全ての list データのみをクリアします。 */
	void Clear() noexcept;

private:

	/** 引数値を元に所属する空間番号を求め返します。 */
	uint32_t GetMortonOrder(uint8_t x, uint8_t y, uint8_t z) const noexcept;

	/**
	* 空間情報を持つ bit から整数の空間レベルに変換させる。
	* @param spatialInfo [入力] 3bit ごとに空間情報を保持している必要があります。
	* @return bit 情報から取得した、所属する空間レベルを返します。
	*/
	uint32_t ExtractSpatialLevels(uint8_t spatialInfo) const noexcept;

	/** この関数は外部でも使える可能性があるためToolsに置いた方がいいと思う。*/
	uint32_t DivideIntoThreeByte(uint8_t value) const noexcept;

private:

	static const uint32_t MaxLevel = 8;

	// * 分割空間配列
	std::vector<std::unique_ptr<std::list<T*>>> m_cells;

	// * 空間レベル
	uint32_t m_level;

	// * 最大空間の最小値
	Math::Vector3 m_min;

	// * 最大空間の最大値
	Math::Vector3 m_max;

	// * 最小空間でのサイズ
	Math::Vector3 m_soaceWide;

	// * 最大空間でのサイズ
	Math::Vector3 m_worldWide;
};

template<class T>
inline bool Octree<T>::Init(uint32_t level, const Math::Vector3& min, const Math::Vector3& max) noexcept
{
	if (level < MaxLevel)
		return false;

	m_level = level;

	// 指定 level の空間数を計算
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

	// Remove 関数で使用するため登録位置を記録しておく。
	if (id1) *id1 = numSpace;
	if (id2) *id2 = m_cells[numSpace]->size();

	// メモリ節約のため、要素が生成されていない可能性があるため。
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
		// 3bitごとに空間情報が格納されているため 3bit ごとに値を検索している
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