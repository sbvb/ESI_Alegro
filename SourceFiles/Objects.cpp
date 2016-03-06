#include "Allegro_esi.h"

using namespace std;

/*************************************************************
---------------------Classe dos Objetos-----------------------
*************************************************************/

Object::Object(){}

void Object::set_obj(int x, int y, int v, int sz)
{
    positionX = x;
    positionY = y;
    speed = v/FPS;
    type = 0;
    m_size = sz;

}

Object::~Object()
{
    al_destroy_bitmap(Object_image);
    al_destroy_sample(sound);
}

void Object::movement(int direction) // for direction = 1 the ship moves right, and left if 0//
{
    int dx = cos(direction*PI/180)*speed;
    int dy = sin(direction*PI/180)*speed;
    positionX += dx;
    positionY -=  dy;
}

void Object::select_image(string diretorio)
{
    Search_Dir image_dir;

    image_dir.load_files(diretorio);

    int p = type;

    Object_image = al_load_bitmap(image_dir.container[p].c_str());

    if(!Object_image)
    {
        cout << "Image bitmap not loaded" << endl;
        al_rest(3);
    }
}

void Object::draw()
{
    al_draw_bitmap(Object_image, positionX, positionY, 0);
}

M_Object::M_Object(){}

M_Object *M_Object::create_each(M_Object *parent, int x, int y, int v, int types, bool random, int sz)
{
    M_Object *tmp;
    tmp = new M_Object();
    tmp->next = parent;
    tmp->destroy = false;
    tmp->set_obj( x, y, v, sz);
    int t;
    if(random)
    {
        t = rand() % types;
    }
    else
    {
        t = types;
    }
    tmp->type = t;

    return tmp;
}

////////////////////////////////////////////////////
///* Funções que controlam as listas de objetos *///
////////////////////////////////////////////////////

M_Object* M_Object::Clean_list(M_Object *obj, bool clean)
{
    M_Object *temp;
    M_Object *top;
    temp = NULL;
    top = obj;

    while(obj)
    {
        if((obj->destroy == true)||clean)
        { // is the particle is dead or if we are deleting all particles
            if(temp)
            {          // then delete it!
                temp->next=obj->next;
                delete obj;
                obj=temp->next;
            }
            else
            {
                top=obj->next;
                delete obj;
                obj=top;
            }
        }
        else {
            temp=obj;
            obj=obj->next;
        }
    }
    return top;
}

void Update_Objects(M_Object *obj, int movement) // 0 = left
{                                                // 1 = down
    int p = movement * 90;                       // 2 = right
    while(obj)                                   // 3 = up
    {
        if(obj->positionY <= 0)
        {
            obj->destroy = true;
        }
        obj->movement(p);
        obj = obj->next;
    }
}

void Draw_Multi(M_Object *t)
{
    while(t)
    {
        t->draw();
        t=t->next;
    }
}

void Enemies_movement(M_Object *ene, int & x)
{
    M_Object *tmp = ene;

    int flag = 0;
    while(tmp)
    {
        if(tmp->positionX >= Width - 200 - tmp->m_size )
        {
            x = 2;
            flag = 1;
            break;
        }
        else if(tmp->positionX <= 200 )
        {
            x = 0;
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    if(flag == 1)
    {
        for(int i = 0; i< 15; i++)
        {
            Update_Objects(ene, 3);
        }
        flag = 0;
    }

}

void Object_Collision(M_Object *obj1, M_Object *obj2)
{
    int cx1, cx2;
    int cy1, cy2;
    int distanc;

    M_Object *temp = obj2;
    while(obj1)
    {
        obj2 = temp;
        while(obj2)
        {
            cx1 = obj1->positionX + (obj1->m_size/2);
            cx2 = obj2->positionX + (obj2->m_size/2);
            cy1 = obj1->positionY + (obj1->m_size/2);
            cy2 = obj2->positionY + (obj2->m_size/2);
            distanc = sqrt( (cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2));
            if( distanc <= (obj1->m_size + obj1->m_size)/2 )
            {
                obj1->destroy = true;
                if( obj1->type == obj2 ->type)
                {
                    obj2->destroy = true;
                }
            }
            obj2 = obj2->next;
        }
        obj1 = obj1->next;
    }

}
