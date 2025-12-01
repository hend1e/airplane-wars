#include "Behavior-PlaneBehavior.h"

#include "Behavior-BulletBehavior.h"

#include "Mgr-BulletMgr.h"
#include "system-system.h"
#include"system-view.h"
#include "core-bullet.h"
#include "core-Enemy.h"
#include "core-Player.h"
BulletManager::BulletManager() {
	LoadResources();
}
void BulletManager::LoadResources() {
	bulletImgs.resize(11);   // 10种子弹图片

	loadimage(&bulletImgs[0], "image\\bullet\\bullet0.png",bullets[0]->rad, bullets[0]->rad);
	loadimage(&bulletImgs[1], "image\\bullet\\bullet1.jpg", bullets[1]->rad, bullets[1]->rad);
	loadimage(&bulletImgs[2], "image\\bullet\\bullet2.jpg", bullets[2]->rad, bullets[2]->rad);
	loadimage(&bulletImgs[3], "image\\bullet\\bullet3.png", bullets[3]->rad, bullets[3]->rad);
	loadimage(&bulletImgs[4], "image\\bullet\\bullet4.png", bullets[4]->rad, bullets[4]->rad);
	loadimage(&bulletImgs[5], "image\\bullet\\bullet5.jpg", bullets[5]->rad,bullets[5]->rad);
	loadimage(&bulletImgs[6], "image\\bullet\\bullet6.png", bullets[6]->rad, bullets[6]->rad);
	loadimage(&bulletImgs[7], "image\\bullet\\bullet7.png", bullets[7]->rad, bullets[7]->rad);
	loadimage(&bulletImgs[8], "image\\bullet\\bullet8.jpg", bullets[8]->rad, bullets[8]->rad);
	loadimage(&bulletImgs[9], "image\\bullet\\bullet9.jpg", bullets[9]->rad, bullets[9]->rad);
	loadimage(&bulletImgs[10], "image\\bullet\\bullet10.png", bullets[10]->rad, bullets[10]->rad);
}

void BulletManager::AddBullet(bullet* b) {
	bullets.push_back(b);
}
void BulletManager::Produce(const std::vector<Player*>& p, const std::vector<Enemy*>& es) {
	for (Player* pp : p) {
		if (ShouldFire(pp)) {
			bullet* b = new bullet();
			if (pp->Vshoot != 1)b->app = 9;//玩家--直线ans斜线子弹
			else b->app=10;//玩家--激光子弹
			b->Type = (RandomInt(0, 99)<=90?0:1);//玩家子弹类型随机
			switch (b->Type) {
			case 0: { auto [vx, vy] = LineBullet(b); b->vx = vx; b->vy = vy; break; }
			case 1: { auto [vx, vy] = BiasBullet(b); b->vx = vx; b->vy = vy; break; }
			case 2: {
				auto [vx, vy] = TracedBullet(b, pp);
				b->vx = vx; b->vy = vy; break;
			}
			default:{ auto [vx, vy] = LineBullet(b); b->vx = vx; b->vy = vy; break; }
			}
			b->camp = 0;
			b->NowCoord = pp->coord;
			b->alive = true;
			b->ATK += pp->AddATK;
			AddBullet(b);
		}
	}
	for (Enemy* ee : es) {
		if (ShouldFire(ee)) {
			bullet* b = new bullet();
			auto [ATK, Type, Rad] = RandomAtkAndTypeAndRad(ee, b);
			b->ATK = ATK;
			b->Type = Type;
			b->rad = Rad;
			b->app = AppMatchEnemyType(ee,b);
			switch (b->Type) {
			case 0: { auto [vx, vy] = LineBullet(b); b->vx = vx; b->vy = vy; break; }
			case 1: { auto [vx, vy] = BiasBullet(b); b->vx = vx; b->vy = vy; break; }
			case 2: 
				auto [vx, vy] = TracedBullet(b, p[0]);
				b->vx = vx; b->vy = vy; break;
			}
			b->camp = 1;
			b->NowCoord = ee->coord;
			b->alive = true;
			AddBullet(b);
		}
	}
}
void BulletManager::Update(const std::vector<Player*>& p, const std::vector<Enemy*>& es) {
	//2.生成子弹
	void Produce(const std::vector<Player*>&p, const std::vector<Enemy*>&es);

	//3. 移动子弹
	for (bullet* b : bullets) {		
		if (IsOutRange(b->NowCoord)) {
			b->alive = false;
		}
		if (b->alive == false) continue;
		b->NowCoord = CalcuBulletMove(b,p[0]);
	}

	//4. 碰撞检测
	for (bullet* b : bullets) {
		if (b->alive == false) continue;
		if (b->camp == 0) {
			// 玩家子弹 → 打敌机
			for (Enemy* e : es) {
				if (!IsSameCamp(e->camp, b->camp) && IsCrash(b->NowCoord, b->rad, e->coord, e->rad)) {
					e->NowHp -= b->ATK;
					b->alive = false;
				}
			}
		}
		else {
			// 敌机子弹 → 打玩家
			for (Player* pp : p) {
				if (!IsSameCamp(pp->camp, b->camp) && IsCrash(b->NowCoord, b->rad, pp->coord, pp->rad)) {
					pp->NowHp -= b->ATK;
					b->alive = false;
				}
			}
		}
	}


}
void BulletManager::Render() {
	for (bullet* b : bullets) {
		switch (b->app) {
		case 0:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[0]);
			break;
		case 1:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[1]);
			break;
		case 2:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[2]);
			break;
		case 3:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[3]);
			break;
		case 4:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[4]);
			break;
		case 5:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[5]);
			break;
		case 6:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[6]);
			break;
		case 7:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[7]);
			break;
		case 8:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[8]);
			break;
		case 9:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[9]);
			break;
		case 10:
			drawAlpha((int)b->NowCoord.first - b->rad / 2, (int)b->NowCoord.first - b->rad / 2, &bulletImgs[10]);
			break;
		}

	}
}
void BulletManager::GC() {
	//easyx




	//kill
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](bullet* b) {
				if (!b->alive) {
					AllKindDestroy(b);
					return true;
				}
				else return false;
			}),
		bullets.end()
	);
}