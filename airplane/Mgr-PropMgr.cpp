#include "Mgr-PropMgr.h"
#include"Behavior-PropBehavior.h"
#include "system-engine.h"
#include <random>
#include"system-system.h"
#include "core-Player.h"
#include"system-view.h"
PropManager::PropManager() {
	LoadPropImages();
}
void PropManager::LoadPropImages() {
	prop_images.reserve(11);			//加载道具图片
	loadimage(&prop_images[0], "image\\prop\\0.png",props[0]->rad, props[0]->rad); //道具0
	loadimage(&prop_images[1], "image\\prop\\1.png", props[0]->rad, props[0]->rad); //道具1
	loadimage(&prop_images[2], "image\\prop\\2.png", props[0]->rad, props[0]->rad); //道具2
	loadimage(&prop_images[3], "image\\prop\\3.png", props[0]->rad, props[0]->rad); //道具3
	loadimage(&prop_images[4], "image\\prop\\4.png", props[0]->rad, props[0]->rad); //道具4
	loadimage(&prop_images[5], "image\\prop\\5.png", props[0]->rad, props[0]->rad); //道具5
	loadimage(&prop_images[6], "image\\prop\\6.png", props[0]->rad, props[0]->rad); //道具6
	loadimage(&prop_images[7], "image\\prop\\7.png", props[0]->rad, props[0]->rad); //道具7
	loadimage(&prop_images[8], "image\\prop\\8.png", props[0]->rad, props[0]->rad); //道具8
	loadimage(&prop_images[9], "image\\prop\\9.png", props[0]->rad, props[0]->rad); //道具9
	loadimage(&prop_images[10], "image\\prop\\10.png", props[0]->rad, props[0]->rad); //道具10
}
void PropManager::Produce(Player*pl) {
		prop* p = new prop;
		std::pair<int, int>TypeAndNum = RandomTypeAndNum(pl, p);
		p->type = TypeAndNum.first;
		p->num = TypeAndNum.second;
		p->NowCoord = RandomProduceCoord(p);
		p->app = AppMatchProp(p);
		AddProp(p);
}
void PropManager::AddProp(prop* p) { props.push_back(p); }
bool PropManager::RandomProduce() {
	const double& dif = AllGame::instance().coef;
	double pSuceess = 0.001 + (0.005 - 0.001) * ((1.0 * dif) > 1.0 ? 1.0 : (1.0 * dif));
	double r = RandomDouble(0, 1);
	return r <= pSuceess;
}
static std::unordered_map<prop*, int>UsingProp;
void PropManager::Update(BulletManager& b, EnemyManager& e, Player* player) {
	if(PropManager::RandomProduce())PropManager::Produce(player);
	for (prop* pp : props) {
		if(IsOutRange(pp->NowCoord)){
			pp->alive = false;
		}
		if (pp->alive == false)continue;
		std::pair<double, double>v = PropMoveCoord(pp);
		pp->NowCoord = SystemMove(pp->NowCoord, v.first, v.second);
	}
	for (prop* p : props) {
		if (p->alive == false)continue;
		if (IsCrash(p->NowCoord, p->rad, player->coord, player->rad)) {
		switch (p->type) {
		case 0: {
			switch (p->num) {
			case 0: { PropEffect_DecreaseVShoot(player, p); break; }
			case 1: { PropEffect_IncreaseBulletDamage(player, p); break; }
			case 2: { PropEffect_IncreasePlaneMaxHp(player, p); break; }
			case 3: { PropEffect_IncreasePlaneSpeed(player, p); break; }
			default: { break; }
			}
			p->alive = false;
			break;
		}
		case 1:{
			switch (p->num) {
			case 0: { PropEffect_Heal(player, p); break; }
			case 1: { PropEffect_ClearScreen(b,e,p); break; }
			case 2: { PropEffect_FullScreenBomb(e,p); break; }
			default: { break; }
			}
			p->alive = false;
			break;
		}
		case 2: {
			switch (p->num) {
			case 0: { PropEffect_LaserWeapon(player, p); break; }
			case 1: { PropEffect_SuperBullet(player, p); break; }
			case 2: { PropEffect_DecreaseDif(p); break; }
			case 3: { PropEffect_Invincible(player, p); break; }
			default: { break; }
			}
			UsingProp[p] = AllGame::instance().GameTime;
			break;
		}
		default: { break; }
		}
	}
		}
	for (auto& [p, t] : UsingProp) {
		if (AllGame::instance().GameTime - t >= p->CD) {
			switch (p->num) {
			case 0: {
				player->Vshoot +=9;
				player->AddATK += 5;
				break;
			}
			case 1: {
				player->atk -= 20;
				break;
			}
			case 2: {
				AllGame::instance().AllKill += 100;
				break;
			}
			case 3: {
				player->camp = 0;
				break;
			}
			default: { break; }
			}
			UsingProp.erase(p);
			p->alive = false;
		}
	}
		

}
void PropManager::Render() {
	for (prop* pp : props) {
		switch (pp->type) {
		case 0:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[0]);
			break;
		case 1:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[1]);
			break;
		case 2:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[2]);
			break;
		case 3:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[3]);
			break;
		case 4:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[4]);
			break;
		case 5:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[5]);
			break;
		case 6:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[6]);
			break;
		case 7:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[7]);
			break;
		case 8:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[8]);
			break;
		case 9:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[9]);
			break;
		case 10:
			drawAlpha((int)pp->NowCoord.first - pp->rad / 2, (int)pp->NowCoord.second - pp->rad / 2, &prop_images[10]);
			break;
		
		}
	}
}
void PropManager::GC() {
	//easyx




	//kill
	props.erase(std::remove_if(props.begin(), props.end(),
		[](prop* p) {
			if (!p->alive) {
				if (UsingProp.find(p) != UsingProp.end())UsingProp.erase(p);
				AllKindDestroy(p);
				return true;
			}
			return false;
		}), props.end());
}

