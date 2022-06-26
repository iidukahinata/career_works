/**
* @file    IResource.h
* @brief   リソース抽象クラス
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include <string_view>

/**
* このクラスではデータ競合を引き起こさない。
* 抽象クラスとして特殊実装ではあるが、並列でのアクセスに対応出来るよう排他制御を行う。
* また、派生先で mutex のコピー禁止の影響を無くすために代入演算子をオーバーロードしている。
*/
class IResource
{
public:

	virtual ~IResource() {}

	/** 独自モデルデータとして保存させる。 */
	virtual void SaveToFile(std::string_view filePath);

	/** 独自モデルデータを読み込みする。 */
	virtual bool LoadFromFile(std::string_view filePath);

	/**
	* 読み込み前処理を行う 
	* 次の更新時、ここでは読み込みは行わずにコマンドとして送信のみするように変更する。
	*/
	bool Load(std::string_view filePath) noexcept;

	std::string_view GetName() const noexcept;

	void AddRef() noexcept;
	void SubRef() noexcept;
	size_t GetRef() const noexcept;

protected:

	/**
	* 派生先で実際にデータを読み込む処理を実装する必要がある。
	* Load 関数内で呼び出されるように設計されている。
	*/
	virtual bool Do_Load(std::string_view filePath) = 0;

private:

	// * 同じリソースかをリソース名から判断するため
	std::string m_filePath;

	// * 参照カウントで解放等を行うための変数。派生先ではなく使用者側でカウントする必要がある。
	size_t m_referenceCount = 0;
};