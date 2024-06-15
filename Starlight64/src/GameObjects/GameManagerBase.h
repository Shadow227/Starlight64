#pragma once

/*
	The GameManager class is a global class that only one should ever exist of. The
	base game manager below is able to manage most simple games, though is meant to be
	expanded upon to add more features one may need. Taking inspration from unreal engines
	GameInstance class.
*/
class GameManagerBase
{
	//Game Globals
private:
	int m_playerCount;
	bool isGamePaused;
};

