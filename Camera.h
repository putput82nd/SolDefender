#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>




class CameraClass
{
protected:
	void BuildView();
	void BuildWorldFrustumPlanes();
	D3DXMATRIX	camView;
	D3DXMATRIX	camProj;
	D3DXMATRIX	camViewProj;
	// Relative to world space.
	D3DXVECTOR3 camPos;
	D3DXVECTOR3 camRight;
	D3DXVECTOR3 camUp;
	D3DXVECTOR3 camLook;
	// Frustum Planes
	D3DXPLANE camFrustumPlanes[6]; // [0] = near
	                             // [1] = far
	                             // [2] = left
	                             // [3] = right
	                             // [4] = top
	                             // [5] = bottom
public:
	CameraClass();
	~CameraClass();
	const D3DXMATRIX& ReturnView() const;
	const D3DXMATRIX& ReturnProj() const;
	const D3DXMATRIX& ReturnViewProj() const;
	const D3DXVECTOR3& ReturnRight() const;
	const D3DXVECTOR3& ReturnUp() const;
	const D3DXVECTOR3& ReturnLook() const;
	void SetPosition(float position[3]);
	D3DXVECTOR3 ReturnPosition();
	void LookAt(float pos[3], float target[3], float up[3]);
	void SetLens(float fov, float aspect, float nearZ, float farZ);
	// Box coordinates should be relative to world space.
	//bool IsVisible(const AABB& box)const;
	void Update();
};
#endif