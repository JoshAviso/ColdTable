#include <ColdTable/Resource/Mesh/Mesh.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <algorithm>
#include <locale>
#include <codecvt>
#include <ColdTable/Math/Vertex.h>
#include <ColdTable/Graphics/VertexBuffer.h>

#include "ColdTable/Resource/ShaderLibrary.h"
#include "ColdTable/Resource/Material/Material.h"

ColdTable::Mesh::Mesh(RenderablePtr renderable) : Resource()
{
	_vertexBuffer = renderable->_vertexBuffer;
	_indexBuffer = renderable->_indexBuffer;
}

ColdTable::Mesh::Mesh(GraphicsDevicePtr sourceDevice, const Vertex* vertexList, UINT vertexCount) : Resource()
{
	_vertexBuffer = sourceDevice->CreateVertexBuffer();
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), vertexCount, ShaderLibrary::GetShader("BlankShader"));
	_indexBuffer = nullptr;
}

ColdTable::Mesh::Mesh(GraphicsDevicePtr sourceDevice, const Vertex* vertexList, UINT vertexCount, const void* indexList,
	UINT indexCount) : Resource()
{
	_vertexBuffer = sourceDevice->CreateVertexBuffer();
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), vertexCount, ShaderLibrary::GetShader("BlankShader"));
	_indexBuffer = sourceDevice->CreateIndexBuffer();
	_indexBuffer->LoadIndices(indexList, indexCount);
}

ColdTable::Mesh::Mesh(GraphicsDevicePtr sourceDevice, const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");
	if (!res) throw std::exception("Mesh not created successfully");
	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	std::vector<Vertex> list_vertices;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;
				if (attribs.texcoords.size() > index.texcoord_index * 2 + 1)
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}

				tinyobj::real_t nx = 0;
				tinyobj::real_t ny = 1;
				tinyobj::real_t nz = 0;

				if (attribs.texcoords.size() > index.normal_index * 3 + 2)
				{
					nx = attribs.normals[index.normal_index * 3 + 0];
					ny = attribs.normals[index.normal_index * 3 + 1];
					nz = attribs.normals[index.normal_index * 3 + 2];
				}

				Vertex vert(Vec3(vx, vy, vz), Vec2(tx, ty), Vec3(nx, ny, nz));
				list_vertices.push_back(vert);
				list_indices.push_back(index_offset + v);
			}
			index_offset += num_face_verts;
		}
	}

	_vertexBuffer = sourceDevice->CreateVertexBuffer();
	_vertexBuffer->LoadVertices(&list_vertices[0], sizeof(Vertex), (UINT)list_vertices.size(), ShaderLibrary::GetShader("BlankShader"));

	_indexBuffer = sourceDevice->CreateIndexBuffer();
	_indexBuffer->LoadIndices(&list_indices[0], (UINT)list_indices.size());
}

ColdTable::Mesh::Mesh(GraphicsDevicePtr sourceDevice, const wchar_t* full_path, MaterialPtr material) :
	Mesh(sourceDevice, full_path){ _material = material; }

ColdTable::Mesh::~Mesh()
{
}

bool ColdTable::Mesh::GetAABB(Vec3& aabb_min, Vec3& aabb_max)
{
	if (_vertexBuffer == nullptr) return false;
	aabb_min = Vec3(999999.0);
	aabb_max = Vec3(-999999.0);

	if (_vertexBuffer->_vertexObjects.empty())
	{
		for (const auto& vertex : _vertexBuffer->_vertices)
		{
			Vec3 pos = vertex->position;

			aabb_min.x = std::min(pos.x, aabb_min.x);
			aabb_min.y = std::min(pos.y, aabb_min.y);
			aabb_min.z = std::min(pos.z, aabb_min.z);
			aabb_max.x = std::max(pos.x, aabb_max.x);
			aabb_max.y = std::max(pos.y, aabb_max.y);
			aabb_max.z = std::max(pos.z, aabb_max.z);
		}
		return true;
	}

	for (const auto& vertex : _vertexBuffer->_vertexObjects)
	{
		Vec3 pos = vertex->getActualPos();

		aabb_min.x = std::min(pos.x, aabb_min.x);
		aabb_min.y = std::min(pos.y, aabb_min.y);
		aabb_min.z = std::min(pos.z, aabb_min.z);
		aabb_max.x = std::max(pos.x, aabb_max.x);
		aabb_max.y = std::max(pos.y, aabb_max.y);
		aabb_max.z = std::max(pos.z, aabb_max.z);
	}

	return true;
}
