#pragma once

#include <ctime>
#include "mpl.h"

// ** Components
//
// They must match the names of your components.
//
struct AsteroidGeneration;
struct GameState;
struct Health;
struct ImageComponent;
struct Score;
struct Transform;

using ComponentsList =
mpl::TypeList<AsteroidGeneration, GameState, Health, ImageComponent, Score, Transform>;

// ** Groups
//
// start them with _grp_ to avoid conflicts (or make a name space)
//
struct _grp_Bullets;
struct _grp_Asteroids;

using GroupsList =
mpl::TypeList<_grp_Bullets, _grp_Asteroids>;

// ** handlers
//
// start them with _grp_ to avoid conflicts (or make a name space)
//
struct _hdlr_GameState;
struct _hdlr_Fighter;

using HandlersList =
mpl::TypeList<_hdlr_Fighter, _hdlr_GameState>;

// ** Systems
//
// they must match the name of the systems classes

class CollisionSystem;
class GameCtrlSystem;
class RenderSystem;
class AsteroidsSystem;
class FighterSystem;
class FighterGunSystem;
class BulletsSystem;

using SystemsList =
mpl::TypeList<CollisionSystem, GameCtrlSystem, RenderSystem, AsteroidsSystem, FighterSystem, FighterGunSystem, BulletsSystem>;

constexpr std::size_t maxComponents = ComponentsList::size;
constexpr std::size_t maxGroups = GroupsList::size;
constexpr std::size_t maxHandlers = HandlersList::size;
constexpr std::size_t maxSystems = SystemsList::size;