#pragma once
#include <ctime>

class Entity;

namespace msg {

	using msgType = std::size_t;

	enum MsgId : msgType {
		_GAME_START,
		_GAME_OVER,
		_PACMAN_DEAD,
		_NO_MORE_TSUKKIS,
		_ADD_GHOSTS,
		_ADD_TSUKKIS,
		_PACMAN_GHOST_COLLISION,
		_PACMAN_TSUKKI_COLLISION,

		//
		_last_MsgId_
	};

	struct Message {
		Message(MsgId id) :
			id(id) {
		}

		MsgId id;
	};

	// sirve para cualquier tipo de objeto que se quiera añadir
	struct AddItemMessage : Message {
		AddItemMessage(MsgId id, size_t numItems) :
			Message(id), numItems_(numItems) {
		}

		size_t numItems_;
	};

	// sirve para cualquier tipo de colisión entre dos entidades
	struct CollisionMessage : Message {
		CollisionMessage(MsgId id, Entity* main, Entity* collidedWith) :
			Message(id), main_(main), collidedWith_(collidedWith) {
		}

		// main siempre es el pacman, pero algún sistema podría querer usarlo en una futura ampliación
		Entity *main_ = nullptr, *collidedWith_ = nullptr;
	};
}
