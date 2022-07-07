/**
* @file    LightMap.h
* @brief
*
* @date	   2022/07/08 2022年度初版
*/
#pragma once


class Light;

/**
* Ligth 管理クラス抽象クラス
* 各インターフェイス関数を定義。
* 派生先でクラスタード用ライトマップなどを作成。
*/
class LightMap
{
	SUPER_CLASS(LightMap)
public:

	virtual ~LightMap();

	/** 各 Light 定数バッファ等を作成等行う。*/
	virtual void Initialize() {}

	/**
	* Light定数バッファをGPUにセットする処理を書き込む。
	* 基本的には Renderer の描画前に呼び出される。
	*/
	virtual void Update(const Math::Vector3& cameraPos) {}

	void Clear() noexcept;

	void AddLight(Light* light) noexcept;
	void RemoveLight(Light* light) noexcept;

	void SetAmbient(const Math::Vector4& color) noexcept;

protected:

	// * Sceneにセットされている全てのLightオブジェクト
	Vector<Light*> m_lights;

	// * 環境光カラー
	Math::Vector4 m_ambientLight;
};