#ifndef AIRPLANE_WARS_ENEMY_MANAGER_H
#define AIRPLANE_WARS_ENEMY_MANAGER_H

#include <vector>
#include "arch/core/Enemy.h"
#include "arch/system/system.h"

class EnemyManager {
public:
	EnemyManager();

	std::vector<Enemy*> enemies;
	void Produce();
	void Update();
	void Render();
	void GC();
};


#endif
