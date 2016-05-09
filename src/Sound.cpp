#include "Sound.h"
#include <OgreStringConverter.h>

Sound::Sound(bool set) {
	sound = set;
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
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