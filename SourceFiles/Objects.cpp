// Programa para tentar criar um Menu básico contendo:
// Opções : mudança no menu
// Fechar : Fechar o programa
// Lista encadeada de objetos buga apos uma limpeza , o final fica apontando para algo indefinido
#include "Allegro_esi.h"


using namespace std;

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER, KEY_Z, KEY_X, KEY_C , KEY_SPACE
};

/*********

*********/
int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    if(!al_init()){
        cout << "failed to initialize allegro!" << endl;
        return -1;
    }
    if(!al_install_audio()){
        cout << "failed to initialize audio!" << endl;
        return -1;
    }
    if(!al_init_acodec_addon()){
        cout << "failed to initialize audio codecs!" << endl;
        return -1;
    };
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    srand(time(NULL));


    ALLEGRO_BITMAP *mnuNew_game = al_load_bitmap("Images\\Menu\\mnuNewGame.png");
    if(!mnuNew_game)
    {
        cout << "couldn't load image!" << endl;
    }
    ALLEGRO_BITMAP *mnuExit = al_load_bitmap("Images\\Menu\\mnuExit.png");
    ALLEGRO_BITMAP *mnuOptions = al_load_bitmap("Images\\Menu\\mnuOptions.png");

    ALLEGRO_BITMAP *mnuNew_gameS = al_load_bitmap("Images\\Menu\\mnuNewGameS.png");
    ALLEGRO_BITMAP *mnuExitS = al_load_bitmap("Images\\Menu\\mnuExitS.png");
    ALLEGRO_BITMAP *mnuOptionsS = al_load_bitmap("Images\\Menu\\mnuOptionsS.png");
    ALLEGRO_BITMAP *help1 = al_load_bitmap("Images\\Help\\Help1.png");
    ALLEGRO_BITMAP *gameStart1 = al_load_bitmap("Images\\Help\\count1.png");
    ALLEGRO_BITMAP *gameStart2 = al_load_bitmap("Images\\Help\\count2.png");
    ALLEGRO_BITMAP *gameStart3 = al_load_bitmap("Images\\Help\\count3.png");
    ALLEGRO_BITMAP *gameStart4 = al_load_bitmap("Images\\Help\\count4.png");

    ALLEGRO_BITMAP *bitmap = NULL;
    ALLEGRO_BITMAP *bitmap2 = NULL;

    bitmap  = al_create_bitmap(200,600);
    bitmap2 = al_create_bitmap(200,600);

    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(0,0,0));

    al_set_target_bitmap(bitmap2);
    al_clear_to_color(al_map_rgb(0,0,0));

    if (!al_reserve_samples(20))
    {
        cout << "failed to reserve samples!\n" << endl;
        return -1;
    }


    bool redraw = false;
    bool doexit = false;
    bool initMenu = true;
    bool dogame = false;

    bool key[8] = {false, false, false, false, false, false, false, false};

    Object *spaceship;
    spaceship = new Object();

    M_Object *shots;
    shots = NULL;
    M_Object *enemies;
    enemies = NULL;

    Sound_Effects Sounds;

    int menuSelection = 1;
    int contador = 0;
    int count_pressed = 0;
    int enem_mov_flag = 0;

    display = al_create_display(Width,Height);
    timer = al_create_timer(1.0/FPS);
    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    // Pintando o background e desenhando o bitmap//
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(100,100,100));

    // Flip display trás o background desenhado para a tela//
    al_flip_display();
    al_start_timer(timer);

    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);


///-/////////////////////////////////////////////////////////////////////-///
///------------------------------ MENU LOOP ------------------------------///
///-/////////////////////////////////////////////////////////////////////-///

        if(initMenu && !dogame)
        {

            if(ev.type == ALLEGRO_EVENT_TIMER)
            {

                if(key[KEY_UP] || key[KEY_DOWN])
                {
                    count_pressed++;
                    if((count_pressed == FPS/6) && key[KEY_UP])
                    {
                        menuSelection = (menuSelection-1) + 3*(1 - 7%menuSelection);
                        count_pressed = 0;
                    }
                    if((count_pressed == FPS/6) && key[KEY_DOWN])
                    {
                        menuSelection = (1 - (menuSelection+1)/4)*menuSelection +1;
                        count_pressed = 0;
                    }
                }
                if(!key[KEY_UP] && !key[KEY_DOWN])
                {
                    count_pressed = 0;
                }
                redraw = true;

            }

            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        key[KEY_UP] = true;
                        menuSelection = (menuSelection-1) + 3*(1 - 7%menuSelection);
                        break;
                    case ALLEGRO_KEY_DOWN:
                        key[KEY_DOWN] = true;
                        menuSelection = (1 - (menuSelection+1)/4)*menuSelection +1;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if(menuSelection == 1)
                        {
                            cout << "loading.";
                            spaceship->set_obj(Width/2 - 60, Height - 120, 300, 100);
                            spaceship->select_image("Images\\Ship\\");
                            for( int i = 0; i < 10; i++)
                            {
                                enemies = enemies->create_each(enemies, 250 + (i*45), 50, 60, 3, true, 45);
                                enemies->select_image("Images\\Enemies\\");
                                enemies = enemies->create_each(enemies, 250 + (i*45), 100, 60, 3, true, 45);
                                enemies->select_image("Images\\Enemies\\");
                                enemies = enemies->create_each(enemies, 250 + (i*45), 150, 60, 3, true, 45);
                                enemies->select_image("Images\\Enemies\\");

                            }
                            al_set_target_bitmap(al_get_backbuffer(display));
                            al_clear_to_color(al_map_rgb(100,100,100));
                            cout << ".";
                            al_draw_bitmap( bitmap, 0, 0, 0);
                            al_draw_bitmap( bitmap2, 800, 0, 0);

                            spaceship->draw();
                            Draw_Multi(enemies);
                            al_flip_display();
                            cout << "." << endl;

                            Sounds.load_music();
                            al_rest(0.2);
                            cout << "done!" << endl;
                            initMenu = false;
                            dogame = true;
                            Sounds.play_music();
                        }
                        if(menuSelection == 3)
                        {
                            doexit = true;
                        }
                        break;
                    case ALLEGRO_KEY_Z:
                        break;
                }
            }

            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        key[KEY_UP] = false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        key[KEY_DOWN] = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        doexit = true;
                        break;
                }
            }

            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }

             if(redraw && al_is_event_queue_empty(event_queue))
            {
                redraw = false;
                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(100,100,100));
                if( menuSelection == 1)
                {
                    al_draw_bitmap(mnuNew_gameS, 410, 300, 0);
                    al_draw_bitmap(mnuOptions, 430, 340, 0);
                    al_draw_bitmap(mnuExit, 476, 380, 0);
                }
                if( menuSelection == 2)
                {
                    al_draw_bitmap(mnuNew_game, 410, 300, 0);
                    al_draw_bitmap(mnuOptionsS, 430, 340, 0);
                    al_draw_bitmap(mnuExit, 476, 380, 0);
                }
                if( menuSelection == 3)
                {
                    al_draw_bitmap(mnuNew_game, 410, 300, 0);
                    al_draw_bitmap(mnuOptions, 430, 340, 0);
                    al_draw_bitmap(mnuExitS, 476, 380, 0);
                }

                al_flip_display();
            }
        }

