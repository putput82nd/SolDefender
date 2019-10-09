#pragma once
//used for rotational calculations, mainly for 3D
#define PI ((float)3.141592654f)
#define ToRadian(degree) ((degree) * (PI / 180.0f))
#define ToDegree(radian) ((radian) * (180.0f / PI))
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include<vector>
#include"GameObjectClass.h"
//#include"Path.h"
using namespace std;


struct SteeringOutput
{
	D3DXVECTOR3 linear;
	float angular;
};

struct Collision
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	float		penDepth;
	float		interpen;//assume this is given to us
	float		friction; //assume this is given to us
};

struct CollisionDetector
{
	Collision GetCollision(D3DXVECTOR3 position, D3DXVECTOR3 moveAmount);
};

class Steering
{
private:
	//Path path;
public:
	Steering();
	~Steering();
	//basic steering
	SteeringOutput Seek(GameObject* self, GameObject* target);
	SteeringOutput Flee(GameObject* self, GameObject* target);
	SteeringOutput Arrive(GameObject* self, GameObject* target);
	SteeringOutput Align(GameObject* self, GameObject* target);
	SteeringOutput VelocityMatch(GameObject* self, GameObject* target);
	SteeringOutput Seperation(GameObject* self, vector<GameObject*> targetList);
	SteeringOutput CollisionAvoidance(GameObject* self, vector<GameObject*> targetList);
	SteeringOutput ObstacleAvoidance(GameObject* self);
	//steering functions using basic steering
	SteeringOutput Wander(GameObject* self);
	SteeringOutput Pursue(GameObject* self, GameObject* target);
	SteeringOutput Evade(GameObject* self, GameObject* target);
	SteeringOutput Face(GameObject* self, GameObject* target);
	SteeringOutput LookWhereYouAreGoing(GameObject* self);
	//SteeringOutput FollowPath(GameObject self, string pathName);
	//behaviors using multiple steering functions
	SteeringOutput Flocking(GameObject* self, vector<GameObject*> targetList);
};