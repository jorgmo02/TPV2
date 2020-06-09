#pragma once
#include <ctime>

class Entity;

namespace msg {

using msgType = std::size_t;

enum MsgId : msgType {
	_GAME_START, _GAME_OVER,

	//
	_last_MsgId_
};

struct Message {
	Message(MsgId id) :
			id(id) {
	}

	MsgId id;
};

}
