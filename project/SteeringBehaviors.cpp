//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

//Includes
#include "SteeringBehaviors.h"
#include <chrono>


//SEEK
//****
SteeringPlugin_Output SeekBehavior::CalculateSteering(float deltaT, AgentInfo* pAgent)
{
	SteeringPlugin_Output steering = {};
//	time += deltaT; 

	//TODO: insert logic
	auto linearVelocity = m_pTargetRef - pAgent->Position; 
	linearVelocity.Normalize(); 
	linearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	steering.LinearVelocity = linearVelocity; 
	//steering.AutoOrientate = false; 
//	steering.AngularVelocity =  0.2*sin(time);

//	steering.AngularVelocity += acos(linearVelocity.y);
	//steering.LinearVelocity = 
//	steering.AutoOrientate = false;
	//steering.AngularVelocity = 1;
	return steering;
}
SteeringPlugin_Output FacedSeekBehavior::CalculateSteering(float deltaT, AgentInfo * pAgent)
{
	SteeringPlugin_Output steering = {};

	//TODO: insert logic
	auto linearVelocity = m_pTargetRef - pAgent->Position;
	linearVelocity.Normalize();
	//linearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	steering.LinearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	steering.LinearVelocity = Vector2( -steering.LinearVelocity.y, -steering.LinearVelocity.x );
	steering.AutoOrientate = false; 
	auto Orientation = fmod(pAgent->Orientation, M_PI ) ;

	//std::cout << "Velocity :" << linearVelocity.x <<  " , " << linearVelocity.y << std::endl;
	//std::cout << "Orientation :" << Orientation ;
//	std::cout << "OrietationVector :  " << x << " , "<< y << std::endl; 

	auto vecToTarget = m_pFacingTargetRef - pAgent->Position; 
	vecToTarget.Normalize(); 
//	steering.LinearVelocity += Vector2(-vecToTarget.y* 0.8 * pAgent->MaxLinearSpeed, -vecToTarget.x* 0.8 * pAgent->MaxLinearSpeed);
//	steering.LinearVelocity += Vector2(-vecToTarget.y* 0.8 * pAgent->MaxLinearSpeed, vecToTarget.x* 0.8 * pAgent->MaxLinearSpeed);

	steering.LinearVelocity.Normalize(); 
	steering.LinearVelocity *= .6 * pAgent->MaxLinearSpeed;
//	auto  angle = acos(-vecToTarget.y); 
	//auto angle = acos(Dot(linearVelocity, vecToTarget)); 
	//if (vecToTarget.x < 0)
	//	angle = -angle;
	Vector2 vector1 = { 0,-1 }; 
	Vector2 vector2 = vecToTarget;
	auto angle = atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x);
	if (angle > M_PI) { angle -= 2 * M_PI; }
	else if (angle <= -M_PI) { angle += 2 * M_PI; }
	//std::cout << "   // Angle :" << angle ; 
	angle -= Orientation;
	//std::cout << "// difference between angles : " << angle << std::endl;
	//if (Orientation < 0)
	//	angle = -angle; 

	//if(vecToTarget.x > 0)
	{
		
	
	 if ( fmod(angle, 3.6)  >  0.03 )
	steering.AngularVelocity = pAgent->MaxLinearSpeed;
	 else if (fmod(angle,3.6) < -0.03 )
		 steering.AngularVelocity = -pAgent->MaxLinearSpeed;
	 else
	 {
		 std::cout << "aiming at enemy " << std::endl; 
		 steering.AngularVelocity = -0;
	 }
	}
	

	return steering;
}

