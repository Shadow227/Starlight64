//#include "mathHelper.h"
#include <vector>
#pragma once
/*
	gameCore.h is a single area I can hold a lot of class info. While a lot of what I have been
	doing is setting up backbone for later, all of these functions and classes will be used, eventually.
*/








/*
	GameObject is the base building block for all objects in the game. Once again using UE as
	a base example, think of this as a UObject. This class is a parent class to be expanded.
*/
class GameObject 
{
	//Private member variables
	const char* m_objectName;
	int m_objectID;
	bool m_isTickEnabled;
	//Save our parent and children. I think I can use this for a hierarchy
	GameObject* m_parent;
	std::vector<GameObject*> m_children;
	//Public member variables
public:
	//Vector3D m_transform;

	//Functions
public:
	//Constructor for our game object, for now this will just set the name but
	//in the future I want to be able to expand this as needed.
	//GameObject(const char* objectName,Vector3D transform, bool canTick = true, GameObject* parent = nullptr)
	//{
		//m_objectName = objectName;
		//m_objectID = 1;
		//m_isTickEnabled = canTick;
		//m_transform = transform;
		//m_parent = parent;
	//};
	//Destructor, handles cleanup.
	//~GameObject()
	//{
	//	Destroy();
	//};
	//Object update, Im taking inspiration from UE here. the "isTickEnabled" bool
	//will control if this function runs or not.
	virtual void onGameTick() = 0;
	//A simple function to add a child to this game objet.
	//TODO: Add more checks to make sure duplicate children can't be added.
	bool AddChild(GameObject* child) 
	{
		//Check if child exists
		if (child) 
		{
			m_children.push_back(child);
		}
	}
	//For destorying the object, this will do the actual cleanup and the destructor will just call
	//this function.
	void Destroy()
	{
	};
};
/*
	GameScene is the "level" the game will load. Every game will need at least 1 scene
	to work properly. Again as of writing this, this function will be mostly empty but I wish
	to set this up now instead of later while its on my mind.
*/
class GameScene 
{
	//TODO: Change this to pointers? Need to finish renderer to figure out if its better to
	//use a pointer here to stack-mem it OR if I should keep it heap memory here.
	std::vector<GameObject> m_levelObjects; // All objects in the scene
	//TODO: Figure out if uint32_t is too large for level IDs, I want to stay resonable here
	uint32_t m_levelID; // The ID of the level. This is what all scenes will be refered to as.

	//(void*) m_tick;
	//(void*) m_onLoad;

public:
	//Create a scene from game objects. I might change this input later when I figure out HOW im
	//going to make scenes but for now this is perfectly fine.
	GameScene* CreateScene(std::vector<GameObject> levelObjects, void* tickFunction = nullptr, void* onLoadEventHandler = nullptr)
	{
		//TODO: Create scene, assign ID.
	}
	//Handles unloading and clearing a scene.
	bool DestroyScene() 
	{
		m_levelObjects.clear();
	}
	//Once I figure out how to do this properly, this is the scene's update function. It will be called
	//every game tick and can be assigned using the "CreateScene()" function.
	void SceneTick() 
	{
			//TODO: Figure out how to call functions I pass through a pointer.
	}
	//The function this calles is called only when the scene is first loaded into the game engine.
	//This is essentually an event that fires after loading has finished and can be used
	//to notify other systems of the level loading, or to call custom code.
	//I want this to be overridden for the most part which will be seen as I develop this engine more.
	void OnLoaded()
	{
			//TODO: Figure out how to call functions I pass through a pointer.
	}
};

/*
	ENGINE DATA:
	This section is for when I convert this over to a true "Engine". These structs are for the game data
	that any user can override.
*/
#pragma region EngineDataStructs
//holds window data, as of right now it holds
//the window width and height, though it may hold more info later.
struct SLE64_WINData
{
	int windowWidth, windowHeight;
};
//holds game info, including scenes and the game name. It will expand as I
//expand this engine to do more.
struct SLE64_BuildData
{
	std::vector<GameScene*> scenes;
	const char* gameName;
	SLE64_WINData* windowData;
};
#pragma endregion