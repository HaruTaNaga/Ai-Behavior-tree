#include "stdafx.h"
#include "Plugin.h"
#include "IExamInterface.h"
#include "behaviors.h"
#include "SteeringBehaviors.h"
//Called only once, during initialization
void Plugin::Initialize(IBaseInterface* pInterface, PluginInfo& info)
{
	//Retrieving the interface
	//This interface gives you access to certain actions the AI_Framework can perform for you
	m_pInterface = static_cast<IExamInterface*>(pInterface);
	std::cout << "Welcome to the elite " << std::endl; 
	//Bit information about the plugin
	//Please fill this in!!
	info.BotName = "MinionExam";
	info.Student_FirstName = "Wout";
	info.Student_LastName = "Gryseels";
	info.Student_Class = "2DAE02";

	m_pBlackBoard = new Elite::Blackboard;

	m_pBlackBoard->AddData("Interface", m_pInterface); 

	vector<std::pair<HouseInfo, float> > seenHouses; 


	auto InvInfo = InventoryInfo();


	EntityInfo Item {};
	EntityInfo Enemy{};
	auto TargetHouse = HouseInfo();	
	auto vHousesInFOV = GetHousesInFOV();	
	auto vEntitiesInFOV = GetEntitiesInFOV();
	auto i = m_pInterface->Agent_GetInfo();

	m_pBlackBoard->AddData("TargetHouse", TargetHouse);
	m_pBlackBoard->AddData("ClosestItem", Item);
	m_pBlackBoard->AddData("ClosestEnemy", Enemy);
	m_pBlackBoard->AddData("Agent", i);
	m_pBlackBoard->AddData("HousesInFOV", vHousesInFOV);
	m_pBlackBoard->AddData("EntitiesInFOV", vEntitiesInFOV);
	m_pBlackBoard->AddData("InventoryInfo", InvInfo);
	m_pBlackBoard->AddData("seenHouses", seenHouses);

	m_pBlackBoard->AddData("ClosestItemSet", false);
	m_pBlackBoard->AddData("ClosestEnemySet", false);
	m_pBlackBoard->AddData("ClosestHouseSet", false);
	m_pBlackBoard->AddData("canRun", false); 
	m_pBlackBoard->AddData("CanHit", true);
	m_pBlackBoard->AddData("TargetSet", false);
	m_pBlackBoard->AddData("HouseTimer", 0.0f);

	m_pBlackBoard->AddData("SeekBehavior", static_cast<ISteeringBehavior  *>(new SeekBehavior));
	m_pBlackBoard->AddData("IdleBehavior", static_cast<ISteeringBehavior  *>(new IdleBehavior));
	m_pBlackBoard->AddData("FacedSeekBehavior", static_cast<ISteeringBehavior  *>(new FacedSeekBehavior));
	m_pBlackBoard->AddData("AvoidingSeekBehavior", static_cast<ISteeringBehavior  *>(new AvoidingSeekBehavior));

	m_pBlackBoard->AddData("WanderingSeekBehavior", static_cast<ISteeringBehavior  *>(new WanderingSeekBehavior));
	m_pBlackBoard->AddData("CurrentBehavior", static_cast<ISteeringBehavior  *>(new SeekBehavior));

	//**TEST behavior tree **//
	//m_pBehaviortree = new Elite::BehaviorTree(m_pBlackBoard,

	//	new Elite::BehaviorSelector
	//	({
	//		new Elite::BehaviorSequence({
	//				new Elite::BehaviorConditional(HasTarget),
	//				new Elite::BehaviorAction(ChangeToSeek)
	//			}),
	//		new Elite::BehaviorSequence({
	//				new Elite::BehaviorConditional(DoesNotHaveTarget),
	//				new Elite::BehaviorAction(ChangeToIdle)
	//			}),
	//	
	//		})

	//);

	m_pBehaviortree = new Elite::BehaviorTree
	(m_pBlackBoard,
		new Elite::BehaviorSelector
		({
				new Elite::BehaviorSelector
				({
					new Elite::BehaviorSequence(
					{
						new Elite::BehaviorConditional(SeeItem),
						new Elite::BehaviorConditional(HasFreeSpace),
						new Elite::BehaviorAction(SaveClosestItemInFOV),
						new Elite::BehaviorSelector
						({
							new Elite::BehaviorSequence(
								{
									new Elite::BehaviorConditional(IsClosestItemInRange),
									new Elite::BehaviorAction(PickUpItem),
									new Elite::BehaviorConditional(IsInventoryFull),
									new Elite::BehaviorSelector
									({
											new Elite::BehaviorSequence(
												{
													new Elite::BehaviorConditional(HasMoreThen1Pistols),
													new Elite::BehaviorAction(RemovePistol),

												}),
											new Elite::BehaviorSequence(
												{
													new Elite::BehaviorConditional(HasMoreThen1Medkits),
													new Elite::BehaviorAction(UseMedKit)
												}),
												new Elite::BehaviorSequence(
												{
													new Elite::BehaviorConditional(HasMoreThen3Food),
													new Elite::BehaviorAction(UseFood)
												}),
										})
								}),
							new Elite::BehaviorSequence(
								{
									new Elite::BehaviorConditional(IsClosestItemNotInRange),
									new Elite::BehaviorAction(ChangeToSeekItem),
								}),


						}),new Elite::BehaviorConditional(rFalse)
						//new Elite::BehaviorConditional(ChangeToSeek)
					}),
				}),   
				new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(StuckInHouse),
					new Elite::BehaviorAction(ChangeToSeek),
					
				}),
				new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(HasGun),
					new Elite::BehaviorConditional(SeeEnemy),
					new Elite::BehaviorAction(ChangeToFacedSeek),
					new Elite::BehaviorAction(TryShoot),

				}),
					new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(HasTrash),
					new Elite::BehaviorAction(RemoveTrash)
				}),                            
			new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(LowHP),
					new Elite::BehaviorConditional(HasMedkit),
					new Elite::BehaviorAction(UseMedKit)

				}),
			new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(LowEnergy),
					new Elite::BehaviorConditional(HasFood),
					new Elite::BehaviorAction(UseFood)

				}),
		
				new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(DontSeeItemOrHaveClosestItem),
					new Elite::BehaviorAction(ChangeToSeek),
					new Elite::BehaviorConditional(rFalse)
				}),	new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(FullStamina),
						new Elite::BehaviorAction(CanRun), new Elite::BehaviorConditional(rFalse)
				}),
				new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(HasNoGun),
					new Elite::BehaviorConditional(SeeEnemy),
					new Elite::BehaviorAction(ChangeToAvoidSeek),

				}),
			new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(DontSeeItem),
					new Elite::BehaviorConditional(VeryLowHP),
					new Elite::BehaviorConditional(HasNoMedkit),
					new Elite::BehaviorConditional(HasNoFood),
					new Elite::BehaviorConditional(NoEnergy),
				//	new Elite::BehaviorConditional(NotStuckInHouse), 
					new Elite::BehaviorSelector
					({
					
							new Elite::BehaviorSequence(
						{
							new Elite::BehaviorAction(ChangeToSeekHouse),
							new Elite::BehaviorConditional(IsInTargetHouse),
							new Elite::BehaviorAction(ChangeToWanderInHouse),
							new Elite::BehaviorConditional(rFalse)
						}),
							new Elite::BehaviorSequence(
						{
							new Elite::BehaviorConditional(IsInCenterOfTargetHouse),
							new Elite::BehaviorAction(ChangeToSeek), 
						
						}),
								new Elite::BehaviorSequence(
						{
							new Elite::BehaviorConditional(HasGun),
							new Elite::BehaviorConditional(SeeEnemy),
							new Elite::BehaviorAction(ChangeToFacedSeek),
							new Elite::BehaviorAction(TryShoot),


						}),
						
					}),
				}),
				

			new Elite::BehaviorSequence(
				{
					new Elite::BehaviorConditional(LowStamina),
					new Elite::BehaviorAction(CanNotRun)
				}),

	
		})
	);
	


}

