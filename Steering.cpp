#include"Steering.h"



Steering::Steering()
{

}

Steering::~Steering()
{

}

SteeringOutput Steering::Seek(GameObject* self, GameObject* target)
{
	SteeringOutput steering;
	steering.linear = target->GetPosition() - self->GetPosition();
	if(D3DXVec3LengthSq(&steering.linear) > 0)
	{
		D3DXVec3Normalize(&steering.linear, &steering.linear); 
		steering.linear *= self->GetMaxAcceleration();//being removed to have done by physics
	}
	steering.angular = 0;
	return steering;
}

SteeringOutput Steering::Flee(GameObject* self, GameObject* target)
{
	SteeringOutput steering;
	steering.linear = self->GetPosition() - target->GetPosition();
	if(D3DXVec3LengthSq(&steering.linear) > 0)
	{
		D3DXVec3Normalize(&steering.linear, &steering.linear); 
		steering.linear *= self->GetMaxAcceleration();//being removed to have done by physics
	}
	steering.angular = 0;
	return steering;
}

SteeringOutput Steering::Arrive(GameObject* self, GameObject* target)
{
	float targetRadius;
	float slowRadius;
	float timeToTarget = 0.1;
	D3DXVECTOR3 direction;
	float distance;
	float targetSpeed;
	SteeringOutput steering;
	direction = target->GetPosition() - self->GetPosition();
	distance = D3DXVec3Length(&direction);
	if(distance < targetRadius)
	{
		steering.linear[0] = 0, steering.linear[1] = 0, steering.linear[2] = 0;
		steering.angular = 0;
		return steering;
	}
	if(distance > slowRadius)
		targetSpeed = self->GetMaxSpeed();
	else
		targetSpeed = self->GetMaxSpeed() * distance / slowRadius;
	D3DXVec3Normalize(&direction, &direction);
	steering.linear /= timeToTarget;
	//being removed to have done by physics
	if(D3DXVec3Length(&steering.linear) > self->GetMaxAcceleration())
	{
		D3DXVec3Length(&steering.linear);
		steering.linear *= self->GetMaxAcceleration();
	}
	steering.angular = 0;
	return steering;
}

