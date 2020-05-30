#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
	System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING || mngr_->getClientId() != 0)
		return;

	for (auto& f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ecs::Transform);

		for (auto& otherF : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
			if (otherF != f) {
				Transform* otherFTR = otherF->getComponent<Transform>(ecs::Transform);
				if (Collisions::collidesWithRotation(otherFTR->position_, otherFTR->width_,
					otherFTR->height_, otherFTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {
					auto id = 2;
					mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(id);
					mngr_->send<msg::FighterKill>(id);
				}
			}
		}

		for (auto& b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
				bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
				fTR->height_, fTR->rotation_)) {
				auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
				mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(id);
				mngr_->send<msg::FighterKill>(id);
			}
		}
	}
}