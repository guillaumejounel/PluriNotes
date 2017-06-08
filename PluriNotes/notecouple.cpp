#include "notecouple.h"

bool NoteCouple::operator==(const NoteCouple& c)const{
    if (c.getX() == x && c.getY()==y) return true;

    if (c.isOriented() == false || oriented == false){
        if (c.getX() == y && c.getY()==x) return true;
    }
    return false;
}
