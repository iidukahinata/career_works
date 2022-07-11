/**
* @file    IResource.h
* @brief   リソース抽象クラス
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


class Context;

class IResource
{
	SUPER_CLASS(IResource)
public:

	virtual ~IResource() {}

	/** 独自モデルデータとして保存させる。*/
	virtual void SaveToFile(StringView filePath);

	/** 独自モデルデータを読み込みする。*/
	virtual bool LoadFromFile(StringView filePath);

	/**
	* 読み込み前処理を行う 
	* 次の更新時、ここでは読み込みは行わずにコマンドとして送信のみするように変更する。
	*/
	bool Load(StringView filePath) noexcept;

	const String& GetName() const noexcept;

	Context* GetContext() const noexcept;

protected:

	/**
	* 派生先で実際にデータを読み込む処理を実装する必要がある。
	* Load 関数内で呼び出されるように設計されている。
	*/
	virtual bool Do_Load(StringView filePath) = 0;

private:

	// * 同じリソースかをリソース名から判断するため
	String m_filePath;
};