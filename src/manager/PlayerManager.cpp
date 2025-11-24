#include "arch/manager/PlayerManager.h"
#include "arch/system/engine.h"
#include "arch/behavior/PlayerBehavior.h"
#include"arch/system/view.h"
#include"arch/system/system.h"
PlayerManager::PlayerManager() {}
void PlayerManager::Produce() {
	Player*player=new Player();
	player->coord=ProducePlayer(player);
	player->NowHp=player->maxHp=100;
	players.push_back(player);
}
void PlayerManager::Update() {
	for (auto& player : players) {
		if (player->NowHp<=0) {AllKindDestroy(player);GameOverView();}
		player->coord=CalcuPlayerMove(player);
	}
}
void PlayerManager::Render() {

}
void PlayerManager::GC() {

}

