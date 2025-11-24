#ifndef AIRPLANE_WARS_BULLET_MANAGER_H
#define AIRPLANE_WARS_BULLET_MANAGER_H

#include <vector>
#include "arch/core/bullet.h"
#include"arch/behavior/PlaneBehavior.h"
class BulletManager {
public:
	std::vector<bullet*> bullets;
	void Produce(const std::vector<Player*>&p, const std::vector<Enemy*>& es);
	void AddBullet(bullet* b);
	void Update(const std::vector<Player*>&p, const std::vector<Enemy*>& es);
	void Render();
	void GC();
};


#endif
