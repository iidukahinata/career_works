/**
* @file    IResource.h
* @brief   リソース抽象クラス
*
* @date	   2022/06/29 2022年度初版
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

	/** 独自モデルデータとして保存させる。*/
	virtual void SaveToFile(std::string_view filePath);

	/** 独自モデルデータを読み込みする。*/
	virtual bool LoadFromFile(std::string_view filePath);

	/**
	* 読み込み前処理を行う 
	* 次の更新時、ここでは読み込みは行わずにコマンドとして送信のみするように変更する。
	*/
	bool Load(std::string_view filePath) noexcept;

	const std::string& GetName() const noexcept;

	Context* GetContext() const noexcept;

protected:

	/**
	* 派生先で実際にデータを読み込む処理を実装する必要がある。
	* Load 関数内で呼び出されるように設計されている。
	*/
	virtual bool Do_Load(std::string_view filePath) = 0;

private:

	// * 同じリソースかをリソース名から判断するため
	std::string m_filePath;
};