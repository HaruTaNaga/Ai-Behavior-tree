/*=============================================================================*/
// Copyright 2017-2018 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// Behaviors.h: Implementation of certain reusable behaviors for Behavior Tree Demo
/*=============================================================================*/
#ifndef ELITE_APPLICATION_BEHAVIOR_TREE_BEHAVIORS
#define ELITE_APPLICATION_BEHAVIOR_TREE_BEHAVIORS
//-----------------------------------------------------------------
// Includes & Forward Declarations
//-----------------------------------------------------------------
#include "stdafx.h"
#include "EliteMath/EMath.h"
#include "EBehaviorTree.h"
#include "SteeringBehaviors.h"


//-----------------------------------------------------------------
// Behaviors
//-----------------------------------------------------------------
//TODO: insert code

inline bool HasTarget(Elite::Blackboard * pBlackboard)
{
	//std::cout << "check if has target" << std::endl; 
	bool hasTarget = false; 
	const bool dataAvailable = pBlackboard->GetData("TargetSet", hasTarget); 
	if (!dataAvailable)
	{
		//std::cout << "Failed to obtain :" << "TargetSet" << "From Btree in" << " HasTarget" << std::endl;
		return false;
	}
	if (hasTarget)
		//std::cout << "Has Target" << std::endl; 
	return hasTarget; 

}
inline bool DoesNotHaveTarget(Elite::Blackboard * pBlackboard)
{

	bool doesnothasTarget = true;
	const bool dataAvailable = pBlackboard->GetData("TargetSet", doesnothasTarget);
	if (!dataAvailable)
	{
		//std::cout << "Failed to obtain :" << "TargetSet" << "From Btree" << " DoesnotHasTarget" << std::endl;
		return false;
	}
	

	return !doesnothasTarget;

}

