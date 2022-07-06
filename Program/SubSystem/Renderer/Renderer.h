/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "LightMap.h"
#include "SubSystem/Core/ISubsystem.h"

class Light;
class Camera;
class RenderObject;
class PostProcessEffect;

/**
* Renderer抽象クラス
* このクラスではインターフェースのみを実装。
* 派生クラスで初期化等の関数を実装する。
*/
class Renderer : public ISubsystem
{
	SUB_CLASS(Renderer)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** Light メソッド */
	void AddLight(Light* light) noexcept;
	void RemoveLight(Light* light) noexcept;

	/** Camera メソッド */
	void AddCamera(Camera* camera) noexcept;
	void RemoveCamera(Camera* camera) noexcept;
	Camera* GetMainCamera() const noexcept;

	/** Render Object メソッド */
	void AddRenderObject(RenderObject* rederObject) noexcept;
	void RemoveRenderObject(RenderObject* rederObject) noexcept;

	/** Post Process Effect メソッド */
	void RegisterPostProcess(PostProcessEffect* postProcess) noexcept;
	void OnRegisterPostProcess(PostProcessEffect* postProcess) noexcept;

protected:

	// * ライト管理のためのマップクラス
	UniquePtr<LightMap> m_lightMap;

	// * Sceneに設置された描画オブジェクト配列。
	Set<RenderObject*> m_renderObjects;

	Camera* m_mainCamera = nullptr;

	// * 配列にするのは後にレイヤーなどでUIなどの描画を制御させていくため。
	Set<Camera*> m_cameras;

	PostProcessEffect* m_postProcessEffect = nullptr;
};