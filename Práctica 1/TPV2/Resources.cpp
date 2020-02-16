#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
//
		{ AIIcon, "resources/images/ai.png" }, //
		{ Airplanes, "resources/images/airplanes.png" }, //
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Astreoid, "resources/images/astreoid.png" }, //
		{ Badges, "resources/images/badges.png" }, //
		{ Bird, "resources/images/bird.png" }, //
		{ Black_Hole, "resources/images/black-hole.png" }, //
		{ Blank, "resources/images/blank.png" }, //
		{ Bullet, "resources/images/bullet.png" }, //
		{ Explosion, "resources/images/explosion.png" }, //
		{ Fire_Egg, "resources/images/fireegg.png" }, //
		{ Heart, "resources/images/heart.png" }, //
		{ KeyBoardIcon, "resources/images/keyboard.png" }, //
		{ Life, "resources/images/life.png" }, //
		{ Monster, "resources/images/monster.png" }, //
		{ MouseIcon, "resources/images/mouse.png" }, //
		{ SpaceShips, "resources/images/spaceships.png" }, //
		{ Star, "resources/images/star.png" }, //
		{ TennisBall, "resources/images/tennis_ball.png" }, //
		{ White_Rect, "resources/images/whiterect.png" } //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ PressAnyKey, "Press Any Key ...", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOver, "Game Over", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ Imperial_March, "resources/sound/imperial_march.wav" }, //
		{ Beat, "resources/sound/beat.wav" }

};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Boooo, "resources/sound/boooo.wav" }, //
		{ Cheer, "resources/sound/cheer.wav" }, //
		{ ExplosionSound, "resources/sound/explosion.wav" }, //
		{ GunShot, "resources/sound/GunShot.wav" }, //
		{ Missed, "resources/sound/missed.wav" }, //
		{ Paddle_Hit, "resources/sound/paddle_hit.wav" }, //
		{ Score_Update, "resources/sound/score_update.wav" }, //
		{ Wall_Hit, "resources/sound/wall_hit.wav" } //
};