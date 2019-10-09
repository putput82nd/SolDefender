#include "Camera.h"





CameraClass::CameraClass()
{
	D3DXMatrixIdentity(&camView);
	D3DXMatrixIdentity(&camProj);
	D3DXMatrixIdentity(&camViewProj);

	camPos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	camUp    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camLook  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CameraClass::~CameraClass()
{

}

const D3DXMATRIX& CameraClass::ReturnView() const
{
	return camView;
}

const D3DXMATRIX& CameraClass::ReturnProj() const
{
	return camProj;
}

const D3DXMATRIX& CameraClass::ReturnViewProj() const
{
	return camViewProj;
}

const D3DXVECTOR3& CameraClass::ReturnRight() const
{
	return camRight;
}

const D3DXVECTOR3& CameraClass::ReturnUp() const
{
	return camUp;
}

const D3DXVECTOR3& CameraClass::ReturnLook() const
{
	return camLook;
}

void CameraClass::SetPosition(float position[3])
{
	camPos.x = position[0];
	camPos.y = position[1];
	camPos.z = position[2];
}
	
D3DXVECTOR3 CameraClass::ReturnPosition()
{
	return camPos;
}

void CameraClass::LookAt(float pos[3], float target[3], float up[3])
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 upper;
	D3DXVECTOR3 lookWhere;
	position.x = pos[0];
	position.y = pos[1];
	position.z = pos[2];
	lookWhere.x = target[0];
	lookWhere.y = target[1];
	lookWhere.z = target[2];
	upper.x = up[0];
	upper.x = up[1];
	upper.x = up[2];
	D3DXVECTOR3 L = lookWhere - position;
	D3DXVec3Normalize(&L, &L);

	D3DXVECTOR3 R;
	D3DXVec3Cross(&R, &upper, &L);
	D3DXVec3Normalize(&R, &R);

	D3DXVECTOR3 U;
	D3DXVec3Cross(&U, &L, &R);
	D3DXVec3Normalize(&U, &U);

	camPos   = pos;
	camRight = R;
	camUp    = U;
	camLook  = L;

	BuildView();
	BuildWorldFrustumPlanes();

	camViewProj = camView * camProj;
}

void CameraClass::SetLens(float fov, float aspect, float nearZ, float farZ)
{
	D3DXMatrixPerspectiveFovLH(&camProj, fov, aspect, nearZ, farZ);
	BuildWorldFrustumPlanes();
	camViewProj = camView * camProj;
}

/*
bool CameraClass::IsVisible(const AABB& box)const
{
	// Test assumes frustum planes face inward.

	D3DXVECTOR3 P;
	D3DXVECTOR3 Q;

	//      N  *Q                    *P
	//      | /                     /
	//      |/                     /
	// -----/----- Plane     -----/----- Plane    
	//     /                     / |
	//    /                     /  |
	//   *P                    *Q  N
	//
	// PQ forms diagonal most closely aligned with plane normal.

	// For each frustum plane, find the box diagonal (there are four main
	// diagonals that intersect the box center point) that points in the
	// same direction as the normal along each axis (i.e., the diagonal 
	// that is most aligned with the plane normal).  Then test if the box
	// is in front of the plane or not.
	for(int i = 0; i < 6; ++i)
	{
		// For each coordinate axis x, y, z...
		for(int j = 0; j < 3; ++j)
		{
			// Make PQ point in the same direction as the plane normal on this axis.
			if( mFrustumPlanes[i][j] >= 0.0f )
			{
				P[j] = box.minPt[j];
				Q[j] = box.maxPt[j];
			}
			else 
			{
				P[j] = box.maxPt[j];
				Q[j] = box.minPt[j];
			}
		}

		// If box is in negative half space, it is behind the plane, and thus, completely
		// outside the frustum.  Note that because PQ points roughly in the direction of the 
		// plane normal, we can deduce that if Q is outside then P is also outside--thus we
		// only need to test Q.
		if( D3DXPlaneDotCoord(&mFrustumPlanes[i], &Q) < 0.0f  ) // outside
			return false;
	}
	return true;
}
*/

void CameraClass::Update()
{
	/*
	// Find the net direction the camera is traveling in (since the
	// camera could be running and strafing).
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
	if( gDInput->keyDown(DIK_W) )
		dir += camLookW;
	if( gDInput->keyDown(DIK_S) )
		dir -= camLookW;
	if( gDInput->keyDown(DIK_D) )
		dir += camRightW;
	if( gDInput->keyDown(DIK_A) )
		dir -= camRightW;

	// Move at mSpeed along net direction.
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 newPos = camPosW + dir*camSpeed*dt;
	
	
	camPosW = newPos;
	
	

	// We rotate at a fixed speed.
	float pitch  = gDInput->mouseDY() / 150.0f;
	float yAngle = gDInput->mouseDX() / 150.0f;


	// Rotate camera's look and up vectors around the camera's right vector.
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &camRightW, pitch);
	D3DXVec3TransformCoord(&camLookW, &camLookW, &R);
	D3DXVec3TransformCoord(&camUpW, &camUpW, &R);


	// Rotate camera axes about the world's y-axis.
	D3DXMatrixRotationY(&R, yAngle);/
	D3DXVec3TransformCoord(&camRightW, &camRightW, &R);
	D3DXVec3TransformCoord(&camUpW, &camUpW, &R);
	D3DXVec3TransformCoord(&camLookW, &camLookW, &R);
	*/
	// Rebuild the view matrix to reflect changes.
	BuildView();
	BuildWorldFrustumPlanes();

	camViewProj = camView * camProj;
}

void CameraClass::BuildView()
{
	D3DXMatrixLookAtLH(&camView, &camPos, &camLook, &camUp);
}

void CameraClass::BuildWorldFrustumPlanes()
{
	// Note: Extract the frustum planes in world space.
	D3DXMATRIX VP = camView * camProj;

	D3DXVECTOR4 col0(VP(0,0), VP(1,0), VP(2,0), VP(3,0));
	D3DXVECTOR4 col1(VP(0,1), VP(1,1), VP(2,1), VP(3,1));
	D3DXVECTOR4 col2(VP(0,2), VP(1,2), VP(2,2), VP(3,2));
	D3DXVECTOR4 col3(VP(0,3), VP(1,3), VP(2,3), VP(3,3));

	// Planes face inward.
	camFrustumPlanes[0] = (D3DXPLANE)(col2);        // near
	camFrustumPlanes[1] = (D3DXPLANE)(col3 - col2); // far
	camFrustumPlanes[2] = (D3DXPLANE)(col3 + col0); // left
	camFrustumPlanes[3] = (D3DXPLANE)(col3 - col0); // right
	camFrustumPlanes[4] = (D3DXPLANE)(col3 - col1); // top
	camFrustumPlanes[5] = (D3DXPLANE)(col3 + col1); // bottom

	for(int i = 0; i < 6; i++)
		D3DXPlaneNormalize(&camFrustumPlanes[i], &camFrustumPlanes[i]);
}