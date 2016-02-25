#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED


class Object
{
    public:
        Object();
        virtual ~Object();

        ALLEGRO_BITMAP *Object_image = NULL;
        ALLEGRO_SAMPLE *sound = NULL;

        int positionX;
        int positionY;
        double speed;
        int type;  // variable to differentiate the objects in the list
        int m_size;


        void set_obj(int x, int y, int v, int sz);
        void draw();
        void movement(int d);
        void select_image(std::string diretorio);
};

class M_Object : public Object
{
public:
    bool destroy;

    M_Object();
    M_Object *next;

    M_Object *create_each(M_Object *parent, int x, int y, int v, int t, bool random, int sz);
    M_Object *Clean_list(M_Object *parent, bool clean);
};

void Draw_Multi(M_Object *parent);
void Update_Objects(M_Object *parent, int movement);
void Enemies_movement(M_Object *enemies, int & x);
void Object_Collision(M_Object *obj1, M_Object *obj2);

#endif // OBJECTS_H
