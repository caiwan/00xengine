#include "Core/Entity.hpp"

namespace engine{
	void Entity::MakeCube(const std::string &pMeshName, Shader &pShader){
		Vector3F position[] = { Vector3F(-1.f,-1.f,-1.f), Vector3F(-1.f,-1.f,1.f), Vector3F(1.f,-1.f,1.f), Vector3F(1.f,-1.f,-1.f),
								Vector3F(-1.f,1.f,-1.f), Vector3F(-1.f,1.f,1.f), Vector3F(1.f,1.f,1.f), Vector3F(1.f,1.f,-1.f), 
								Vector3F(-1.f,-1.f,-1.f), Vector3F(-1.f,1.f,-1.f), Vector3F(1.f,1.f,-1.f), Vector3F(1.f,-1.f,-1.f),
								Vector3F(-1.f,-1.f,1.f), Vector3F(-1.f,1.f,1.f), Vector3F(1.f,1.f,1.f), Vector3F(1.f,-1.f,1.f), 
								Vector3F(-1.f,-1.f,-1.f), Vector3F(-1.f,-1.f,1.f), Vector3F(-1.f,1.f,1.f), Vector3F(-1.f,1.f,-1.f), 
								Vector3F(1.f,-1.f,-1.f), Vector3F(1.f,-1.f,1.f), Vector3F(1.f,1.f,1.f), Vector3F(1.f,1.f,-1.f)
							  };

		Index indices[] =	  { 0, 2, 1, 0, 3, 2, 
								4, 5, 6, 4, 6, 7,
								8, 9, 10, 8, 10, 11, 
								12, 15, 14, 12, 14, 13, 
								16, 17, 18, 16, 18, 19, 
								20, 23, 22, 20, 22, 21
							  };

		Vector2F texcoords[] = {Vector2F(1.f, 1.f), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f),
								Vector2F(1.f, 1.F), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f),
								Vector2F(1.f, 1.F), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f),
								Vector2F(1.f, 1.F), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f),
								Vector2F(1.f, 1.F), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f),
								Vector2F(1.f, 1.F), Vector2F(1.f, 0.f), Vector2F(0.f, 0.f), Vector2F(0.f, 1.f)
		};

		Vector3F normals[] = {	Vector3F::NEGUNIT_Y, Vector3F::NEGUNIT_Y, Vector3F::NEGUNIT_Y, Vector3F::NEGUNIT_Y,
								Vector3F::UNIT_Y, Vector3F::UNIT_Y, Vector3F::UNIT_Y, Vector3F::UNIT_Y, 
								Vector3F::NEGUNIT_Z, Vector3F::NEGUNIT_Z, Vector3F::NEGUNIT_Z, Vector3F::NEGUNIT_Z,
								Vector3F::UNIT_Z, Vector3F::UNIT_Z, Vector3F::UNIT_Z, Vector3F::UNIT_Z, 
								Vector3F::NEGUNIT_X, Vector3F::NEGUNIT_X, Vector3F::NEGUNIT_X, Vector3F::NEGUNIT_X,
								Vector3F::UNIT_X, Vector3F::UNIT_X, Vector3F::UNIT_X, Vector3F::UNIT_X 
							 };

		
		CreateVAO(pMeshName, pShader, position, sizeof(position), indices, sizeof(indices));

		switch(mType){
		case ET_MESH:
			Make(normals,texcoords);break;
		case ET_OBJECT:
			Make(normals);break;
		case ET_DEBUGOBJECT:
			Make(texcoords);break;
		}
	}

	// :[
	void Entity::MakeSphere(const std::string &pMeshName, Shader &pShader, s32 pSlices){
		std::vector<Vector3F> vertices;
		std::vector<Vector2F> texcoords;
		std::vector<Vector3F> normals;
		std::vector<Index> indices;
		Vector3F v;

		f32 angleStep = 2.f * Math::Pi / (f32)pSlices;
		int midP = pSlices;

		for(int i = 0; i < pSlices; ++i)
			for(int j = 0; j < pSlices; ++j){
				v.x = Math::Sin(angleStep * (f32)i) * Math::Sin(angleStep * (f32)j);
				v.y = Math::Cos(angleStep * (f32)i);
				v.z = Math::Sin(angleStep * (f32)i) * Math::Cos(angleStep * (f32)j);

				vertices.push_back(v);
				normals.push_back(v);

				texcoords.push_back(Vector2F((f32)j / (f32)pSlices, (1.f - (f32)i) / (f32)(pSlices - 1)));
			}
			
		for(int i = 0; i < pSlices; ++i)
			for(int j = 0; j < pSlices; ++j){
				indices.push_back( i    * (pSlices + 1) +  j);
				indices.push_back((i+1) * (pSlices + 1) +  j);
				indices.push_back((i+1) * (pSlices + 1) + (j + 1));
				
				indices.push_back( i    * (pSlices + 1) +  j);
				indices.push_back((i+1) * (pSlices + 1) + (j + 1));
				indices.push_back( i    * (pSlices + 1) + (j + 1));
			}

		CreateVAO(pMeshName, pShader, &vertices[0], vertices.size() * sizeof(Vector3F), &indices[0], indices.size() * sizeof(Index));
		Make(&normals[0]);
	}
}