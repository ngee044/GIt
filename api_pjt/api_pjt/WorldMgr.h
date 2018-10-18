#pragma once
#include "Singleton.h"
#include <list>
#include "eType.h"
#include "World.h"
#include "Collision.h"

//typedef std::list <World*> _WOLRDLIST;

class BitMap;
class World;
class Collision;

class WorldMgr : public Singleton<WorldMgr>
{
private:
	BitMap *bitmap;
	bool m_gameover;
	World *m_worldClass;
	Collision *m_collsion;
	int m_mapstatus;
	bool isMoveOrReturn; // true-> 다음맵으로 이동 false-> 이전 맵으로 이동

protected:
	RECT rc1, rc2, rc3, rc4, rc5;
	RECT MoveRec, ReturnRec;
	RECT EventRec1, EventRec2;

public:
	WorldMgr();
	~WorldMgr();

	void Init();
	void CreatBattle();
	void Reset();
	void Delete();
	bool GetRectValue();
	bool ChangeMap();
	void SetMapStatus(int idx) { m_mapstatus = idx; }
	int GetMapStatus() { return m_mapstatus; }
	bool GetMoveMapInfo() { return isMoveOrReturn; }
	void GetMapInfo();
	void MoveLocation();
	void MapEvent(eTYPE_EVENT type);
	
};