inline bool LowHP(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	AgentInfo pAgent;
	if(! pBlackboard->GetData("Agent", pAgent)) return false; 
	return  (pAgent.Health < 7);
	
}
inline bool rFalse(Elite::Blackboard * pBlackboard)
{
	return false; 
}
inline bool StuckInHouse(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	float  houseTimer{}; 
	pBlackboard->GetData("HouseTimer", houseTimer);
	return houseTimer > 20;  
	                                     

}
inline bool NotStuckInHouse(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 
	bool isHouseSet = false; 

	if (!isHouseSet)
	{
		std::cout <<  "check in target house :: NO HOUSE SET" << std::endl;
			return false; 
	}
	float  houseTimer{};
	pBlackboard->GetData("HouseTimer", houseTimer);
	return houseTimer < 10;


}
inline bool VeryLowHP(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	AgentInfo pAgent;
	if (!pBlackboard->GetData("Agent", pAgent)) return false;
	return  (pAgent.Health < 4.9);

}
inline bool NoEnergy(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	AgentInfo pAgent;
	if (!pBlackboard->GetData("Agent", pAgent)) return false;
	return  (pAgent.Energy < 1.8);

}
inline bool FullStamina(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	AgentInfo pAgent;
	if (!pBlackboard->GetData("Agent", pAgent)) return false;
	return (pAgent.Stamina > 9.9);
	
}
inline bool LowStamina(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 

	AgentInfo pAgent;
	if (!pBlackboard->GetData("Agent", pAgent)) return false;
	return (pAgent.Stamina < 0.09);

}
inline bool HasMedkit(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	return  (InvInfo.slots[0] == ItemTypes::MEDKIT
		|| InvInfo.slots[1] == ItemTypes::MEDKIT
		|| InvInfo.slots[2] == ItemTypes::MEDKIT
		|| InvInfo.slots[3] == ItemTypes::MEDKIT
		|| InvInfo.slots[4] == ItemTypes::MEDKIT);
}
inline bool HasNoMedkit(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	return  !(InvInfo.slots[0] == ItemTypes::MEDKIT
		|| InvInfo.slots[1] == ItemTypes::MEDKIT
		|| InvInfo.slots[2] == ItemTypes::MEDKIT
		|| InvInfo.slots[3] == ItemTypes::MEDKIT
		|| InvInfo.slots[4] == ItemTypes::MEDKIT);
}
inline bool HasMoreThen1Pistols(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	int PistolCount =  0; 
	for (int i =  0 ; i  < 5; i++)
	{
		if(InvInfo.slots[i] == ItemTypes::PISTOL)
		{
			++PistolCount; 
		}
	}
	return (PistolCount >= 2);
		
	
}
inline bool HasMoreThen1Medkits(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	int Count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::MEDKIT)
		{
			++Count;
		}
	}
	return (Count > 1);



}
inline bool HasMoreThen3Food(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	int Count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::FOOD)
		{
			++Count;
		}
	}
	return (Count >= 4);



}
inline bool HasLessThen2Food(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	int Count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::FOOD)
		{
			++Count;
		}
	}
	return (Count <= 1);



}
inline bool LowEnergy(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check  low energy " << std::endl; 
	AgentInfo pAgent;
	if (!pBlackboard->GetData("Agent", pAgent)) return false;
	return (pAgent.Energy < 2.0f);
	
}
inline bool HasFood(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);

	return  (InvInfo.slots[0] == ItemTypes::FOOD
		|| InvInfo.slots[1] == ItemTypes::FOOD
		|| InvInfo.slots[2] == ItemTypes::FOOD
		|| InvInfo.slots[3] == ItemTypes::FOOD
		|| InvInfo.slots[4] == ItemTypes::FOOD);

}
inline bool HasNoFood(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);

	return  !(InvInfo.slots[0] == ItemTypes::FOOD
		|| InvInfo.slots[1] == ItemTypes::FOOD
		|| InvInfo.slots[2] == ItemTypes::FOOD
		|| InvInfo.slots[3] == ItemTypes::FOOD
		|| InvInfo.slots[4] == ItemTypes::FOOD);

}
inline bool HasGun(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	//std::cout << "Check  has gun energy " << std::endl;
	return  (InvInfo.slots[0] == ItemTypes::PISTOL
		|| InvInfo.slots[1] == ItemTypes::PISTOL
		|| InvInfo.slots[2] == ItemTypes::PISTOL
		|| InvInfo.slots[3] == ItemTypes::PISTOL
		|| InvInfo.slots[4] == ItemTypes::PISTOL);

}
inline bool HasNoGun(Elite::Blackboard * pBlackboard)
{
	//Todo Keep track  of inventory in blackboard
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	//std::cout << "Check  has gun energy " << std::endl;
	return  !(InvInfo.slots[0] == ItemTypes::PISTOL
		|| InvInfo.slots[1] == ItemTypes::PISTOL
		|| InvInfo.slots[2] == ItemTypes::PISTOL
		|| InvInfo.slots[3] == ItemTypes::PISTOL
		|| InvInfo.slots[4] == ItemTypes::PISTOL);

}
inline bool IsInTargetHouse(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 
	auto House = HouseInfo();
	bool isHouseSet; 

	AgentInfo pAgent;
	std::cout << "checking if in target house  : ";
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("TargetHouse", House)
		&& pBlackboard->GetData("ClosestHouseSet", isHouseSet)

		;
	if (!dataAvailable)
		return Elite::Failure;

	if (!isHouseSet)
	{
		std::cout <<  "check in target house :: NO HOUSE SET" << std::endl;
				return Elite::Failure;
	}
	auto cen = House.Center;
	auto dim = House.Size * 0.5;
	auto pos = pAgent.Position;
	if (cen.x + dim.x > pos.x && cen.x - dim.x < pos.x
		&& cen.y + dim.y > pos.y && cen.y - dim.y < pos.y)
	{
		std::cout << "Is in target house" << std::endl;
		return Elite::Success; 
	}
	std::cout << "Is Not target house" << std::endl;
	return Elite::Failure; 
}
inline bool IsInCenterOfTargetHouse(Elite::Blackboard * pBlackboard)
{
	//std::cout << "Check low hp" << std::endl; 
	auto House = HouseInfo();
	bool isHouseSet;
	vector<std::pair<HouseInfo, float> > seenHouses;


	AgentInfo pAgent;
	std::cout << "checking if in center target house" << std::endl;
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("TargetHouse", House)
		&& pBlackboard->GetData("ClosestHouseSet", isHouseSet)
	&& pBlackboard->GetData("seenHouses", seenHouses)

		;
	if (!dataAvailable)
		return Elite::Failure;

	if (!isHouseSet)
	{
		std::cout << "check in center target house :: NO HOUSE SET" << std::endl;
		return Elite::Failure;
	}

	auto v = House.Center - pAgent.Position;
	if (v.Magnitude() < 5)
	{
		for (auto house : seenHouses)
			if (house.first.Center == House.Center)
				house.second = 0;
		pBlackboard->ChangeData("seenHouses", seenHouses);
		pBlackboard->ChangeData("ClosestItemSet", false);
		pBlackboard->ChangeData("ClosestHouseSet", false);
		pBlackboard->ChangeData("TargetHouse", HouseInfo());

		return Elite::Success;
	}

	return Elite::Failure;
}
inline bool SeeItem(Elite::Blackboard * pBlackboard)
{
	vector<EntityInfo> vEInfo; 
	std::cout << "Check see Item " << std::endl; 
	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo)
		) return false;

	for (auto eInfo : vEInfo)
	{
		if (eInfo.Type == eEntityType::ITEM)
		{
			std::cout << "see Item " << std::endl;
			return true;
		}
	}
	return false; 
}
inline bool DontSeeItem(Elite::Blackboard * pBlackboard)
{
	vector<EntityInfo> vEInfo;
	std::cout << "Check see Item " << std::endl;
	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo)
		) return false;

	for (auto eInfo : vEInfo)
	{
		if (eInfo.Type == eEntityType::ITEM)
		{
			std::cout << "see Item " << std::endl;
			return false;
		}
	}
	return true;
}
inline bool SeeEnemy(Elite::Blackboard * pBlackboard)
{
	vector<EntityInfo> vEInfo;
	//std::cout << "Check see Item " << std::endl; 

	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo)  
		) return false;

	//if (isHouseSet)
	//	return false; 
	for (auto eInfo : vEInfo)
	{
		if (eInfo.Type == eEntityType::ENEMY) {
		
			pBlackboard->ChangeData("ClosestEnemySet", true);
			pBlackboard->ChangeData("ClosestEnemy", eInfo);
			return true;
		}


	}
	pBlackboard->ChangeData("ClosestEnemySet", false);
	return false;
}
inline bool FlagsSet(Elite::Blackboard * pBlackboard)
{
	std::cout << "Check flags:"; 
	vector<EntityInfo> vEInfo;
	bool isItemSet = false;
	bool isHouseSet = false;
	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo)
		|| !pBlackboard->GetData("ClosestItemSet", isItemSet)
		|| !pBlackboard->GetData("ClosestHouseSet", isHouseSet)) return false;
	if (!isItemSet)
	{
		std::cout << "item not set"; 
	}
	if (!isItemSet)
	{
		std::cout << "house not set";
	}
}
inline bool DontSeeItemOrHaveClosestItem(Elite::Blackboard * pBlackboard)
{
	//std::cout << "check  see item in fov " << std::endl;
	vector<EntityInfo> vEInfo;
	bool isItemSet = false; 
	bool isHouseSet = false;
	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo) 
		|| !pBlackboard->GetData("ClosestItemSet", isItemSet)
		|| !pBlackboard->GetData("ClosestHouseSet", isHouseSet)) return false;

	//if (isItemSet)
	//	return false; 
	if (isHouseSet)
		return false; 
	for (auto eInfo : vEInfo)
	{
		return false;

	}

	return true;

}
inline bool HasFreeSpace(Elite::Blackboard * pBlackboard)
{
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);

	return  (InvInfo.slots[0] == ItemTypes::EMPTY
		|| InvInfo.slots[1] == ItemTypes::EMPTY
		|| InvInfo.slots[2] == ItemTypes::EMPTY
		|| InvInfo.slots[3] == ItemTypes::EMPTY
		|| InvInfo.slots[4] == ItemTypes::EMPTY);
}


