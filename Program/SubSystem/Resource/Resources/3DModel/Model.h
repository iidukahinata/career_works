/**
* @file    Model.h
* @brief
*
* @date	   2022/05/11 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "ModelData.h"
#include "SubSystem/Renderer/D3D11/D3D11Shader.h"
#include "SubSystem/Renderer/D3D11/D3D11InputLayout.h"
#include "SubSystem/Renderer/D3D11/D3D11SamplerState.h"

/** Model の初期化時設定の項目構造体 */
struct ModelDesc
{
	// * 読み込むモデルパスを指定してください。
	std::string modelFilePath;

	// * テクスチャが入っているフォルダパスを指定してください。
	std::string textureFolderPath;

	// * null 以外の値である必要があります。
	D3D11_INPUT_ELEMENT_DESC* layout = nullptr;

	// * layout 配列の要素数を指定してください。
	UINT layoutSize = 0;

	// * 使用するシェーダーパスを指定してください。
	const char* vsShader = "assets/Shader/LambertVS.cso";
	const char* psShader = "assets/Shader/LambertPS.cso";
};

/** 今後テクスチャデータをマテリアルに分ける実装に変更予定。 */
class Model
{
public:

	Model() = default;

	/** リソースの参照数を変更する必要があるため、コピー関数をオバーライドする。*/
	Model(const Model& model);
	Model& operator=(const Model& model);

	~Model();

	void Init(const ModelDesc& desc);
	void Draw(const DirectX::XMMATRIX& world);

private:

	/** 指定フォルダ内の全てのテクスチャを読み込む */
	void LoadTextures(std::string_view textureFolderPath);

private:

	ModelData* m_modelData;

	// * shader object
	D3D11VertexShader m_vertexShader;
	D3D11PixelShader  m_pixelShader;

	D3D11InputLayout m_inputLayout;

	D3D11SamplerState m_samplerState;
};