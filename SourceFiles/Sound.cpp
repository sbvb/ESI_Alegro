#include "Allegro_esi.h"
using namespace std;

Sound_Effects::~Sound_Effects()
{
    al_destroy_sample(sound);
    al_destroy_sample(game);
    al_destroy_sample_instance(instance_game);
}
void Sound_Effects::load_sound(M_Object *obj)
{
    Search_Dir sound_dir;

    string diretorio = "Sounds\\Shot\\";

    sound_dir.load_files(diretorio);

    sound = al_load_sample(sound_dir.container[0].c_str()); //shots points to the sound previously
                                                                //charged similar to bitmaps
    if (!sound){
        cout <<  "Audio clip sample not loaded!\n" << endl;
    }

    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Sound_Effects::load_music() //play the background sound
{
    Search_Dir sound_game_dir;

    string snd_dir = "Sounds\\Game_Sound\\";

    sound_game_dir.load_files(snd_dir);

    //ADD ERROR TREATISING

    game = al_load_sample(sound_game_dir.container[0].c_str());//shots points to the sound previously
                                                                //charged similar to bitmaps
    if (!game){
        cout <<  "Audio clip sample not loaded!\n" << endl;
    }

    instance_game = al_create_sample_instance(game);
    al_set_sample_instance_playmode(instance_game, ALLEGRO_PLAYMODE_LOOP); //Set the playback mode.
    al_attach_sample_instance_to_mixer(instance_game, al_get_default_mixer()); //Attach instance_game
                                                                               //to default mixer.
}

void Sound_Effects::play_music()
{
    al_play_sample_instance(instance_game); //Play an instance of a sample data.
}
void Sound_Effects::stop_music()
{
    al_stop_sample_instance(instance_game);
}

void Sound_Effects::set_volume(int volume)
{
    al_set_sample_instance_gain(instance_game, volume);
}
