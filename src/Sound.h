#ifndef __Sound_h_
#define __Sound_h_

#include <SDL_mixer.h>

class Sound {
protected:

public:
    Sound(bool set);
    virtual ~Sound();
    void mute();
    bool getSound();
    void playGroundCollide();
    void playTableCollide();
    void playPaddleCollide();
    void playPaddleSwing();

    bool              sound;
    Mix_Chunk*        wosh;
    Mix_Chunk*        ping;
    Mix_Chunk*        pong;
    Mix_Chunk*        ding;

};

//---------------------------------------------------------------------------

#endif // #ifndef __Sound_h_

//---------------------------------------------------------------------------