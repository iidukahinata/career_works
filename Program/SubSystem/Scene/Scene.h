/**
* @file    Scene.h
* @brief   シーン抽象クラス
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <memory>
#include "GameObject.h"
#include "SubSystem/Renderer/Camera/Camera.h"
#include "SubSystem/Renderer/Drawings/Light/LightMap.h"

class IScene
{
public:

	virtual ~IScene() {}

	/**
	* サブクラスでロード時処理を実現させる 
	* この関数が終了したタイミングでシーンが切り替わる。
	* モデル等リソース読み込み処理を持つゲームオブジェクトの生成処理を書くと効率化する可能性がある。
	* しかし、IO処理は一定時間より早くならないので SetUp 待ち時間が減ることでの短縮のみ
	* 例：前のシーンで使用していたリソースを読み込む、同じリソースの読み込み待ちを無くす。
	*/
	virtual void Awake() {};

	/**
	* サブクラスで初期化時処理を実現させる 
	* シーンが切り替わってから処理される初期化関数。
	*/
	virtual void Init();

	/** サブクラスで更新時処理を実現させる */
	virtual void Update();

	/** サブクラスで描画時処理を実現させる */
	virtual void Draw();

	/** Scene 終了時のサブクラスでの解放処理を実現 */
	virtual void Clear();

	virtual const char* GetName() = 0;

	/** GameObject function */
	template<class T>
	T* AddGameObject();
	void AddGameObject(IGameObject* gameObject);

	template<class T>
	T* GetGameObject(std::string_view name);
	IGameObject* GetGameObject(std::string_view name);

	void RemoveGameObject(IGameObject* gameObject);
	std::vector<std::unique_ptr<IGameObject>>& GetGameObjects() noexcept;

	/** アクセス */
	Camera* GetMainCamera() const noexcept;
	LightMap* GetLightMap() noexcept;

	/** 遅延セットアップ */
	void SetSceneManager(class SceneManager* sceneManager) noexcept;
	class SceneManager* GetSceneManager() const noexcept;

protected:

	// * シーン内オブジェクト配列
	std::vector<std::unique_ptr<IGameObject>> m_gameObjects;

	// * サブカメラは派生先でユーザーに拡張してもらう
	std::unique_ptr<Camera> m_mainCamera;

	// * シーン内のライト管理クラス
	LightMap m_lightMap;

	DirectionalLight m_directionalLight;
	std::vector<PointLight> m_pointLights;
	std::vector<SpotLight> m_spotLights;

	class SceneManager* m_sceneManager = nullptr;
};

template<class T>
inline T* IScene::AddGameObject()
{
	auto gameObject = new T;

	// 検索時間の短縮のために配列番号をIDとする
	gameObject->SetID(m_gameObjects.size());
	gameObject->SetScene(this);

	gameObject->Awake();

	m_gameObjects.emplace_back(gameObject);
	return gameObject;
}

template<class T>
inline T* IScene::GetGameObject(std::string_view name)
{
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetName() == name.data())
		{
			return dynamic_cast<T*>(gameObject.get());
		}
	}
	return nullptr;
}