///-/////////////////////////////////////////////////////////////////////-///
///------------------------------ GAME LOOP ------------------------------///
///-/////////////////////////////////////////////////////////////////////-///

        if(dogame && !initMenu)
        {
            if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                if(contador > 195)
                {
                    if(key[KEY_LEFT] && spaceship->positionX >= 185)
                    {
                        spaceship->movement(180);
                    }
                    if(key[KEY_RIGHT] && spaceship->positionX <= 695)
                    {
                        spaceship->movement(0);
                    }
                    Object_Collision(shots, enemies);

                    shots = shots->Clean_list(shots, false);
                    Update_Objects(shots, 1);

                    enemies = enemies->Clean_list(enemies, false);
                    Enemies_movement(enemies, enem_mov_flag);
                    Update_Objects(enemies, enem_mov_flag);
                }
                if(contador < 200)
                {
                    contador ++;
                }

                redraw = true;
            }

            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        break;
                    case ALLEGRO_KEY_DOWN:
                        break;
                    case ALLEGRO_KEY_LEFT:
                        key[KEY_LEFT] = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        key[KEY_RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_Z:
                        key[KEY_Z] = true;
                        shots = shots->create_each(shots, spaceship->positionX + 50, spaceship->positionY, 300, 2, false, 20);
                        shots->select_image("Images\\Shots\\G1\\");
                        Sounds.load_sound( shots);
                        break;
                    case ALLEGRO_KEY_X:
                        key[KEY_X] = true;
                        shots = shots->create_each(shots, spaceship->positionX + 50, spaceship->positionY, 300, 1, false, 20);
                        shots->select_image("Images\\Shots\\G1\\");
                        Sounds.load_sound( shots);
                        break;
                    case ALLEGRO_KEY_C:
                        key[KEY_C] = true;
                        shots = shots->create_each(shots, spaceship->positionX + 50, spaceship->positionY, 300, 0, false, 20);
                        shots->select_image("Images\\Shots\\G1\\");
                        Sounds.load_sound( shots);
                        break;
                    case ALLEGRO_KEY_SPACE:
                        break;
                }
            }

            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        break;
                    case ALLEGRO_KEY_DOWN:
                        break;
                    case ALLEGRO_KEY_LEFT:
                        key[KEY_LEFT] = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        key[KEY_RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        shots = shots->Clean_list(shots, true);
                        enemies = enemies->Clean_list(enemies, true);
                        Sounds.stop_music();
                        dogame = false;
                        initMenu = true;
                        break;
                    case ALLEGRO_KEY_Z:
                        key[KEY_Z] = false;
                        break;
                }
            }

            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                shots = shots->Clean_list(shots, true);
                enemies = enemies->Clean_list(enemies, true);
                break;
            }

            if(redraw && al_is_event_queue_empty(event_queue))
            {
                redraw = false;
                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(100,100,100));

                al_draw_bitmap( bitmap, 0, 0, 0);
                al_draw_bitmap( bitmap2, 800, 0, 0);
                al_draw_bitmap( help1, 0, 100, 0);
                if(contador < 60)
                {
                    al_draw_bitmap( gameStart1, 150, 100, 0);
                }
                else if(contador < 120)
                {
                    al_draw_bitmap( gameStart2, 150, 100, 0);
                }
                else if(contador < 180)
                {
                    al_draw_bitmap( gameStart3, 150, 100, 0);
                }
                else if(contador < 200)
                {
                    al_draw_bitmap( gameStart4, 400, 100, 0);
                }

                spaceship->draw();
                Draw_Multi(enemies);

                Draw_Multi(shots);

                al_flip_display();
            }
        }

    }

    al_destroy_bitmap(mnuExit);
    al_destroy_bitmap(mnuExitS);
    al_destroy_bitmap(mnuNew_game);
    al_destroy_bitmap(mnuNew_gameS);
    al_destroy_bitmap(mnuOptions);
    al_destroy_bitmap(mnuOptionsS);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
