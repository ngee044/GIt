#pragma once
#include "Object.h"
#include "WorldMgr.h"
#include "CharacterMgr.h"

class World : public Object
{
private:

protected:
	bool GameOver;
public:
	World();
	virtual ~World();

	virtual void Init();
	virtual void Reset();
	virtual void Delete();
	
	int Is_GameOver() { return GameOver; }
	void CreateMapRECT(eTYPE_MAP type, RECT *rc1, RECT *rc2, RECT *rc3, RECT *rc4, RECT *rc5);
	void MapMove(eTYPE_MAP type, RECT *MoveRec, RECT *ReturnRec);
	void GameMapEvent(eTYPE_MAP map, RECT *EventRec1, RECT *EventRec2);
};

