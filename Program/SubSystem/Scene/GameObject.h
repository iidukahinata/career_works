/**
* @file    GameObject.h
* @brief   各GameObjectの抽象クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "Transform.h"

class IGameObject
{
public:

	virtual ~IGameObject() {}

	/**
	* サブクラスで初期化処理を実現させる
	* Scene登録時に呼び出されるように設計されている
	*/
	virtual void Init() {}

	/**
	* サブクラスで更新処理を実現させる
	* 呼び出しタイミングは所属 Scene の実装方法で変化
	*/
	virtual void Update() {}

	/**
	* サブクラスで描画処理を実現させる
	* 呼び出しタイミングは所属 Scene の実装方法で変化
	*/
	virtual void Draw() {}

	int GetID() const noexcept;
	void SetID(int id) noexcept;
	const std::string& GetName() noexcept;

	Transform& GetTransform() noexcept;

	/** 遅延セットアップ */
	void SetScene(class IScene* scene) noexcept;

protected:

	// * Sceneクラスで探索時等に使用される
	int m_id;

	// * Sceneクラスで検索等で使用される
	std::string m_name;

	Transform m_transform;

	class IScene* m_scene = nullptr;
};