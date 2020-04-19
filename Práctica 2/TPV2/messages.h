#pragma once
#include <ctime>

class Entity;

namespace msg {

	using msgType = std::size_t;

	enum MsgId : msgType {
		_FIGHTER_ASTEROID_COLLISION_, //
		_BULLET_ASTEROID_COLLISION_,
		_NO_MORE_ASTEROIDS_,
		_ADD_ASTEROIDS_REQUEST_,
		_GAME_OVER, //


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
		BulletAsteroidCollisionMsg(Entity* asteroid, Entity* bullet_) :
			Message(_BULLET_ASTEROID_COLLISION_), //
			bullet_(bullet_), asteroid_(asteroid) {
		}

		Entity* asteroid_;
		Entity* bullet_;
	};
}