//SteeringPlugin_Output SeekWayPointBehavior::CalculateSteering(float deltaT, AgentInfo* pAgent)
//{
//	SteeringPlugin_Output steering = {};
//
//	//TODO: insert logic
//	auto linearVelocity = m_pTargetRef - pAgent->Position;
//	linearVelocity.Normalize();
//	linearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
//	steering.LinearVelocity = linearVelocity;
//
//	return steering;
//}
//
////WANDER (base> SEEK)
////******
//SteeringPlugin_Output WanderBehavior::CalculateSteering(float deltaT, AgentInfo* pAgent)
//{
//	//TODO: insert logic
//	//HINT: Don't forget to set Seek:m_pTargetRef
//SteeringPlugin_Output steering = {};
//	return steering;
//
//	//Calculate WanderOffset
//	//auto offset = pAgent->GetLinearVelocity(); 
//	//offset.Normalize(); 
//	//offset *= m_Offset; 
//
//	////Wander circle offset
//	//auto circleOffset = Elite::Vector2(cos(m_WanderAngle) * m_Radius, sin(m_WanderAngle) * m_Radius); 
//
//
//
//
//	//m_WanderAngle += randomFloat() * m_AngleChange - (m_AngleChange * 0.5f); 
//
//	////m_WanderAngle += randomFloat() * 2;
//
//	//auto newTarget = TargetData(pAgent->GetPosition() + offset + circleOffset); 
//	////auto pos = offset + circleOffset;
//	//Seek::m_pTargetRef = &newTarget; 
//
////if (pAgent->CanRenderBehavior())
////	{
////		auto pos = pAgent->GetPosition(); 
////		DEBUGRENDERER2D->DrawSegment(pos, pos + offset, { 0,0,1 }); 
////	//	DEBUGRENDERER2D->DrawCircle(pos + offset, m_Radius, { 0,0,0.66f }, -.7f); 
////	//	DEBUGRENDERER2D->DrawPoint(pos + offset + circleOffset, 0.5f, { 0,1,0 }, -.7f); 
////
////	}
//	//Return Seek Output (with our wander target)
//	//return SeekBehavior::CalculateSteering(deltaT, pAgent);
//}

////PURSUIT (base> SEEK)
////*******
//SteeringPlugin_Output Pursuit::CalculateSteering(float deltaT, SteeringAgent* pAgent)
//{
//	//TODO: insert logic
//	//HINT: Calculate the future position of the target
//	//(based on the current distance between agent and target)
//	auto targetVelocity = m_pTargetRef->LinearVelocity;
//	auto displacement = m_pTargetRef->Position - pAgent->GetPosition(); 
//	auto distance = sqrt((displacement.x * displacement.x) + (displacement.y * displacement.y)); 
//
//	auto newTarget = TargetData((m_pTargetRef->Position + targetVelocity) * distance); 
//	Seek::m_pTargetRef = &newTarget;
//	return Seek::CalculateSteering(deltaT, pAgent);
//}
//
////FLEE
////****
//SteeringPlugin_Output Flee::CalculateSteering(float deltaT, SteeringAgent* pAgent)
//{
//	SteeringOutput steering = {};
//
//	//TODO: insert logic
//	//HINT: Inverse of Seek...
//	auto linearVelocity = m_pTargetRef->Position - pAgent->GetPosition();
//	linearVelocity.Normalize();
//	linearVelocity = linearVelocity * -1; 
//	linearVelocity = linearVelocity * pAgent->GetMaxLinearSpeed();
//	steering.LinearVelocity = linearVelocity;
//
//	return steering;
//}
//
////EVADE (base> FLEE)
////*****
//SteeringPlugin_Output Evade::CalculateSteering(float deltaT, SteeringAgent* pAgent)
//{
//	//TODO: insert logic
//	//HINT: Calculate the future position of the target
//	//(based on the current distance between agent and target)
//	auto targetVelocity = m_pTargetRef->LinearVelocity;
//	auto displacement = m_pTargetRef->Position - pAgent->GetPosition();
//	auto distance = sqrt((displacement.x * displacement.x) + (displacement.y * displacement.y));
//
//	auto newTarget = TargetData((m_pTargetRef->Position + targetVelocity) * distance);
//	Flee::m_pTargetRef = &newTarget;
//	return Flee::CalculateSteering(deltaT, pAgent);
//}
//
////ARRIVE
////******
//SteeringOutput Arrive::CalculateSteering(float deltaT, SteeringAgent* pAgent)
//{
//	SteeringOutput steering = {};
//
//	//TODO: insert logic
//	//HINT: Calculate the distance between the agent and target
//	//Rampdown the desired velocity when entering the slowdown area (m_SlowRadius)
//	//auto distancevec = m_pTargetRef->Position - pAgent->GetPosition(); 
//	auto distance = Distance(m_pTargetRef->Position, pAgent->GetPosition());
//	if (distance < m_SlowRadius)
//	{
//		auto linearVelocity = m_pTargetRef->Position - pAgent->GetPosition();
//		steering.LinearVelocity = linearVelocity * ((m_SlowRadius - distance) / m_SlowRadius);
//	}
//	return steering;
//}
//
//SteeringOutput AvoidObstacle::CalculateSteering(float deltaT, SteeringAgent * pAgent)
//{
//	return SteeringOutput();
//}