inline bool HasTrash(Elite::Blackboard * pBlackboard)
{
	auto InvInfo = InventoryInfo();
	//std::cout << "check has trash" << std::endl;
	pBlackboard->GetData("InventoryInfo", InvInfo);

	return  (InvInfo.slots[0] == ItemTypes::GARBAGE
		|| InvInfo.slots[1] == ItemTypes::GARBAGE
		|| InvInfo.slots[2] == ItemTypes::GARBAGE
		|| InvInfo.slots[3] == ItemTypes::GARBAGE
		|| InvInfo.slots[4] == ItemTypes::GARBAGE);

}


inline bool IsInventoryFull(Elite::Blackboard* pBlackboard)
{
	auto InvInfo = InventoryInfo();
	pBlackboard->GetData("InventoryInfo", InvInfo);
	return  (InvInfo.slots[0] != ItemTypes::EMPTY
		&& InvInfo.slots[1] != ItemTypes::EMPTY
		&&  InvInfo.slots[2] != ItemTypes::EMPTY
		&&   InvInfo.slots[3] != ItemTypes::EMPTY
		&&   InvInfo.slots[4] != ItemTypes::EMPTY);
	return true;
}
inline bool IsEnergyNotFull(Elite::Blackboard* pBlackboard)
{
	AgentInfo Agent;
	if (!pBlackboard->GetData("", Agent)) return false;
	auto energy = Agent.Energy;
	if (energy < 9.5)
		return true;
	else
		return true;
	return true;
}
inline bool IsHpNotFull(Elite::Blackboard* pBlackboard)
{
	AgentInfo Agent;
	if (!pBlackboard->GetData("Agent", Agent)) return false;
	auto hp = Agent.Health; 
	if (hp < 9.5)
		return true; 
	else 
	return true;
}
inline bool Empty(Elite::Blackboard* pBlackboard)
{

	return true;
}

