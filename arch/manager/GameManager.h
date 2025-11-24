#ifndef AIRPLANE_WARS_GAME_MANAGER_H
#define AIRPLANE_WARS_GAME_MANAGER_H

#include "arch/behavior/PlayerBehavior.h"
#include "arch/manager/EnemyManager.h"
#include "arch/manager/BulletManager.h"
#include "arch/manager/PropManager.h"
#include "arch/manager/PlayerManager.h"
#include "arch/system/engine.h"

class GameManager {
public:
	PlayerManager playerMgr;
	EnemyManager enemyMgr;
	BulletManager bulletMgr;
	PropManager propMgr;

	void Update();
	void Render();
	void CG();
};


#endif
