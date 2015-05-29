
#include <iostream>
#include <core/animation.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

#include "item.h"

Item::Item(Object *parent, ObjectID id, double posx, double posy, bool walk, string type)
    : Object(parent, id), walkable(walk), type(type)
{
    set_position(posx, posy);
    set_x(posx);
    set_y(posy);
}

Item::~Item()
{
}

//Alterar
void
Item::draw_self()
{
    //const Color color { 80, 180, 205 };
    Animation* item;
    
    item = new Animation(current_sprite, 0, 0, w(), h(), 1,0, false);
    
    item->draw(x(), y());
    //Environment *env = Environment::get_instance();
    //env->canvas->fill(bounding_box(), color);
}

void
Item::change_sprite(string item)
{
    current_sprite = item;
}

void
Item::update_self()
{
    set_x(this->x());
    set_y(this->y());
}