inline Elite::BehaviorState UseMedKit(Elite::Blackboard * pBlackboard)
{
	auto InvInfo = InventoryInfo();
	IExamInterface * Interface  {};
	std::cout << " try  use medkit" << std::endl;
	const bool dataAvailable =  pBlackboard->GetData("InventoryInfo", InvInfo)
	&& pBlackboard->GetData("Interface", Interface);
	if (!dataAvailable)
		return Elite::Failure;
	for (int i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::MEDKIT)
		{
			InvInfo.slots[i] = ItemTypes::EMPTY;
			pBlackboard->ChangeData("InventoryInfo", InvInfo);
			Interface->Inventory_UseItem(i);
			Interface->Inventory_RemoveItem(i);
			std::cout << " succesfully used medkit" << std::endl;
			return Elite::Success;
		}
	}
	/*int medkitslot = -1;
	if (InvInfo.slots[0] == ItemTypes::MEDKIT)
		medkitslot = 0; 
	if (InvInfo.slots[1] == ItemTypes::MEDKIT)
		medkitslot = 1;
	if (InvInfo.slots[2] == ItemTypes::MEDKIT)
		medkitslot = 2;
	if (InvInfo.slots[3] == ItemTypes::MEDKIT)
		medkitslot = 3;
	if (InvInfo.slots[4] == ItemTypes::MEDKIT)
		medkitslot = 4;



	if (medkitslot >= 0)
	{
		Interface->Inventory_UseItem(medkitslot);
		Interface->Inventory_RemoveItem(medkitslot);
		return Elite::Success;
	}*/
	std::cout << "Tried to use medkit without medkit" << std::endl; 
	return Elite::Failure; 

}


inline Elite::BehaviorState UseFood(Elite::Blackboard * pBlackboard)
{
	auto InvInfo = InventoryInfo();
	IExamInterface * Interface  {};
	std::cout << " try use food" << std::endl;
	const bool dataAvailable = pBlackboard->GetData("InventoryInfo", InvInfo)
		&& pBlackboard->GetData("Interface", Interface);
	if (!dataAvailable)
		return Elite::Failure;

	for (int i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::FOOD)
		{
			InvInfo.slots[i] = ItemTypes::EMPTY;
			pBlackboard->ChangeData("InventoryInfo", InvInfo);
			Interface->Inventory_UseItem(i);
			Interface->Inventory_RemoveItem(i);
			std::cout << " succesfully used food" << std::endl;
			return Elite::Success;
		}
	}

	
	std::cout << "Tried to use food without food" << std::endl;
	return Elite::Failure;

}

