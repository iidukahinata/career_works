/**
* @file    D3D11Shader.h
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
* @note
*						 D3D11Shader
*						   	 ↓
*		   -----------------------------------------
*	      ↓	                 ↓					   ↓
*	D3D11VertexShader	D3D11PixelShader	D3D11ComputeShader
*/
#pragma once


#include "D3D11DeviceChild.h"

/**	各シェーダーオブジェクト抽象クラス */
class D3D11Shader : public D3D11DeviceChild
{
public:

	/**
	* 指定シェーダーのコンパイルを行う
	* @param shader [入力] コンパイルを行うシェーダーファイル名
	* @param entrypoint [入力] 指定シェーダーの開始位置
	* @param traget [入力] シェーダー種類を指定
	*/
	bool CompileFromFile(std::string_view shader, std::string_view entrypoint, std::string_view traget) noexcept;

	/** アクセス */
	ID3DBlob* GetBlob() const noexcept;

protected:

	// * コンパイルしたシェーダーデータを保持させる
	Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
};

class D3D11VertexShader : public D3D11Shader
{
public:

	/**
	* @param shader [入力] 何かしらの文字列である必要があります。
	* @param entrypoint [入力] 何かしらの文字列である必要があります。
	* @param traget [入力] 何かしらの文字列である必要があります。
	*/
	bool Create(std::string_view shader, std::string_view entrypoint = "main", std::string_view target = "vs_5_0") noexcept;

	/** デバイス設定するための関数です。*/
	void VSSet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
};

class D3D11PixelShader : public D3D11Shader
{
public:

	/**
	* @param shader [入力] 何かしらの文字列である必要があります。
	* @param entrypoint [入力] 何かしらの文字列である必要があります。
	* @param traget [入力] 何かしらの文字列である必要があります。
	*/
	bool Create(std::string_view shader, std::string_view entrypoint = "main", std::string_view target = "ps_5_0") noexcept;

	/** デバイス設定するための関数です。*/
	void PSSet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
};

class D3D11ComputeShader : public D3D11Shader
{
public:

	/**
	* @param shader [入力] 何かしらの文字列である必要があります。
	* @param entrypoint [入力] 何かしらの文字列である必要があります。
	* @param traget [入力] 何かしらの文字列である必要があります。
	*/
	bool Create(std::string_view shader, std::string_view entrypoint = "main", std::string_view target = "gs_5_0") noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader;
};