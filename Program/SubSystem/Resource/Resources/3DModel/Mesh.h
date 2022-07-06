/**
* @file    Mesh.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../IResource.h"
#include "SubSystem/Renderer/Geometry/Vertex.h"
#include "SubSystem/Renderer/D3D11/D3D11IndexBuffer.h"
#include "SubSystem/Renderer/D3D11/D3D11VertexBuffer.h"

class Mesh : public IResource
{
	SUB_CLASS(Mesh)
public:

	Mesh() = default;
	void Construct(const Vector<VertexBump3D>& vertices, const Vector<uint32_t>& indices) noexcept;

	/** 独自モデルデータとして保存させる。*/
	void SaveToFile(String_View filePath) override;

	/** 独自モデルデータを読み込みする。*/
	bool LoadFromFile(String_View filePath) override;

	/** アクセス */
	void SetVertices(const Vector<VertexBump3D>& vertices) noexcept;
	const Vector<VertexBump3D>& GetVertices() noexcept;

	void SetIndices(const Vector<uint32_t>& indices) noexcept;
	const Vector<uint32_t>& GetIndices() noexcept;

	void Render() const noexcept;

protected:

	virtual bool Do_Load(String_View filePath) override;

	String ConvertProprietaryFormat(String_View filePath) const noexcept;

private:

	bool SetUp() noexcept;

private:

	Vector<VertexBump3D> m_vertices;
	Vector<uint32_t> m_indices;

	D3D11VertexBuffer<VertexBump3D> m_vertexBuffer;
	D3D11IndexBuffer m_indexBuffer;
};