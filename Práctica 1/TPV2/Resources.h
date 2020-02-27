#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId : int {
		// images
		AIIcon,
		Airplanes,
		Asteroid,
		Astreoid,
		Badges,
		Bird,
		Black_Hole,
		Blank,
		Bullet,
		Explosion,
		Fire_Egg,
		Heart,
		KeyBoardIcon,
		Life,
		Monster,
		MouseIcon,
		SpaceShips,
		Star,
		TennisBall,
		White_Rect,

		// text
		HelloWorld,
		PressAnyKey,
		GameOver,
		YouWon,
		YouLost
	};

	enum AudioId : int {
		// music
		Beat,
		Imperial_March,

		// sound effects
		Boooo,
		Cheer,
		ExplosionSound,
		GunShot,
		Missed,
		Paddle_Hit,
		Score_Update,
		Wall_Hit
	};

	enum FontId : int {
		ARIAL16, ARIAL24,
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

};
