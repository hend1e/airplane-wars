#include "arch/behavior/PlayerBehavior.h"
#include "arch/system/engine.h"
std::pair<int,int>CalcuPlayerMove(Player* p) {

}
std::pair<int,int>ProducePlayer(Player* p) {
	int screenX = AllGame::instance().ScreenX;
	int screenY = AllGame::instance().ScreenY;

	// x = 屏幕中点
	int x = screenX / 2;

	// y = 屏幕底部往上 1/8
	int y = (screenY * 7) / 8;

	return {x,y};
}