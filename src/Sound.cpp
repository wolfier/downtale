#include "Sound.h"
#include <OgreStringConverter.h>

Sound::Sound(bool set) {
	sound = set;
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
    Mix_Chunk* bg = Mix_LoadWAV(("media/sounds/bg.ogg"));
    if(sound){
		Mix_PlayChannel(-1, bg, 10);
		printf("player\n");
	}

}

Sound::~Sound() {

}

bool Sound::getSound(){
	return sound;
}

void Sound::mute(){
	sound = !sound;
}

void Sound::playShatter(int x){
    Mix_Chunk* shatter = Mix_LoadWAV(("media/sounds/shatter"+std::to_string(x)+".ogg").c_str());
	if(sound){
		Mix_PlayChannel(-1, shatter, 0);
		printf("player\n");
	}
}

void Sound::playShield(){
    Mix_Chunk* shatter = Mix_LoadWAV(("media/sounds/shield.ogg"));
	if(sound){
		Mix_PlayChannel(-1, shatter, 0);
		printf("player\n");
	}
}

void Sound::playFuel(){
    Mix_Chunk* shatter = Mix_LoadWAV(("media/sounds/fuel.ogg"));
	if(sound){
		Mix_PlayChannel(-1, shatter, 0);
		printf("player\n");
	}
}