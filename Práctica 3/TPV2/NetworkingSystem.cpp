#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
	System(ecs::_sys_NetWorking) {
}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message& msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	Networking* net = game_->getNetworking();
	msg::Message* msg = nullptr;
	msg::FighterInfoMsg* fighterMensj = nullptr;
	msg::BulletShootMsg* bulletMensj = nullptr;
	msg::FighterKill* killedMensj = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_CONNECTED:
			break;

		case msg::_CONNECTION_REFUSED:
			break;

		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
				static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;

		case msg::_PLAYERS_READY:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_PLAYERS_READY);
			break;

		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_PLAYER_INFO);
			break;

		case msg::_FIGHTER_MOVE:
			fighterMensj = static_cast<msg::FighterInfoMsg*>(msg);
			mngr_->forwardMsg<msg::FighterInfoMsg>(fighterMensj->senderClientId,
				fighterMensj->x, fighterMensj->y, fighterMensj->rotation);
			break;
			
		case msg::_BULLET_SHOOT:
			bulletMensj = static_cast<msg::BulletShootMsg*>(msg);
			mngr_->forwardMsg<msg::BulletShootMsg>(bulletMensj->senderClientId,
				bulletMensj->x, bulletMensj->y, bulletMensj->vel, bulletMensj->playerWhoShot);
			break;
			
		case msg::_FIGHTER_KILLED:
			killedMensj = static_cast<msg::FighterKill*>(msg);
			mngr_->forwardMsg<msg::FighterKill>(killedMensj->senderClientId, killedMensj->playerId);
			break;

		default:
			cout << "UNHANDLED MESSAGE WITH ID " << msg->id << endl;
			assert(false);
			break;
		}
	}
}