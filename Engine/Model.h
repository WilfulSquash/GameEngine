#pragma once
#include "Mesh.h"
#include <vector>
using namespace std;
namespace nu{
	class Model {	
	public:
		Model() = default;
		Model(const vector<Mesh>& meshes) : m_meshes{ meshes } {}

		void AddMesh(const Mesh& mesh) { m_meshes.push_back(mesh); }

		void SetMeshes(const vector<Mesh>& meshes) { m_meshes = meshes; }
		const vector<Mesh>& GetMeshes() const { return m_meshes; }
		vector<Mesh> m_meshes;
	private:

	};
}