//Called only once
void Plugin::DllInit()
{
	//Called when the plugin is loaded
	delete m_pBlackBoard; 
	delete m_pBehaviortree; 
	delete m_pInterface;
}

//Called only once
void Plugin::DllShutdown()
{
	//Called wheb the plugin gets unloaded
}

//Called only once, during initialization
void Plugin::InitGameDebugParams(GameDebugParams& params)
{
	params.AutoFollowCam = true; //Automatically follow the AI? (Default = true)
	params.RenderUI = true; //Render the IMGUI Panel? (Default = true)
	params.SpawnEnemies = true; //Do you want to spawn enemies? (Default = true)
	params.EnemyCount = 20; //How many enemies? (Default = 20)
	params.GodMode = false; //GodMode > You can't die, can be usefull to inspect certain behaviours (Default = false)
							//params.LevelFile = "LevelTwo.gppl";
	params.AutoGrabClosestItem = true; //A call to Item_Grab(...) returns the closest item that can be grabbed. (EntityInfo argument is ignored)
	params.OverrideDifficulty = false;
	params.Difficulty = 2.f;
}

//Only Active in DEBUG Mode
//(=Use only for Debug Purposes)
void Plugin::Update(float dt)
{
	

}

//Update
//This function calculates the new SteeringOutput, called once per frame
SteeringPlugin_Output Plugin::UpdateSteering(float dt)
{
	
	auto steering = SteeringPlugin_Output();
	m_TotalTime += dt; 
	//Use the Interface (IAssignmentInterface) to 'interface' with the AI_Framework
	auto agentInfo = m_pInterface->Agent_GetInfo();

	//Retrieve the current location of our CheckPoint
	auto checkpointLocation = m_pInterface->World_GetCheckpointLocation();

	//Use the navmesh to calculate the next navmesh point
	auto nextTargetPos = m_pInterface->NavMesh_GetClosestPathPoint(checkpointLocation);

	//OR, Use the mouse target
	//auto nextTargetPos = m_Target; //Uncomment this to use mouse position as guidance
	auto vEntitiesInFOV = GetEntitiesInFOV();	
//uses m_pInterface->Fov_GetHouseByIndex(...)
	 //uses m_pInterface->Fov_GetEntityByIndex(...)
	m_pBlackBoard->ChangeData("EntitiesInFOV", vEntitiesInFOV);	
	auto vHousesInFOV = GetHousesInFOV();		  //********************
	m_pBlackBoard->ChangeData("HousesInFOV", vHousesInFOV);
	vector<std::pair<HouseInfo, float> > seenHouses;
	m_pBlackBoard->GetData("seenHouses", seenHouses);

	for (auto house : vHousesInFOV)
	{
		bool hasBeenseen = false;
		for (auto seenHouse : seenHouses)
			if (seenHouse.first.Center == house.Center)
				hasBeenseen = true; 
			
		if (!hasBeenseen)
		{
			seenHouses.push_back({ house, 0.0f }); std::cout << "remember house" << std::endl;
		}
	}
	for (auto & seenHouse : seenHouses)
	{
		seenHouse.second += dt; 
	}

	auto nfo = m_pInterface->Agent_GetInfo();
	m_pBlackBoard->ChangeData("Agent", nfo);
	bool isClosestHouseSet  {}; 
	m_pBlackBoard->GetData("ClosestHouseSet", isClosestHouseSet);
	HouseInfo closestHouse {}; 
	m_pBlackBoard->GetData("TargetHouse", closestHouse);

	//check if agent is in hous e
	for (auto & seenHouse : seenHouses)
	{
		if (isClosestHouseSet && seenHouse.first.Center == closestHouse.Center)
			continue;
		auto cen = seenHouse.first.Center; 
		auto dim = seenHouse.first.Size * 0.5; 
		auto pos = nfo.Position; 
		if (cen.x + dim.x > pos.x && cen.x - dim.x < pos.x
			&& cen.y + dim.y > pos.y && cen.y - dim.y < pos.y)
		{
			seenHouse.second = 0;// std::cout << "reset house timer" << std::endl;
		}

	}
	m_pBlackBoard->ChangeData("seenHouses", seenHouses);
	m_pBehaviortree->Update();
	if (m_GrabItem)
	{
		ItemInfo item;
		//Item_Grab > When DebugParams.AutoGrabClosestItem is TRUE, the Item_Grab function returns the closest item in range
		//Keep in mind that DebugParams are only used for debugging purposes, by default this flag is FALSE
		//Otherwise, use GetEntitiesInFOV() to retrieve a vector of all entities in the FOV (EntityInfo)
		//Item_Grab gives you the ItemInfo back, based on the passed EntityHash (retrieved by GetEntitiesInFOV)
		if (m_pInterface->Item_Grab({}, item))
		{
			//Once grabbed, you can add it to a specific inventory slot
			//Slot must be empty
			m_pInterface->Inventory_AddItem(0, item);
		}
	}
	float hTimer; 
	m_pBlackBoard->GetData("HouseTimer", hTimer);
	if (m_pInterface->Agent_GetInfo().IsInHouse)
		m_pBlackBoard->ChangeData("HouseTimer", hTimer  += dt);
	else
		m_pBlackBoard->ChangeData("HouseTimer", 0.0f);


	if (m_UseItem)
	{
		//Use an item (make sure there is an item at the given inventory slot)
		m_pInterface->Inventory_UseItem(0);
	}

	if (m_RemoveItem)
	{
		//Remove an item from a inventory slot
		m_pInterface->Inventory_RemoveItem(0);
	}

	//Simple Seek Behaviour (towards Target)
	steering.LinearVelocity = nextTargetPos - agentInfo.Position; //Desired Velocity
	steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
	steering.LinearVelocity *= agentInfo.MaxLinearSpeed; //Rescale to Max Speed

	if (Distance(nextTargetPos, agentInfo.Position) < 2.f)
	{
		steering.LinearVelocity = Elite::ZeroVector2;
	}

	//steering.AngularVelocity = m_AngSpeed; //Rotate your character to inspect the world while walking
	steering.AutoOrientate = true; //Setting AutoOrientate to TRue overrides the AngularVelocity

	steering.RunMode = m_CanRun; //If RunMode is True > MaxLinSpd is increased for a limited time (till your stamina runs out)

								 //SteeringPlugin_Output is works the exact same way a SteeringBehaviour output

								 //@End (Demo Purposes)
	m_GrabItem = false; //Reset State
	m_UseItem = false;
	m_RemoveItem = false;

	//return steering;
	ISteeringBehavior  * Behavior; 
	auto b = m_pBlackBoard->GetData("CurrentBehavior", Behavior);
	auto in = m_pInterface->Agent_GetInfo();
	auto r=  Behavior->CalculateSteering(dt, &in);
	bool  canrun = false; 
	m_pBlackBoard->GetData("canRun", canrun);
	if (canrun)
	{
		r.RunMode = true; 
	}
	m_pInterface->Draw_Segment(in.Position, in.Position + in.LinearVelocity,  {1, 1,0 }, 0);
	m_pInterface->Draw_SolidCircle(in.Position + in.LinearVelocity, .7f, { 0,0 }, { 0.3, 1, 0 });
	if  (dynamic_cast<SeekBehavior *>(Behavior) != nullptr)
	{
		m_pInterface->Draw_SolidCircle(dynamic_cast<SeekBehavior *>(Behavior)->m_pTargetRef, .7f, { 0,0 }, { 0.1, 1, 0.2 });
	}
	if (dynamic_cast<FacedSeekBehavior *>(Behavior) != nullptr)
	{
		m_pInterface->Draw_SolidCircle(dynamic_cast<FacedSeekBehavior *>(Behavior)->m_pTargetRef, .7f, { 0,0 }, { 0.4, .1, 0.2 });
	}
	if (dynamic_cast<WanderingSeekBehavior *>(Behavior) != nullptr)
	{
		m_pInterface->Draw_SolidCircle(dynamic_cast<WanderingSeekBehavior *>(Behavior)->m_pTargetRef, .7f, { 0,0 }, { 0, 0.5, 1 });
	}
	return  r; 
}

//This function should only be used for rendering debug elements
void Plugin::Render(float dt) const
{
	//This Render function should only contain calls to Interface->Draw_... functions
	m_pInterface->Draw_SolidCircle(m_Target, .7f, { 0,0 }, { 1, 0, 0 });
	
}

vector<HouseInfo> Plugin::GetHousesInFOV() const
{
	vector<HouseInfo> vHousesInFOV = {};

	HouseInfo hi = {};
	for (int i = 0;; ++i)
	{
		if (m_pInterface->Fov_GetHouseByIndex(i, hi))
		{
			vHousesInFOV.push_back(hi);
			continue;
		}

		break;
	}

	return vHousesInFOV;
}

vector<EntityInfo> Plugin::GetEntitiesInFOV() const
{
	vector<EntityInfo> vEntitiesInFOV = {};

	EntityInfo ei = {};
	for (int i = 0;; ++i)
	{
		if (m_pInterface->Fov_GetEntityByIndex(i, ei))
		{
			vEntitiesInFOV.push_back(ei);
			continue;
		}

		break;
	}

	return vEntitiesInFOV;
}
