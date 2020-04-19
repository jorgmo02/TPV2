#pragma once

#include <list>
#include "SDLGame.h"
#include "DefFactory.h"
#include "ecs.h"
#include "Entity.h"
#include "System.h"
#include "OFFacotry.h"
#include "messages.h"

class Manager {
	using uptr_ent = std::unique_ptr<Entity, std::function<void(Entity*)>>;
	using uptr_msg = std::unique_ptr<msg::Message, std::function<void(msg::Message*)>>;
	using EventType = std::function<void()>;

public:
	Manager(SDLGame* game) :
		game_(game) {
		msgs_ = new std::list<uptr_msg>();

		// needed only when using method flushMessages
		// that uses the std::swap
		supportMsgs_ = new std::list<uptr_msg>();
	}

	virtual ~Manager() {
		delete msgs_;
		delete supportMsgs_;
	}

	// entities
	template<typename FT = DefFactory<Entity>, typename ...Targs>
	inline Entity* addEntity(Targs&&...args) {
		Entity* e = FT::construct(std::forward<Targs>(args)...);
		if (e != nullptr) {
			e->setEntityMngr(this);
			e->resetGroups();
			events_.push_back([this, e]() {
				ents_.emplace_back(e, [](Entity* p) {
					FT::destroy(p);
					});
				});
		}
		return e;
	}

	// groups
	inline void addToGroup(std::size_t grpId, Entity* e) {
		events_.push_back([this, grpId, e]() {
			entsGroups_[grpId].push_back(e);
			});
	}


	// handlers
	template<typename TH>
	inline void setHandler(Entity* e) {
		constexpr std::size_t id = mpl::IndexOf<TH, HandlersList>();
		handlers_[id] = e;
	}

	template<typename TH>
	inline Entity* getHandler() {
		constexpr std::size_t id = mpl::IndexOf<TH, HandlersList>();
		return handlers_[id];
	}

	// systems
	template<typename T, typename ...Targs>
	T* addSystem(Targs&&... args) {
		constexpr std::size_t sysId = mpl::IndexOf<T, SystemsList>();
		T* s = new T(std::forward<Targs>(args)...);
		systems_[sysId] = unique_ptr<T>(s);
		s->setGame(game_);
		s->setMngr(this);
		s->init();
		return s;
	}

	template<typename T>
	T* getSystem() {
		constexpr std::size_t sysId = mpl::IndexOf<T, SystemsList>();
		return static_cast<T*>(systems_[sysId].get());
	}

	// access to lists of entities
	template<typename TG>
	const vector<Entity*>& getGroupEntities() {
		constexpr std::size_t grpId = mpl::IndexOf<TG, GroupsList>();
		return entsGroups_[grpId];
	}

	const std::vector<uptr_ent>& getEntities() {
		return ents_;
	}

	// refresh lists of enteties (remove not active and modify groups)
	void refresh();

	// messaging

	template<typename T, typename FT = OFFacotry<T>, typename ...Ts>
	void send(Ts&&...args) {
		msg::Message* msg = FT::construct(std::forward<Ts>(args)...);
		uptr_msg uPtr(msg, [](msg::Message* p) {
			FT::destroy(static_cast<T*>(p));
			});
		msgs_->push_back(std::move(uPtr));
	}

	// This version uses the swap trick to delay sending
	// message to the next iteration
	//
	void flushMessages() {
		std::swap(msgs_,supportMsgs_);
		while (!supportMsgs_->empty()) {
			uptr_msg msg = std::move(supportMsgs_->front());
			for (auto &s : systems_) {
				s->recieve(*msg);
			}
			supportMsgs_->pop_front();
		}
	}

private:
	SDLGame* game_;
	std::vector<uptr_ent> ents_;
	std::array<std::vector<Entity*>, maxGroups> entsGroups_;
	std::array<Entity*, maxHandlers> handlers_;
	std::array<unique_ptr<System>, maxSystems> systems_;

	std::list<std::function<void()>> events_;
	std::list<uptr_msg>* msgs_;
	std::list<uptr_msg>* supportMsgs_;

};
