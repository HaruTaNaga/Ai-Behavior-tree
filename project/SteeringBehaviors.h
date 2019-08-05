/*=============================================================================*/
// Copyright 2017-2018 Elite Engine
// Authors: Matthieu Delaere, Thomas Goussaert
/*=============================================================================*/
// SteeringBehaviors.h: SteeringBehaviors interface and different implementations
/*=============================================================================*/
#ifndef ELITE_STEERINGBEHAVIORS
#define ELITE_STEERINGBEHAVIORS
#include <Exam_HelperStructs.h>

//-----------------------------------------------------------------
// Includes & Forward Declarations
//-----------------------------------------------------------------
//#include "SteeringHelpers.h"

using namespace Elite;

#pragma region **ISTEERINGBEHAVIOR** (BASE)
class ISteeringBehavior
{
public:
	ISteeringBehavior() = default;
	virtual ~ISteeringBehavior() = default;

	virtual SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) = 0;
/*
	template<class T, typename std::enable_if<std::is_base_of<ISteeringBehavior, T>::value>::type* = nullptr>
	T* As()
	{ return static_cast<T*>(this); }*/
	int temp_id = 0;
};
#pragma endregion

///////////////////////////////////////
//SEEK
//****
class SeekBehavior : public ISteeringBehavior
{
public:
	SeekBehavior() = default;
	virtual ~SeekBehavior() = default;

	//Seek Behaviour
	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;
	float time {}; 

	//Seek Functions
	virtual void SetTarget(const Vector2 pTarget) { m_pTargetRef = pTarget; }
 
	Vector2 m_pTargetRef = {};
};
class WanderingSeekBehavior : public ISteeringBehavior
{
public:
	WanderingSeekBehavior() = default;
	virtual ~WanderingSeekBehavior() = default;

	//Seek Behaviour
	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;
	float time{};
		float m_Offset = 6.f; //Offset (Agent Direction)
	float m_Radius = 4.f; //WanderRadius
	float m_AngleChange = ToRadians(45); //Max WanderAngle change per frame
	float m_WanderAngle = 0.f; //Internal
	//Seek Functions
	virtual void SetTarget(const Vector2 pTarget) { m_pTargetRef = pTarget; }

	Vector2 m_pTargetRef = {};
};
class FacedSeekBehavior : public ISteeringBehavior
{
public:
	FacedSeekBehavior() = default;
	virtual ~FacedSeekBehavior() = default;

	//Seek Behaviour
	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;

	//Seek Functions
	virtual void SetTarget(const Vector2 pTarget, const Vector2 pFacingTarget) { m_pTargetRef = pTarget; m_pFacingTargetRef = pFacingTarget; }

	Vector2 m_pTargetRef = {};
	Vector2 m_pFacingTargetRef = {};
};
class AvoidingSeekBehavior : public ISteeringBehavior
{
public:
	AvoidingSeekBehavior() = default;
	virtual ~AvoidingSeekBehavior() = default;

	//Seek Behaviour
	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;

	//Seek Functions
	virtual void SetTarget(const Vector2 pTarget, const Vector2 pFacingTarget) { m_pTargetRef = pTarget; m_pFacingTargetRef = pFacingTarget; }

	Vector2 m_pTargetRef = {};
	Vector2 m_pFacingTargetRef = {};
};
//class SeekWayPointBehavior : public ISteeringBehavior
//{
//public:
//	SeekBehavior() = default;
//	virtual ~SeekBehavior() = default;
//
//	//Seek Behaviour
//	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;
//
//	//Seek Functions
//	virtual void SetTarget(const Vector2 pTarget) { m_pTargetRef = pTarget; }
//protected:
//	Vector2 m_pTargetRef = {};
//};
class IdleBehavior : public ISteeringBehavior
{
public:
	IdleBehavior() = default;
	virtual ~IdleBehavior() = default;
	//Seek Behaviour
	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;

};
//////////////////////////
//WANDER
////******
//class Wander : public Seek
//{
//public:
//	Wander() = default;
//	virtual ~Wander() = default;
//
//	//Wander Behavior
//	SteeringPlugin_Output CalculateSteering(float deltaT, AgentInfo* pAgent) override;
//
//	void SetWanderOffset(float offset) { m_Offset = offset; }
//	void SetWanderRadius(float radius) { m_Radius = radius; }
//	void SetMaxAngleChange(float rad) { m_AngleChange = rad; }
//
//protected:
//	float m_Offset = 6.f; //Offset (Agent Direction)
//	float m_Radius = 4.f; //WanderRadius
//	float m_AngleChange = ToRadians(45); //Max WanderAngle change per frame
//	float m_WanderAngle = 0.f; //Internal
//
//private:
//	//void SetTarget(const TargetData* pTarget) override {} //Hide SetTarget, No Target needed for Wander
//};
/*
////////////////////////////
//PURSUIT
//******
class Pursuit : public Seek
{
public:
	Pursuit() = default;
	virtual ~Pursuit() = default;

	//Pursuit Behavior
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;

	//Pursuit Functions (Hides Seek::SetTarget)
	virtual void SetTarget(const TargetData* pTarget) override { m_pTargetRef = pTarget; }

protected:
	const TargetData* m_pTargetRef = nullptr;
};

/////////////////////////
//FLEE
//****
class Flee : public Seek
{
public:
	Flee() = default;
	virtual ~Flee() = default;

	//Seek Behavior
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;
};

//////////////////////////
//EVADE
//*****
class Evade : public Flee
{
public:
	Evade() = default;
	virtual ~Evade() = default;

	//Evade Behavior
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;

	//Evade Functions (Hides Flee::SetTarget)
	void SetTarget(const TargetData* pTarget) override { m_pTargetRef = pTarget; }

protected:
	const TargetData* m_pTargetRef = nullptr;
};

/////////////////////////////////////////
//ARRIVE
//******
class Arrive : public ISteeringBehavior
{
public:
	Arrive() = default;
	virtual ~Arrive() = default;

	//Arrive Behavior
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override;

	//Arrive Functions
	virtual void SetTarget(const TargetData* pTarget) { m_pTargetRef = pTarget; }
	void SetSlowRadius(float radius) { m_SlowRadius = radius; }
	void SetTargetRadius(float radius) { m_TargetRadius = radius; }

protected:

	const TargetData* m_pTargetRef = nullptr;
	float m_SlowRadius = 15.f;
	float m_TargetRadius = 3.f;
};


//Avoid Obstable
//******
struct Obstacle
{
	Elite::Vector2 center; 
	float radius; 
};

class AvoidObstacle : public ISteeringBehavior
{
public:
	AvoidObstacle(const vector<Obstacle>& obstacles)
		:m_Obstacles(obstacles) {} ;
	virtual ~AvoidObstacle() = default; 
	SteeringOutput CalculateSteering(float deltaT, SteeringAgent* pAgent) override; 

	void SetMaxAvoidanceForce(float max) { m_MaxAvoidanceForce = max;  }

protected: 
	vector<Obstacle> m_Obstacles = {};
	float m_MaxAvoidanceForce = 10.0f; 

};*/
#endif