SteeringPlugin_Output IdleBehavior::CalculateSteering(float deltaT, AgentInfo * pAgent )
{
	 SteeringPlugin_Output r = SteeringPlugin_Output();
	// r.LinearVelocity = Elite::Vector2{ 0,0 };
	 return r; 
}

SteeringPlugin_Output WanderingSeekBehavior::CalculateSteering(float deltaT, AgentInfo * pAgent)
{
	SteeringPlugin_Output steering = {};
	//	time += deltaT; 

		//TODO: insert logic
	
	//steering.AutoOrientate = false; 
//	steering.AngularVelocity =  0.2*sin(time);



	auto offset = pAgent->LinearVelocity; 
	offset.Normalize(); 
	offset *= m_Offset; 

	//Wander circle offset
	auto circleOffset = Elite::Vector2(cos(m_WanderAngle) * m_Radius, sin(m_WanderAngle) * m_Radius); 
	m_WanderAngle += randomFloat() * m_AngleChange - (m_AngleChange * 0.5f); 
	auto newTarget = pAgent->Position + offset + circleOffset; 
	//auto pos = offset + circleOffset;
	auto wanderTarget = newTarget; 

	//Return Seek Output (with our wander target)


	auto linearVelocity = m_pTargetRef - pAgent->Position;
	//linearVelocity = wanderTarget - pAgent->Position; 
	linearVelocity.Normalize();
	linearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	steering.LinearVelocity = linearVelocity;

//	steering.AngularVelocity += acos(linearVelocity.y);
	//steering.LinearVelocity = 
//	steering.AutoOrientate = false;
	//steering.AngularVelocity = 1;
	return steering;
	return SteeringPlugin_Output();
}

SteeringPlugin_Output AvoidingSeekBehavior::CalculateSteering(float deltaT, AgentInfo * pAgent)
{
	SteeringPlugin_Output steering = {};
	
	//TODO: insert logic
	auto linearVelocity = m_pTargetRef - pAgent->Position;
	linearVelocity.Normalize();
	//linearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	steering.LinearVelocity = linearVelocity * pAgent->MaxLinearSpeed;
	//steering.LinearVelocity = Vector2(-steering.LinearVelocity.y, steering.LinearVelocity.x);
	//steering.AutoOrientate = false;
	auto Orientation = fmod(pAgent->Orientation, M_PI);

	//std::cout << "Velocity :" << linearVelocity.x <<  " , " << linearVelocity.y << std::endl;
	//std::cout << "Orientation :" << Orientation ;
//	std::cout << "OrietationVector :  " << x << " , "<< y << std::endl; 

	auto vecToTarget = m_pFacingTargetRef - pAgent->Position;
	vecToTarget.Normalize();
	//steering.LinearVelocity += Vector2(-vecToTarget.y* 0.8 * pAgent->MaxLinearSpeed, -vecToTarget.x* 0.8 * pAgent->MaxLinearSpeed);
	steering.LinearVelocity += Vector2(vecToTarget.y* 1.5 * pAgent->MaxLinearSpeed, -vecToTarget.x* 1.5 * pAgent->MaxLinearSpeed);
	if (pAgent->LinearVelocity.Magnitude() < 1.5)
		steering.LinearVelocity -= Vector2(vecToTarget.y* 1.5 * pAgent->MaxLinearSpeed, -vecToTarget.x* 1.5 * pAgent->MaxLinearSpeed);

	steering.LinearVelocity.Normalize();
	steering.LinearVelocity *=  pAgent->MaxLinearSpeed;


	return steering;
}
