#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "Directory.h"

class Sound_Effects
{
public:
    ~Sound_Effects();
    ALLEGRO_SAMPLE *sound = NULL;
    ALLEGRO_SAMPLE *game = NULL;

    ALLEGRO_SAMPLE_INSTANCE *instance_game = NULL;

    Search_Dir sound_dir;

//    ALLEGRO_SAMPLE_INSTANCE *instance_game = NULL; // remeber to use it in the UI class

    void load_sound(M_Object *obj);
    void load_music();
    void play_music();
    void stop_music();
    void set_volume(int volume);
};

#endif // SOUND_H_INCLUDED

