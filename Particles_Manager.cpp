#include "Allegro_esi.h"

void Particle_Manager::Clean_Particles(Object *obj, bool clean)
{
    Object *temp;
    Object *top;

    top = obj;

    while(obj)
    {
        if(obj->destroy||clean) { // is the particle is dead or if we are deleting all particles
            if(temp){          // then delete it!
                temp->next=obj->next;
                free(obj);
                obj=temp->next;
            }
            else {
                top=obj->next;
                free(obj);
                obj=top;
            }
        }
        else {
            temp=t;
            t=t->next;
        }
    }
}