inline Elite::BehaviorState PickUpItem(Elite::Blackboard * pBlackboard)
{

	EntityInfo Item;
	bool isItemSet;
	IExamInterface * pInterface; 
	InventoryInfo inv; 
	std::cout << "trying to pick up item" << std::endl;
	const bool dataAvailable = pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("ClosestItem", Item)
		&& pBlackboard->GetData("ClosestItemSet", isItemSet)
		&& pBlackboard->GetData("InventoryInfo", inv)
		;
	if (!dataAvailable)
		return Elite::Failure;
	if (!isItemSet)
	{
		std::cout << "Tried Pick up item without item set in BB" << std::endl;
		return Elite::Failure;
	}
	pBlackboard->ChangeData("ClosestItemSet", false);
	ItemInfo item; 

	if (pInterface->Item_Grab(Item, item))
	{
		//Once grabbed, you can add it to a specific inventory slot
		//Slot must be empty
		int emptyslotindex = -1; 
		for (int i = 0; i < 5; i++)
		{
			if (inv.slots[i] == ItemTypes::EMPTY)
			{ 
				emptyslotindex = i;
				break;
			}
		}
	
		
		if  (emptyslotindex ==  -1)
		{
			std::cout << "tried adding item to full invetory" << std::endl; 
			return Failure; 
		}
		pInterface->Inventory_AddItem(emptyslotindex, item);
		inv.slots[emptyslotindex] = (ItemTypes)(int)item.Type; 
		pBlackboard->ChangeData("ClosestItemSet", false);
		pBlackboard->ChangeData("ClosestHouseSet", false);
		pBlackboard->ChangeData("InventoryInfo", inv);
	}

	std::cout << "picked up item" << std::endl;
	return Elite::Success;

}

