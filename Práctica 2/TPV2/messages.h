#pragma once
#include <ctime>
#include "Vector2D.h"

class Entity;

namespace msg {

	using msgType = std::size_t;

	enum MsgId : msgType {
		_FIGHTER_ASTEROID_COLLISION_, //
		_BULLET_ASTEROID_COLLISION_,
		_NO_MORE_ASTEROIDS_,
		_SHOOT_,
		_DISABLE_ALL_,
		_NEW_TRY_,

		//
		_last_MsgId_
	};

	struct Message {
		Message(MsgId id) :
			id(id) {
		}

		MsgId id;
	};

	struct FighterAsteroidCollisionMsg : Message
	{
		FighterAsteroidCollisionMsg(Entity* asteroid, Entity* fighter) :
			Message(_FIGHTER_ASTEROID_COLLISION_), //
			fighter_(fighter), asteroid_(asteroid) {
		}

		Entity* asteroid_;
		Entity* fighter_;
	};

	struct BulletAsteroidCollisionMsg : Message
	{
		BulletAsteroidCollisionMsg(Entity* asteroid, Entity* bullet) :
			Message(_BULLET_ASTEROID_COLLISION_), //
			bullet_(bullet), asteroid_(asteroid) {
		}

		Entity* asteroid_;
		Entity* bullet_;
	};

	struct ShootMsg : Message
	{
		ShootMsg(Vector2D pos, double rot) :
			Message(_SHOOT_), //
			pos_(pos), rot_(rot) {
		}

		Vector2D pos_;
		double rot_;
	};
}