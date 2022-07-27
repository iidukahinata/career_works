/**
* @file    Material.cpp
* @brief
*
* @date	   2022/07/26 2022年度初版
*/


#include "Material.h"
#include "Texture.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

Material::Material()
{
	// 仮設定
	SetVSShader("assets/Resource/Shader/PBR_VS.cso");
	SetPSShader("assets/Resource/Shader/PBR_PS.cso");
}

void Material::SaveToFile(StringView filePath)
{
	const auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	if (!fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode))
		return;

	fileStream.Write(m_textures.size());
	for (auto& texture : m_textures)
	{
		fileStream.Write(texture->GetName());
	};
}

bool Material::LoadFromFile(StringView filePath)
{
	const auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	size_t numTexture = 0;
	fileStream.Read(&numTexture);

	Vector<String> texturePaths(numTexture);
	for (auto& path : texturePaths)
	{
		fileStream.Read(&path);
	};

	fileStream.Close();

	if (const auto resoureManager = GetContext()->GetSubsystem<ResourceManager>())
	{
		for (auto& path : texturePaths)
		{
			AddTexture(resoureManager->Load<Texture>(path));
		}
	};

	CreateRootSignature();
	CreatePipelineState();

	return m_textures.empty() == false;
}

void Material::AddTexture(Texture* texture) noexcept
{
	m_textures.emplace_back(texture);
}

void Material::SetVSShader(StringView name)
{
	m_vertexShader.Compile(name, "main", "vs_5_0");
}

void Material::SetPSShader(StringView name)
{
	m_pixelShader.Compile(name, "main", "ps_5_0");
}

void Material::ShaderSet() const noexcept
{
	m_pipelineState.Set();
	m_rootSignature.SetGraphics();
}

String Material::ConvertProprietaryFormat(StringView filePath) const noexcept
{
	String path = "assets/Resource/Material/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	StringView sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".material";

	return path;
}

bool Material::CreatePipelineState() noexcept
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
	gpipeline.pRootSignature = m_rootSignature.Get();
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(m_vertexShader.GetBlob());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(m_pixelShader.GetBlob());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	gpipeline.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

	gpipeline.DepthStencilState.DepthEnable = true;
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	gpipeline.DepthStencilState.StencilEnable = false;

	gpipeline.InputLayout = m_vertexShader.GetInputLayout();

	gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	gpipeline.SampleDesc.Count = 1;
	gpipeline.SampleDesc.Quality = 0;

	return m_pipelineState.Create(gpipeline);
}

bool Material::CreateRootSignature() noexcept
{
	constexpr UINT maxCBVCount = 8;
	constexpr UINT maxSRVCount = 16;
	constexpr UINT maxUAVCount = 8;

	// パラメータ設定
	Array<CD3DX12_DESCRIPTOR_RANGE1, 3> descTblRanges;
	Array<CD3DX12_ROOT_PARAMETER1, 3> rootParams;

	//=== CBV用設定 ============================================
	descTblRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, maxCBVCount, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
	rootParams[0].InitAsDescriptorTable(1, &descTblRanges[0]);
	//==========================================================

	//=== SRV用設定 ============================================
	descTblRanges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, maxSRVCount, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
	rootParams[1].InitAsDescriptorTable(1, &descTblRanges[1]);
	//==========================================================

	//=== UAV用設定 ============================================
	descTblRanges[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, maxUAVCount, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
	rootParams[2].InitAsDescriptorTable(2, &descTblRanges[2]);
	//==========================================================

	Array<CD3DX12_STATIC_SAMPLER_DESC, 1> samplerDescs;
	samplerDescs[0].Init(1, D3D12_FILTER_ANISOTROPIC, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);

	auto ret = m_rootSignature.Create(
		rootParams.max_size(), rootParams.data(), samplerDescs.max_size(), samplerDescs.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS);

	return ret;
}