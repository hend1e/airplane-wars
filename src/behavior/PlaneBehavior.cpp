#include "arch/behavior/PlaneBehavior.h"
#include "arch/system/engine.h"

bool ShouldFire(plane* p) {
	if (p->Vshoot <= 0) return false;
	return AllGame::instance().frameCount % p->Vshoot == 0;
}
