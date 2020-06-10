#include "CollisionSystem.h"
#include "Collisions.h"
#include "FoodSystem.h"
#include "GameState.h"
#include "GhostsSystem.h"
#include "Manager.h"
#include "Transform.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collisions) {
}

void CollisionSystem::update() {

	auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
	if (gameState->state_ != GameState::RUNNING)
		return;

	Entity* pacmanEntity = mngr_->getHandler(ecs::_hdlr_PacManEntity);	// guardar referencia por si pudiera hacer falta en el mensaje de la colisión
	auto ptr = pacmanEntity->getComponent<Transform>(ecs::Transform);

	// collision with food
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Food)) {
		auto etr = e->getComponent<Transform>(ecs::Transform);
		if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_,
			etr->position_, etr->width_, etr->height_)) {
			mngr_->send<msg::CollisionMessage>(msg::_PACMAN_TSUKKI_COLLISION, pacmanEntity, e);
		}
	}

	// collision with ghosts
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Ghost)) {
		auto etr = e->getComponent<Transform>(ecs::Transform);
		if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_,
			etr->position_, etr->width_, etr->height_)) {
			mngr_->send<msg::CollisionMessage>(msg::_PACMAN_GHOST_COLLISION, pacmanEntity, e);
			break;
		}
	}
}