SteeringOutput Steering::Pursue(GameObject* self, GameObject* target)
{
	D3DXVECTOR3 targetVelocity;
	D3DXVECTOR3 direction;
	float distance;
	float speed;
	float prediction, maxPrediction;
	direction = target->GetPosition()- self->GetPosition();
	speed = D3DXVec3Length(&D3DXVECTOR3(self->GetVelocity()));
	if(speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		prediction = distance / speed;
	targetVelocity = self->GetVelocity() * prediction;
	target->SetPosition(targetVelocity);
	return Seek(self, target);
}

SteeringOutput Steering::Evade(GameObject* self, GameObject* target)
{
	D3DXVECTOR3 targetVelocity;
	D3DXVECTOR3 direction;
	float distance;
	float speed;
	float prediction, maxPrediction;
	direction = target->GetPosition() - self->GetPosition();
	speed = D3DXVec3Length(&self->GetVelocity());
	if(speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		prediction = distance / speed;
	target->SetPosition(target->GetVelocity() * prediction);
	return Flee(self, target);
}

SteeringOutput Steering::VelocityMatch(GameObject* self, GameObject* target)
{

	float timeToTarget = 0.1;
	SteeringOutput steering;
	steering.linear = target->GetVelocity() - self->GetVelocity();
	steering.linear /= timeToTarget;
	//being removed to have done by physics
	if(D3DXVec3Length(&steering.linear) > self->GetMaxAcceleration())
		D3DXVec3Normalize(&steering.linear, &steering.linear);
	steering.linear *= self->GetMaxAcceleration();
	steering.angular = 0;
	return steering;
}
/*
SteeringOutput Steering::FollowPath(GameObject* self, string* pathName)
{
	GameObject* target;
	target->SetPosition(path.GetNextPathNode(self->GetPosition(), pathName));
	return Seek(self, target);
}
*/
SteeringOutput Steering::Seperation(GameObject* self, vector<GameObject*> targetList)
{
	float threshold;
	float decayCoeff;
	D3DXVECTOR3 direction;
	float distance;
	float strength;
	SteeringOutput steering;

	for(int i = 0; i < targetList.size(); i++)
	{
		direction = targetList[i]->GetPosition() - self->GetPosition();
		distance = D3DXVec3Length(&direction);
		if(distance < threshold)
		{
			strength = min(decayCoeff / (distance * distance), self->GetMaxAcceleration());
		}
		D3DXVec3Normalize(&direction, &direction);
		steering.linear[0] =+ strength + direction[0];
		steering.linear[1] =+ strength + direction[1];
		steering.linear[2] =+ strength + direction[2];
	}
	return steering;
}

SteeringOutput Steering::CollisionAvoidance(GameObject* self, vector<GameObject*> targetList)
{
	SteeringOutput steering;
	float shortestTime = INFINITY;
	GameObject* firstTarget = NULL;
	float firstMinSeperation;
	float firstDistance;
	float minSeperation;
	D3DXVECTOR3 firstRelativePos;
	D3DXVECTOR3 firstRelativeVel;
	D3DXVECTOR3 relativePos;
	D3DXVECTOR3 relativeVel;
	float distance;
	float relativeSpeed;
	float timeToCollision;

	float collisionRadius = 3;//use this for now and set it universally for all object until AABB is used
	for(int i = 0; i < targetList.size(); i++)
	{
		relativePos = targetList[i]->GetPosition() - self->GetPosition();
		relativeVel = targetList[i]->GetVelocity() - self->GetVelocity();
		relativeSpeed = D3DXVec3Length(&relativeVel);
		timeToCollision = (D3DXVec3Dot(&relativePos, &relativeVel) / relativeSpeed * relativeSpeed);//need to check my math if I should use cross or dot product for this
		distance = D3DXVec3Length(&relativePos);
		minSeperation = distance - relativeSpeed * shortestTime;
		if(minSeperation > 2 * collisionRadius)
			continue;
		if(timeToCollision > 0 && timeToCollision < shortestTime)
		{
			shortestTime = timeToCollision;
			firstTarget = targetList[i];
			firstMinSeperation = minSeperation;
			firstDistance = distance;
			firstRelativePos = relativePos;
			firstRelativeVel = relativeVel;
		}
		if(firstTarget == NULL)
		{
			steering.linear[0] = 0, steering.linear[1] = 0, steering.linear[2] = 0;
			steering.angular = 0;
			return steering;
		}
		if(firstMinSeperation <= 0 || distance < 2 * collisionRadius)
		{
			relativePos = firstTarget->GetPosition() - self->GetPosition();
		}
		else
			relativePos = firstRelativePos + firstRelativeVel * shortestTime;
		D3DXVec3Normalize(&relativePos, &relativePos);
		steering.linear = relativePos * self->GetMaxAcceleration();//being removed to be done by physics
		return steering;
	}
}

SteeringOutput Steering::ObstacleAvoidance(GameObject* self)//currently only using 1 ray out of 5
{
	CollisionDetector collisionDetector;
	Collision collision;
	float avoidanceRadius;
	float lookAhead;
	D3DXVECTOR3 temp;
	D3DXVECTOR3 rayVector[5];	//0 = direction game object is facing
								//1 = to left of game object
								//2 = right of game object
								//3 = below game object
								//4 = above game object
	GameObject* target;
	SteeringOutput steering;

	target = self;
	rayVector[0] = self->GetVelocity();


	for(int i = 0; i < 1; i++)//only using one ray currently, adjust to the number of rays used
	{
		D3DXVec3Normalize(&rayVector[i], &rayVector[i]);
		rayVector[i] *= lookAhead;
	}
	
	int j = 0;
	for(int i = 0; i < 1; i++)//only using ray currently
	{
		collision = collisionDetector.GetCollision(temp, rayVector[i]);
		temp =+ collision.position + collision.normal * avoidanceRadius;
		j++;
	}
	if(temp[0] == 0 && temp[1] == 0 && temp[2] ==0)
	{
		steering.linear[0] = 0, steering.linear[1] = 0, steering.linear[2] = 0;
		steering.angular = 0;
		return steering;
	}
	temp /= j;
	target->SetPosition(temp);
	steering = Seek(self, target);
	return steering;
}

Collision CollisionDetector::GetCollision(D3DXVECTOR3 position, D3DXVECTOR3 moveAmount)
{
	Collision collision;
	return collision;
}













/*
SteeringOutput Steering::Align(GameObject* self, GameObject* target)
{
	float targetRadius;
	float slowRadius;
	float timeToTarget = 0.1;
	float rotation[4];
	float rotationDirection;
	float rotationSize;
	float targetRotation;
	float angularAcceleration;
	float targetOrientation[4];
	
	SteeringOutput steering;
	targetOrientation[0] = 
	rotation = target.orientation - self.orientation;
	
	//rotation = =mapToRange();//need a function here to have the result between -pi and pi
	rotationSize = abs(rotationDirection);
	if(rotationSize < targetRadius)
		return;
	if(rotationSize > slowRadius)
		targetRotation = self.maxRotation;
	else
		targetRotation = self.maxRotation * rotationSize / slowRadius;
	targetRotation *= rotation / rotationSize;
	steering.angular = targetRotation - self.rotation;
	steering.angular /= timeToTarget;
	angularAcceleration = abs(steering.angular);
	//being removed to have done by physics
	//if(angularAcceleration > self.maxAngularAcceleration)
	//{
		//steering.angular /= angularAcceleration;
		//steering.angular *= self.maxAngularAcceleration;
	//}
	
	steering.angular = 0;
	return steering;
}*/










/*
SteeringOutput Steering::Wander(GameObject* self)
{
	float* offset;
	float* volatility;//adjustable
	float angle;
	float selfTemp;
	volatility[0] = 10, volatility[1] = 0, volatility[2] = 0;
	GameObject target;
	SteeringOutput steering;
	volatility =+ self->GetPosition();
	target.SetPosition(volatility);
	offset[0] = volatility[0] - self->GetPosition()[0];
	offset[1] = volatility[1] - self->GetPosition()[1];
	offset[2] = volatility[2] - self->GetPosition()[2];

	
	return steering;
}



SteeringOutput Steering::Face(GameObject self, GameObject target)
{
	D3DXVECTOR3 direction;
	direction = target.position - self.position;
	if(D3DXVec3Length(&direction) == 0)
		return;
	target.orientation = atan2(-direction.x, direction.z);
	return Align(self, target);
}

SteeringOutput Steering::LookWhereYouAreGoing(GameObject self)
{
	GameObject target;
	target = self;
	Steering steeering;
	if(D3DXVec3Length(&self.velocity) == 0)
		return;
	target.orientation = atan2(-self.velocity.x, self.velocity.z);
	return Align(self, target);
}

SteeringOutput Steering::Flocking(GameObject self, vector<GameObject*> targetList)
{
	GameObject target;
	SteeringOutput steering;
	target = self;
	Seperation(self, targetList);
	for(int i = 0; i < targetList.size(); i++)
	{
		target.velocity += targetList[i]->velocity;
		target.position += targetList[i]->position;
	}
	target.velocity / targetList.size() + 1;
	target.position / targetList.size() + 1;
	steering = Align(self, target);
	steering = VelocityMatch(self, target);
	steering = Arrive(self, target);
	return steering;
}
*/