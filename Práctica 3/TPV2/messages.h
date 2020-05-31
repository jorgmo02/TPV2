#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Vector2D.h"

namespace msg {
	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED, //
		_CONNECTION_REFUSED, //
		_CLIENT_DISCONNECTED, //
		_PLAYER_INFO, //
		_PLAYERS_READY,
		_FIGHTER_MOVE, //
		_BULLET_SHOOT,
		_FIGHTER_KILLED,

		//
		_last_MsgId_
	};

#pragma pack(push,1)

	struct Message {
		Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
		}
		Message(MsgId id) :
			Message(sizeof(Message), id) {
		}
		msgSizeType size;
		uint32_t senderClientId;
		MsgId id;
	};

	struct ConnectedMsg : Message {
		ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct ConnectionRefusedMsg : Message {
		ConnectionRefusedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTION_REFUSED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct ClientDisconnectedMsg : Message {
		ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
				clientId) {
		}
		uint32_t clientId;
	};

	struct PlayerInfoMsg : Message {
		PlayerInfoMsg(const char* name) :
			Message(sizeof(PlayerInfoMsg), _PLAYER_INFO) {
			strcpy_s(name_, 11, name);
		}
		char name_[11];
	};

	struct FighterInfoMsg : Message {
		FighterInfoMsg(double x, double y, double rot, MsgId id = _FIGHTER_MOVE) :
			Message(sizeof(FighterInfoMsg), id), x(x), y(y), rotation(rot) {}
		double rotation;
		double x;
		double y;
	};
	
	struct BulletShootMsg : Message {
		BulletShootMsg() : BulletShootMsg(0, 0, {0, 0}) {}
		BulletShootMsg(double x, double y, Vector2D vel) :
			Message(sizeof(BulletShootMsg), _BULLET_SHOOT), x(x), y(y), vel(vel) {}
		double x;
		double y;
		Vector2D vel;
	};
	
	struct FighterKill : Message {
		FighterKill(uint8_t playerId) :
			Message(sizeof(FighterKill), _FIGHTER_KILLED), playerId(playerId) {};
		uint8_t playerId;
	};

#pragma pack(pop)
}
