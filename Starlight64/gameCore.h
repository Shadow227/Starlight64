#include "mathHelper.h"
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
	private:
		const char* m_objectName;
		int m_objectID;
		bool m_isTickEnabled;
		//Save our parent and children. I think I can use this for a hierarchy
		GameObject* m_parent;
		std::vector<GameObject*> m_children;
		//Public member variables
	public:
		Vector3D m_transform;
		//Functions
	public:
		//Constructor for our game object, for now this will just set the name but
		//in the future I want to be able to expand this as needed.
		GameObject(const char* objectName, Vector3D transform, bool canTick = true, GameObject* parent = nullptr)
		{
			m_objectName = objectName;
			m_objectID = 1;
			m_isTickEnabled = canTick;
			m_transform = transform;
			m_parent = parent;
		};
		//Destructor, handles cleanup.
		~GameObject()
		{
			Destroy();
		};
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
		Data for all GameScenes, this holds the fileName of the scene and if the scene is currently loaded.
	*/
	struct GameSceneData
	{
		char* fileName;
		bool isLoaded;
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

		using CustomTickEvent = void(*)(void);
		using CustomOnLoad = void(*)(void);

		CustomTickEvent m_tickEvent = nullptr;
		CustomTickEvent m_onLoad = nullptr;

	public:
		//Handles unloading and clearing a scene.
		bool DestroyScene()
		{
			if(m_levelObjects.size() > 0)
				m_levelObjects.clear();
			return true;
		}

		/*
			As long as a function was passed into CreateScene, this will call the function linked to this scene.
		*/
		void SceneTick()
		{
			if (m_tickEvent)
				m_tickEvent();
		}
		/*
			Creaets a scene, This is the constructor as a scene for this class. Returns the GameScene as a pointer. 
			TODO: Make SceneFileFormat, Load File, and finish this system.
		*/
		static GameScene* CreateScene(GameSceneData* sceneData, void* tickFunction = nullptr, void* onLoadEventHandler = nullptr)
		{
			//TODO: Create scene, assign ID.
		}
		
		/*	
			Like the SceneTick() this will get a function passed from CreateScene, and will run the function
			as soon as the scene has loaded in its first frame.
		*/
		void OnLoaded()
		{
			if (m_onLoad)
				m_onLoad();
		}
	};

	/*
	Create a scene from GameSceneData, which holds a filename and a bool if the level is currently loaded. Returns a pointer to
	the new scene that has been created.
*/


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
		std::vector<GameSceneData*> scenes;
		const char* gameName;
		SLE64_WINData* windowData;
	};
#pragma endregion







