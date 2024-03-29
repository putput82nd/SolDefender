#include"Mesh.h"

MeshClass::MeshClass()
{
	
}

MeshClass::~MeshClass()
{

}

void MeshClass::InitMeshClass(IDirect3DDevice9* gd3dDevice)
{
	InitAllVertexDeclarations(gd3dDevice);
}

void MeshClass::LoadXFile(LPCWSTR fileName, IDirect3DDevice9* gd3dDevice)
{
	Model* meshModel;
	meshModel = new Model;

	// Step 1: Load the .x file from file into a system memory mesh.
	ID3DXMesh* meshSys      = 0;
	ID3DXBuffer* adjBuffer  = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls          = 0;

	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, gd3dDevice,
		&adjBuffer,	&mtrlBuffer, 0, &numMtrls, &meshSys);

	// Step 2: Find out if the mesh already has normal info?
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	meshSys->GetDeclaration(elems);
	
	bool hasNormals = false;
	D3DVERTEXELEMENT9 term = D3DDECL_END();
	for(int i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		// Did we reach D3DDECL_END() {0xFF,0,D3DDECLTYPE_UNUSED, 0,0,0}?
		if(elems[i].Stream == 0xff )
			break;

		if( elems[i].Type == D3DDECLTYPE_FLOAT3 &&
			elems[i].Usage == D3DDECLUSAGE_NORMAL &&
			elems[i].UsageIndex == 0 )
		{
			hasNormals = true;
			break;
		}
	}

	// Step 3: Change vertex format to VertexPNT.
	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexPNT::Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh* temp = 0;
	meshSys->CloneMesh(D3DXMESH_SYSTEMMEM, 
		elements, gd3dDevice, &temp);
	SAFE_RELEASE(meshSys);
	meshSys = temp;

	// Step 4: If the mesh did not have normals, generate them.
	if( hasNormals == false)
		D3DXComputeNormals(meshSys, 0);

	// Step 5: Optimize the mesh.
	meshSys->Optimize(D3DXMESH_MANAGED | 
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, 
		(DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0, &meshModel->mesh);
	SAFE_RELEASE(meshSys); // Done w/ system mesh.
	SAFE_RELEASE(adjBuffer); // Done with buffer.

	//***************************************************
	
	// Step 6: Extract the materials and load the textures.
	if( mtrlBuffer != 0 && numMtrls != 0 )
	{
		D3DXMATERIAL* d3dxmtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(DWORD i = 0; i < numMtrls; ++i)
		{
			// Save the ith material.  Note that the MatD3D property does not have an ambient
			// value set when its loaded, so just set it to the diffuse value.
			Mtrl m;
			m.ambient   = d3dxmtrls[i].MatD3D.Ambient;
			m.diffuse   = d3dxmtrls[i].MatD3D.Diffuse;
			m.spec      = d3dxmtrls[i].MatD3D.Specular;
			m.specPower = d3dxmtrls[i].MatD3D.Power;
			meshModel->mtrls.push_back( m );
			
			// Check if the ith material has an associative texture
			if( d3dxmtrls[i].pTextureFilename != 0 )
			{
				// Yes, load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				int len = 0;
				len = (int)strlen(d3dxmtrls[i].pTextureFilename) + 1;
				wchar_t *ucString = new wchar_t[len];
				mbstowcs(ucString, d3dxmtrls[i].pTextureFilename, len);
				LPCWSTR filename = (LPCWSTR)ucString;
				D3DXCreateTextureFromFile(gd3dDevice, filename, &tex);
				// Save the loaded texture
				meshModel->texs.push_back( tex );
			}
			else
			{
				// No texture for the ith subset
				meshModel->texs.push_back( 0 );
			}
		}
	}
	modelList[fileName] = meshModel;
	SAFE_RELEASE(mtrlBuffer);
}

void MeshClass::Render(LPCWSTR fileName, IDirect3DDevice9* gd3dDevice, UINT i)
{
	modelList[fileName]->mesh->DrawSubset(i);
}

void MeshClass::ComputeBoundingBox(LPCWSTR fileName)
{
	VertexPNT* v = 0;
	modelList[fileName]->mesh->LockVertexBuffer(0, (void**)&v);
	D3DXComputeBoundingBox(&v->pos, modelList[fileName]->mesh->GetNumVertices(),
		modelList[fileName]->mesh->GetNumBytesPerVertex(), 
		&modelList[fileName]->boundingBox.minPt, &modelList[fileName]->boundingBox.maxPt);
	modelList[fileName]->mesh->UnlockVertexBuffer();
}

void MeshClass::ComputeBoundingSphere(LPCWSTR fileName)
{
	VertexPNT* v = 0;
	modelList[fileName]->mesh->LockVertexBuffer(0, (void**)&v);
	D3DXComputeBoundingSphere(&v->pos, modelList[fileName]->mesh->GetNumVertices(),
		modelList[fileName]->mesh->GetNumBytesPerVertex(), 
		&modelList[fileName]->boundingSphere.pos, &modelList[fileName]->boundingSphere.radius);
	modelList[fileName]->mesh->UnlockVertexBuffer();
}

void MeshClass::DeleteMesh(LPCWSTR fileName)
{
	modelList.erase(fileName);
}

IDirect3DTexture9* MeshClass::ReturnTexture(LPCWSTR fileName, UINT i)
{
	return modelList[fileName]->texs[i];
}
	
Mtrl MeshClass::ReturnMaterial(LPCWSTR fileName, UINT i)
{
	return modelList[fileName]->mtrls[i];
}

DWORD MeshClass::ReturnNumMtrls(LPCWSTR fileName)
{
	return modelList[fileName]->mtrls.size();
}