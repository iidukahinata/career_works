/**
* @file    Scene.h
* @brief   シーン抽象クラス
*
* @date	   2022/05/06 2022年度初版
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
	* モデル等のリソース読み込み処理を書くと効率化する可能性がある。
	* 例：前のシーンで使用していたリソースを読み込む、同じリソースの読み込み待ちを無くす。
	*/
	virtual void Awake() {};

	/**
	* サブクラスで初期化時処理を実現させる 
	* シーンが切り替わってから処理される初期化関数。
	*/
	virtual void Init() {};

	/** サブクラスで更新時処理を実現させる */
	virtual void Update();

	/** サブクラスで描画時処理を実現させる */
	virtual void Draw();

	/** Scene 終了時のサブクラスでの解放処理を実現 */
	virtual void Clear();

	/** GameObject function */
	void AddGameObject(IGameObject* gameObject);
	IGameObject* GetGameObject(std::string_view name);
	void RemoveGameObject(int id);
	std::vector<std::unique_ptr<IGameObject>>& GetGameObjects() noexcept;

	/** アクセス */
	Camera* GetMainCamera() const noexcept;
	LightMap* GetLightMap() noexcept;

	/** 遅延セットアップ */
	void SetSceneManager(class SceneManager* sceneManager) noexcept;

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