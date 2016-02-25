#ifndef SHIP_H
#define SHIP_H


class Object
{
    public:
        Object(int x, int y , int z);
        virtual ~Object();

        ALLEGRO_BITMAP *Object_image = NULL;

        int positionX;
        int positionY;
        int speed;

        void draw();
        void movement(int d);
        void select_image(std::string diretorio);
};

#endif // SHIP_H

