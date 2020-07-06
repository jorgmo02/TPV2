#pragma once
#include <ctime>

class Entity;

namespace msg {

	using msgType = std::size_t;

	enum MsgId : msgType {
		_GAME_START,				// Comienza una nueva partida (State = running)
		_GAME_OVER,					// Pacman no tiene m�s vidas
		_GAME_RESET,				// El jugador comienza una nueva partida
		_PACMAN_DEAD,				// Pacman pierde una vida
		_GHOST_DEAD,				// Pacman pierde una vida
		_NO_MORE_TSUKKIS,			// No queda Food (gana el jugador)
		_ADD_GHOSTS,				// Petici�n de a�adir fantasmas
		_ADD_TSUKKIS,				// Petici�n de a�adir comida
		_ADD_BONUS,					// Petici�n de a�adir bonus
		_PACMAN_GHOST_COLLISION,	// Colisi�n (pacman con fantasma)
		_PACMAN_TSUKKI_COLLISION,	// Colisi�n (pacman con comida)
		_PACMAN_BONUS_COLLISION,	// Colisi�n (pacman con fresa)
		_BONUS_END,					// Bonus se acaba

		//
		_last_MsgId_
	};

	struct Message {
		Message(MsgId id) :
			id(id) {
		}

		MsgId id;
	};

	// sirve para cualquier tipo de objeto que se quiera a�adir
	struct AddItemMessage : Message {
		AddItemMessage(MsgId id, size_t numItems) :
			Message(id), numItems_(numItems) {
		}

		size_t numItems_;
	};

	// sirve para cualquier tipo de colisi�n entre dos entidades
	struct CollisionMessage : Message {
		CollisionMessage(MsgId id, Entity* main, Entity* collidedWith) :
			Message(id), main_(main), collidedWith_(collidedWith) {
		}

		// main siempre es el pacman, pero alg�n sistema podr�a querer usarlo en una futura ampliaci�n
		Entity *main_ = nullptr, *collidedWith_ = nullptr;
	};
}
