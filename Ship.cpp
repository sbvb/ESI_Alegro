#include "Allegro_esi.h"

using namespace std;

/*************************************************************
---------------------Classe dos Objetos-----------------------
*************************************************************/

Object::Object(int x, int y, int v)
{
    positionX = x;
    positionY = y;
    speed = v/FPS;
}

Object::~Object()
{
    cout << "destructor called" << endl;
}

void Object::movement(int direction) // for direction = 1 the ship moves right, and left if 0//
{
    int dx = cos(direction*PI/180)*speed;
    int dy = sin(direction*PI/180)*speed;
    positionX += dx;
    positionY -= dy;
}

void Object::select_image(string diretorio)
{
    const char *d = diretorio.c_str();
    Object_image = al_load_bitmap(d);
}

void Object::draw()
{
    al_draw_bitmap(Object_image, positionX, positionY, 0);
}