inline Elite::BehaviorState ChangeToIdle(Elite::Blackboard * pBlackboard)
{
	ISteeringBehavior * pIdle = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	AgentInfo pAgent;
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("IdleBehavior", pIdle)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		;

	if (!dataAvailable)
		return Elite::Failure;


	if (pIdle != pCurrentBehavior)
	{
		printf("Switch to Idle behavior \n");
		pBlackboard->ChangeData("CurrentBehavior", pIdle);
	}
	return Elite::Success;

}
inline Elite::BehaviorState ChangeToSeek(Elite::Blackboard * pBlackboard)
{
	//std::cout << "chaange to seek" << std::endl;
	ISteeringBehavior * pSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	AgentInfo pAgent;
	IExamInterface * pInterface {};
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("SeekBehavior", pSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */
	auto checkpointLocation = pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);

	dynamic_cast<SeekBehavior *>(pSeek)->SetTarget(nextTargetPos);
	if (pSeek != pCurrentBehavior)
	{
	//	printf("Switch to seek behavior \n");
		
	}
	pBlackboard->ChangeData("CurrentBehavior", pSeek);
	return Elite::Success;

}
inline Elite::BehaviorState ChangeToFacedSeek(Elite::Blackboard * pBlackboard)
{
	ISteeringBehavior * pfacedSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	AgentInfo pAgent;
	EntityInfo enemy; 
	bool IsEnemySet {}; 
	IExamInterface * pInterface{};
	//std::cout << " facedseek behavior" << std::endl;
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("ClosestEnemy", enemy)
		&& pBlackboard->GetData("ClosestEnemySet", IsEnemySet)
		&& pBlackboard->GetData("FacedSeekBehavior", pfacedSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */
	if (!IsEnemySet)
	{
		std::cout << "try face without enemy set" << std::endl;
		return Elite::Failure;
	}
	auto checkpointLocation = pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);

	dynamic_cast<FacedSeekBehavior *>(pfacedSeek)->SetTarget(nextTargetPos, enemy.Location);

	//printf("Switch to facedseek behavior \n");


	pBlackboard->ChangeData("CurrentBehavior", pfacedSeek);
	return Elite::Success;

}
inline Elite::BehaviorState ChangeToAvoidSeek(Elite::Blackboard * pBlackboard)
{
	ISteeringBehavior * pavoidSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	AgentInfo pAgent;
	EntityInfo enemy;
	bool IsEnemySet{};
	IExamInterface * pInterface{};
	//std::cout << " facedseek behavior" << std::endl;
	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("ClosestEnemy", enemy)
		&& pBlackboard->GetData("ClosestEnemySet", IsEnemySet)
		&& pBlackboard->GetData("AvoidingSeekBehavior", pavoidSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
	return Elite::Failure; */
	if (!IsEnemySet)
	{
		std::cout << "try avoid without enemy set" << std::endl; 
		return Elite::Failure;
	}
	auto checkpointLocation = pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);

	dynamic_cast<AvoidingSeekBehavior *>(pavoidSeek)->SetTarget(nextTargetPos, enemy.Location);

	//printf("Switch to facedseek behavior \n");


	pBlackboard->ChangeData("CurrentBehavior", pavoidSeek);
	return Elite::Success;

}
inline Elite::BehaviorState TryShoot(Elite::Blackboard * pBlackboard)
{

	AgentInfo pAgent;
	//bool canHit = false;
	//std::cout << "Try SHOOT   // ";
	EntityInfo enemi;
	bool IsEnemySet{};
	IExamInterface * pInterface{};
	auto InvInfo = InventoryInfo();
	//IExamInterface * Interface{};
	vector<EntityInfo> enemies; 

	const bool dataAvailable = pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("ClosestEnemy", enemi)
		//&& pBlackboard->GetData("CanHit", canHit)
		&& pBlackboard->GetData("ClosestEnemySet", IsEnemySet)
		&& pBlackboard->GetData("InventoryInfo", InvInfo)
		&& pBlackboard->GetData("EntitiesInFOV", enemies)
	//	&& pBlackboard->GetData("Interface", Interface)

		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */
	if (!IsEnemySet)
	{
		std::cout << "Tried shooting without enemy set" << std::endl;
		return Failure; 
	}

	auto checkpointLocation = pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);
	auto dir = nextTargetPos - pAgent.Position; 
	dir.Normalize(); 
	for (auto enemy : enemies)
	{
		if (enemy.Type == eEntityType::ITEM) continue; 
		auto vecToTarget = enemy.Location - pAgent.Position;
		//auto dist = vecToTarget.Magnitude(); 
		//std::cout << "shooting dist: " << dist << endl; 
		vecToTarget.Normalize();
		Vector2 vector1 = { 0,-1 };
		Vector2 vector2 = vecToTarget;
		auto angle = atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x);
		if (angle > M_PI) { angle -= 2 * M_PI; }
		else if (angle <= -M_PI) { angle += 2 * M_PI; }
		//auto angle = acos(-vecToTarget.y); 
		angle -= pAgent.Orientation;
	//	std::cout << "angle for shoot:  " << angle << std::endl;
		auto d =  ((3 -  2 *vecToTarget.Magnitude()) *0.05 * 0.3);
		if (d < 0)
			d = 0;
		if (abs(angle) < 0.05 + d)
		{
	//		std::cout << "shooting" << std::endl;
			for (int i = 0; i < 5; i++)
			{
				if (InvInfo.slots[i] == ItemTypes::PISTOL)
				{
					if (pInterface->Inventory_UseItem(i))
					{
						//Bullets  left 
						return Elite::Success;
					}
					InvInfo.slots[i] = ItemTypes::EMPTY;
					pBlackboard->ChangeData("InventoryInfo", InvInfo);
					pBlackboard->ChangeData("ClosestEnemySet", false);
					pInterface->Inventory_RemoveItem(i);
		//			std::cout << " succesfully removed empty gun" << std::endl;
					return Elite::Success;
				}
			}

		}
	}
	
	

	printf("Switch to facedseek behavior \n");


	return Elite::Failure;

}
inline Elite::BehaviorState SwitchToWaypointSeek(Elite::Blackboard * pBlackboard)
{
	ISteeringBehavior * pSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	IExamInterface * pInterface;
	const bool dataAvailable = pBlackboard->GetData("Interface", pInterface)
		&& pBlackboard->GetData("SeekBehavior", pSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */   
		//Retrieve the current location of our CheckPoint
	auto checkpointLocation = pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);

	dynamic_cast<SeekBehavior *>(pSeek)->SetTarget(nextTargetPos);
	printf("Switch to Seek Item behavior \n");
	pBlackboard->ChangeData("CurrentBehavior", pSeek);
	return Elite::Success;

}
inline Elite::BehaviorState ChangeToSeekItem(Elite::Blackboard * pBlackboard)
{
	ISteeringBehavior * pSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	Vector2 target; 
	EntityInfo closestItem;
	bool isItemSet; 


	AgentInfo pAgent;
	const bool dataAvailable =
		pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("SeekBehavior", pSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		&& pBlackboard->GetData("ClosestItem", closestItem)
		&& pBlackboard->GetData("ClosestItemSet", isItemSet)

		;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */
	if (!isItemSet)
	{
		std::cout << "Tried going to closest item without item set in BB" << std::endl;
		return Elite::Failure;
	}

	dynamic_cast<SeekBehavior *>(pSeek)->SetTarget(closestItem.Location); 
	//printf("Switch to Seek Item behavior \n");
	pBlackboard->ChangeData("CurrentBehavior", pSeek);
	
	return Elite::Success;

}
inline Elite::BehaviorState ChangeToSeekHouse(Elite::Blackboard * pBlackboard)
{
	std::cout << "Seeking house ";
	ISteeringBehavior * pSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	Vector2 target;
	EntityInfo closestItem;
	bool isItemSet;
	IExamInterface * Interface{};
	std::vector<std::pair<HouseInfo, float>> seenHouses; 
	AgentInfo pAgent;
	bool closestHouseSet;
	const bool dataAvailable =
		pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("SeekBehavior", pSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		&& pBlackboard->GetData("ClosestItem", closestItem)
		&& pBlackboard->GetData("ClosestItemSet", isItemSet)
		&& pBlackboard->GetData("seenHouses", seenHouses)
		&& pBlackboard->GetData("Interface", Interface)
		&& pBlackboard->GetData("ClosestHouseSet", closestHouseSet);;

		;

	if (!dataAvailable)
		return Elite::Failure;
	
	float maxvisittime = -9999999; 
	HouseInfo h; 
	for (auto house : seenHouses)
	{
		if (house.second > maxvisittime)
		{
			h = house.first; 
			maxvisittime = house.second; 
		}
			
	}
	pBlackboard->ChangeData("TargetHouse", h);
	pBlackboard->ChangeData("ClosestHouseSet", true); 
	
	auto t = Interface->NavMesh_GetClosestPathPoint(h.Center);
	std::cout << "target :" << t.x << ","  << t.y << "  "; 
	std::cout << "Center :" << h.Center.x << "," << h.Center.y << " ";
	dynamic_cast<SeekBehavior *>(pSeek)->SetTarget(t);
	//printf("Switch to Seek Item behavior \n");
	pBlackboard->ChangeData("CurrentBehavior", pSeek);

	return Elite::Success;

}
inline Elite::BehaviorState ChangeToWanderInHouse(Elite::Blackboard * pBlackboard)
{
	std::cout << "change to wander in house" ;
	ISteeringBehavior * pWanderingSeek = nullptr;
	ISteeringBehavior * pCurrentBehavior = nullptr;
	Vector2 target;
	EntityInfo closestItem;
	bool isHouseSet;
	IExamInterface * Interface{};
	HouseInfo targetHouse;
	AgentInfo pAgent;

	const bool dataAvailable =
		pBlackboard->GetData("Agent", pAgent)
		&& pBlackboard->GetData("WanderingSeekBehavior", pWanderingSeek)
		&& pBlackboard->GetData("CurrentBehavior", pCurrentBehavior)
		&& pBlackboard->GetData("ClosestItem", closestItem)
		&& pBlackboard->GetData("ClosestHouseSet", isHouseSet)
		&& pBlackboard->GetData("TargetHouse", targetHouse)
		&& pBlackboard->GetData("Interface", Interface);
		//&& pBlackboard->GetData("ClosestHouseSet", closestHouseSet);

	;

	if (!dataAvailable)
		return Elite::Failure;
	/*if (!pAgent || !pSeek)
		return Elite::Failure; */
	if (!isHouseSet)
	{
		std::cout << "tried to wander in house without house set " << std::endl; 

		return Elite::Failure;
	}


	dynamic_cast<WanderingSeekBehavior *>(pWanderingSeek)->SetTarget(Interface->NavMesh_GetClosestPathPoint(targetHouse.Center));

	pBlackboard->ChangeData("CurrentBehavior", pWanderingSeek);

	return Elite::Success;

}
inline Elite::BehaviorState RemoveTrash(Elite::Blackboard * pBlackboard)
{
	std::cout << "Try remove garbage" << std::endl; 

	auto InvInfo = InventoryInfo();
	IExamInterface * Interface  {};



	const bool dataAvailable = 
		pBlackboard->GetData("InventoryInfo", InvInfo)
		&& pBlackboard->GetData("Interface", Interface);

	if (!dataAvailable)
		return Elite::Failure;

	for (int  i = 0; i < 5; i++)
	{
		if (InvInfo.slots[i] == ItemTypes::GARBAGE)
		{
			InvInfo.slots[i] = ItemTypes::EMPTY; 
			pBlackboard->ChangeData("InventoryInfo", InvInfo);
			Interface->Inventory_RemoveItem(i);
			std::cout << " succesfully removed garbage" << std::endl;
			return Elite::Success;
		}	}
	std::cout << "Try Failed remove garbage no garbage found" << std::endl;
	return Elite::Failure;
}
inline Elite::BehaviorState RemovePistol(Elite::Blackboard * pBlackboard)
{
	std::cout << "Try remove Pistol" << std::endl;

	auto InvInfo = InventoryInfo();
	IExamInterface * Interface{};



	const bool dataAvailable =
		pBlackboard->GetData("InventoryInfo", InvInfo)
		&& pBlackboard->GetData("Interface", Interface);

	if (!dataAvailable)
		return Elite::Failure;

	for (int i = 4; i >= 0; i--)
	{
		if (InvInfo.slots[i] == ItemTypes::PISTOL)
		{
			InvInfo.slots[i] = ItemTypes::EMPTY;
			pBlackboard->ChangeData("InventoryInfo", InvInfo);
			Interface->Inventory_RemoveItem(i);
			std::cout << " succesfully removed pistol" << std::endl;
			return Elite::Success;
		}
	}
	std::cout << "Try Failed remove gun no gun found" << std::endl;
	return Elite::Failure;
}
inline  Elite::BehaviorState CanRun(Elite::Blackboard * pBlackboard)
{

	//std::cout << "can run" << std::endl; 

	pBlackboard->ChangeData("canRun", true); 
	return Elite::Success;
}
inline  Elite::BehaviorState CanNotRun(Elite::Blackboard * pBlackboard)
{
//	std::cout << "Can not run" << std::endl; 
	pBlackboard->ChangeData("canRun", false);
	return Elite::Failure;
}
inline  Elite::BehaviorState SaveClosestItemInFOV(Elite::Blackboard * pBlackboard)
{

	vector<EntityInfo> vEInfo;

	
	if (!pBlackboard->GetData("EntitiesInFOV", vEInfo)) 	return Elite::Failure;
	AgentInfo Agent;
	if (!pBlackboard->GetData("Agent", Agent)) 	return Elite::Failure;
	auto loc = Agent.Position;
	float maxdist = 999999;
	EntityInfo Item; 

	for (auto eInfo : vEInfo)
	{
		auto pos = eInfo.Location;
		auto v = Agent.Position - eInfo.Location;
		auto dist = sqrt(v.x * v.x + v.y * v.y);
		if (dist < maxdist)
		{
			maxdist = dist; 
			Item = eInfo;

		}

	}
	if (maxdist <  99999)
	{
		if (pBlackboard->ChangeData("ClosestItem", Item) && pBlackboard->ChangeData("ClosestItemSet", true))
		return Elite::Success;
	}
	return Elite::Failure;
}


inline bool IsClosestItemInRange(Elite::Blackboard * pBlackboard)
{
	EntityInfo Item;
	bool ItemSet; 
	AgentInfo Agent;
	if (!pBlackboard->GetData("Agent", Agent)) 	return false;
	if (!pBlackboard->GetData("ClosestItem", Item)) return false;
	if (!pBlackboard->GetData("ClosestItemSet", ItemSet)) return false;

	auto loc = Agent.Position;
	if (!ItemSet)
	{
		std::cout << "Tried checking if closest item is in range  without item set in BB" << std::endl;
		return Elite::Failure;
	}

	auto pos = Item.Location;
	auto v = Agent.Position - pos;
	auto dist = sqrt(v.x * v.x + v.y * v.y);
	if (dist < Agent.GrabRange)
	{
		return Elite::Success;
	}
	Elite::Failure;
	
}

inline bool IsClosestItemNotInRange(Elite::Blackboard * pBlackboard)
{
	EntityInfo Item;
	bool ItemSet;
	AgentInfo Agent;
	if (!pBlackboard->GetData("Agent", Agent)) 	return Elite::Failure;
	if (!pBlackboard->GetData("ClosestItem", Item)) return false;
	if (!pBlackboard->GetData("ClosestItemSet", ItemSet)) return false;

	auto loc = Agent.Position;
	if (!ItemSet)
	{
		std::cout << "Tried checking if closest item is in range  without item set in BB" << std::endl;
		return Elite::Failure;
	}

	auto pos = Item.Location;
	auto v = Agent.Position - pos;
	auto dist = sqrt(v.x * v.x + v.y * v.y);
	if (dist < Agent.GrabRange)
	{
		
		return false;
	}
	return true;

}

#endif