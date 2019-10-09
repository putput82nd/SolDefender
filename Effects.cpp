#include"Effects.h"



EffectsClass::EffectsClass()
{

}

EffectsClass::~EffectsClass()
{

}

void EffectsClass::LoadEffects(LPCWSTR fxName, IDirect3DDevice9* gd3dDevice)
{
	FX* shader;
	shader = new FX;
	ID3DXBuffer* errors = 0;
	D3DXCreateEffectFromFile(gd3dDevice, fxName, 0, 0, 
		D3DXSHADER_DEBUG, 0, &shader->gFX, &errors);
	if(errors)
		MessageBox(0, (LPCWSTR)errors->GetBufferPointer(), 0, 0);

	// Obtain handles.
	shader->ghTech            = shader->gFX->GetTechniqueByName("Main");//later change all ParameterByName to ParameterBySemantic and use universal semantics variables for all handles
	shader->ghWVP             = shader->gFX->GetParameterBySemantic(0, "WORLDVIEWPROJECTION");
	shader->ghWorldInvTrans   = shader->gFX->GetParameterBySemantic(0, "WORLDINVERSETRANSPOSE");
	shader->ghLightVecW     = shader->gFX->GetParameterBySemantic(0, "DIRECTION");
	shader->ghEyePos          = shader->gFX->GetParameterBySemantic(0, "VIEWPOINT");
	shader->ghWorld           = shader->gFX->GetParameterBySemantic(0, "WORLD");
	shader->ghTex             = shader->gFX->GetParameterBySemantic(0, "TEXTURE");
	shader->ghDiffuseMtrl     = shader->gFX->GetParameterByName(0, "gDiffuseMtrl");
	shader->ghDiffuseLight    = shader->gFX->GetParameterByName(0, "gDiffuseLight");
	shader->ghAmbientMtrl	= shader->gFX->GetParameterByName(0, "gAmbientMtrl");
	shader->ghAmbientLight = shader->gFX->GetParameterByName(0, "gAmbientLight");
	shader->ghSpecularMtrl  = shader->gFX->GetParameterByName(0, "gSpecularMtrl");
	shader->ghSpecularLight = shader->gFX->GetParameterByName(0, "gSpecularLight");
	shader->ghSpecularPower = shader->gFX->GetParameterBySemantic(0, "SPECULARPOWER");
	fxList[fxName] = shader;
}

void EffectsClass::DeleteEffects(LPCWSTR fileName)
{
	fxList.erase(fileName);
}

void EffectsClass::Begin(LPCWSTR fileName, UINT numPasses)
{
	fxList[fileName]->gFX->Begin(&numPasses, 0);
}

void EffectsClass::BeginPass(LPCWSTR fileName, UINT i)
{
	fxList[fileName]->gFX->BeginPass(i);
}

void EffectsClass::SetCamPos(LPCWSTR fileName, D3DXVECTOR3 camPos)
{
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghEyePos, &camPos, sizeof(D3DXVECTOR3));
}

void EffectsClass::SetTech(LPCWSTR fileName)
{
	fxList[fileName]->gFX->SetTechnique(fxList[fileName]->ghTech);
}

void EffectsClass::SetFX(LPCWSTR fileName, D3DXMATRIX camViewProj, D3DXMATRIX world)
{
	fxList[fileName]->gFX->SetTechnique(fxList[fileName]->ghTech);
	
	D3DXMATRIX worldViewProj;
	worldViewProj = world * camViewProj;
	fxList[fileName]->gFX->SetMatrix(fxList[fileName]->ghWVP, &worldViewProj);
	
	D3DXMATRIX worldInvTrans;
	D3DXMatrixInverse(&worldInvTrans, 0, &world);
	D3DXMatrixTranspose(&worldInvTrans, &worldInvTrans);
	fxList[fileName]->gFX->SetMatrix(fxList[fileName]->ghWorldInvTrans, &worldInvTrans);
	fxList[fileName]->gFX->SetMatrix(fxList[fileName]->ghWorld, &world);
}

void EffectsClass::SetLight(LPCWSTR fileName, Light light)
{
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghLightVecW, &light.Position, sizeof(D3DXVECTOR3));
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghDiffuseLight, &light.Diffuse, sizeof(D3DXCOLOR));
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghAmbientLight, &light.Ambient, sizeof(D3DXCOLOR));
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghSpecularLight, &light.Specular, sizeof(D3DXCOLOR));
}

void EffectsClass::SetFXMaterial(LPCWSTR fileName, Mtrl mtrl)
{
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghDiffuseMtrl, &mtrl.diffuse, sizeof(D3DXCOLOR));
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghAmbientMtrl, &mtrl.ambient, sizeof(D3DXCOLOR));
	fxList[fileName]->gFX->SetValue(fxList[fileName]->ghSpecularMtrl, &mtrl.spec, sizeof(D3DXCOLOR));
	fxList[fileName]->gFX->SetFloat(fxList[fileName]->ghSpecularPower, mtrl.specPower);
}
	
void EffectsClass::SetFXTexture(LPCWSTR fileName, IDirect3DTexture9* tex)
{
	fxList[fileName]->gFX->SetTexture(fxList[fileName]->ghTex, tex);
	fxList[fileName]->gFX->CommitChanges();
}

void EffectsClass::End(LPCWSTR fileName)
{
	fxList[fileName]->gFX->End();
}

void EffectsClass::EndPass(LPCWSTR fileName)
{
	fxList[fileName]->gFX->EndPass();
}

void EffectsClass::Reset(LPCWSTR fileName)
{
	fxList[fileName]->gFX->OnResetDevice();
}