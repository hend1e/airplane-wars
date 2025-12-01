#include "Mgr-EnemyMgr.h"
#include<vector>
#include <algorithm>
#include "Behavior-EnemyBehavior.h"
#include "core-Enemy.h"
#include"system-engine.h"
#include"system-view.h"
EnemyManager::EnemyManager() {
	LoadEnemyImages();
}
void EnemyManager::LoadEnemyImages() {
	enemy_images.resize(3);//3种敌机图片
	loadimage(&enemy_images[0], "image\\enemy\\common.jpg",enemies[0]->rad, enemies[0]->rad);
	loadimage(&enemy_images[1], "image\\enemy\\elite.jpg", enemies[1]->rad, enemies[1]->rad);
	loadimage(&enemy_images[2], "image\\enemy\\boss.jpg", enemies[2]->rad, enemies[2]->rad);
}
static bool IsProduce() {
	auto Lerp = [](double a, double b, double t) {
		return a + (b - a) * t;
		};
	double min_prob = 0; // 最小生成概率
	double max_prob = 0.05; // 最大生成概率
	double current_prob = Lerp(min_prob, max_prob, AllGame::instance().coef);

	// 生成随机数并判断是否生成敌机
	double rand_val = RandomDouble(0, 1);
	return rand_val <= current_prob;
}
void EnemyManager::Produce() {
	Enemy* e = new Enemy();
	e->coord = RandomLocationProduce(e);
	auto [modol, type] = RandomModelAndTypeWithCoef(e);
	e->modol = modol;
	e->type = type;
	e->NowHp = e->maxHp = MaxHpMatchType(e);
	e->rad = RadMatchType(e);
	e->camp = 1;
	e->Vshoot = 120;
	e->alive = true;
	enemies.push_back(e);
}

void EnemyManager::Update(Player*p) {
	if (IsProduce())EnemyManager::Produce();
	for (auto& ee : enemies) {
		if (IsOutRange(ee->coord) || ee->NowHp <= 0) {
			if (ee->NowHp <= 0)AllGame::instance().AllKill++;
			ee->alive = false;
		}
		if (ee->alive == false)continue;
		ee->coord = CalculateEnemy(ee,p);
	}
}
void EnemyManager::Render() {
	for (auto& ee : enemies) {
		switch (ee->type) {
		case 0:
			
			drawAlpha((int)ee->coord.first - ee->rad / 2, (int)ee->coord.second - ee->rad / 2, &enemy_images[0]);
			break;
		case 1:
		
			drawAlpha((int)ee->coord.first - ee->rad / 2, (int)ee->coord.second - ee->rad / 2, &enemy_images[1]);
			break;
		case 2:
			
			drawAlpha((int)ee->coord.first - ee->rad / 2, (int)ee->coord.second - ee->rad / 2, &enemy_images[2]);
			break;
		}
	}

}
void EnemyManager::GC() {
	//esayx





	//kill
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](Enemy* e) {
				if (!e->alive) {
					AllKindDestroy(e);
					return true;
				}
				else return false;
			}), enemies.end()
				);
}



