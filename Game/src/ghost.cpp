#include "ghost.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <core/animation.h>

#include <cassert>
#include <iostream>

using namespace std;

const string& GHOST_GUARD_RUNNING_PATH = "res/sprites/ghost_guarda1_running.png";
const string& GHOST_GUARD_3_RUNNING_PATH = "res/sprites/ghost_guarda3_running.png";

/**
 * [Ghost::Ghost Loads the guard information in the game]
 * @param  parent                           [The parent is the map object that
 *                                          will contains the ghost guard.]
 * @param  id                               [identifier of object]
 * @param  ghost_guard_horizontal_position  [Guard position on the map in the axis x]
 * @param  ghost_guard_vertical_position    [Guard position on the map in the axis y]
 * @param  mass_of_ghost_guard              [Contains mass information of the guard object]
 * @param  walkable                         [Defines if the ghost guard is an object able to walk]
 * @param  t                                [description]
 * @param  initial_movement_direction       [Defines the initial direction of moviment]
 */
Ghost::Ghost(Object *parent, ObjectID id,
            const double ghost_guard_horizontal_position,
            const double ghost_guard_vertical_position,
            const unsigned int mass_of_ghost_guard,
            const bool walkable, string t,
            const unsigned int initial_movement_direction)
{
    Object(parent, id, ghost_guard_horizontal_position,
           ghost_guard_vertical_position);
    type = t;

    ghost_guard_animation = (unique_ptr<Animation>)new Animation
    (GHOST_GUARD_RUNNING_PATH, 0, 0, 70, 70, 8,
    GHOST_GUARD_SPEED_IN_MILISECONDS, true);
    this->direction_of_movement = (Direction) initial_movement_direction;
    last_game_time_saved = 0;

    if(t == "hard")
    {
        change_animation();
    }else
    {
       //do nothing
    }
    this->set_mass(mass_of_ghost_guard);
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    update_vision();
}

Ghost::~Ghost()
{
}

/**
 * [Ghost::direction Just returns informations of m_direction.]
 * @method Ghost::direction
 * @return [description]
 */
Ghost::Direction Ghost::direction()
{
    return direction_of_movement;
}

void Ghost::update_vision()
{
}

/**
 * [Ghost::set_direction Modifies the movement direction]
 * @method Ghost::set_direction
 * @param  direction_of_movement [The value of the direction that will be setted.]
 */
void Ghost::set_direction(Direction direction_of_movement)
{
    this->direction_of_movement = direction_of_movement;
}

/**
 * [Ghost::draw_self Draws the animation of ghost guard on screen.]
 * @method Ghost::draw_self
 */
void Ghost::draw_self()
{
    ghost_guard_animation->draw(x(), y());
}
/**
 * [Ghost::walk Walk to the player's position at a constant speed.]
 * @method Ghost::walk
 */
void Ghost::walk()
{
    //
    const bool player_is_to_the_right = (player_horizontal_position > this->x());
    const bool player_is_to_the_left = (player_horizontal_position < this->x());
    if(player_is_to_the_right)
    {
        set_x(x() - GHOST_GUARD_SPEED);
    }else if(player_is_to_the_left)
    {
        set_x(x() + GHOST_GUARD_SPEED);
    }else
    {
        set_x(x());
    }
    //
    const bool player_is_to_the_buttom = (player_vertical_position < this->y());
    const bool player_is_to_the_top = (player_vertical_position > this->y());
    if(player_is_to_the_buttom)
    {
        set_y(y() - GHOST_GUARD_SPEED);
    }else if(player_is_to_the_top)
    {
        set_y(y() + GHOST_GUARD_SPEED);
    }else
    {
        set_y(y());
    }
    //
    const bool player_is_aligned_vertically = (not player_is_to_the_right and not player_is_to_the_left);
    if(player_is_aligned_vertically and player_is_to_the_top)
    {
        set_direction(Ghost::UP);
    }else if(player_is_aligned_vertically and player_is_to_the_buttom)
    {
        set_direction(Ghost::DOWN);
    }else if(player_is_to_the_left)
    {
        set_direction(Ghost::LEFT);
    }else if(player_is_to_the_right)
    {
        set_direction(Ghost::RIGHT);
    }else
    {
        
    }
}
/**
 * [Ghost::update_direction Updates the sprite of object (ghost guard) based on the ghost guard movement direction.]
 * @method Ghost::update_direction
 * @param  elapsed                 [Elapsed time since the game start. This parameter is not used here.]
 */
void Ghost::update_direction(unsigned long elapsed)
{
    if(elapsed - last_game_time_saved > 5000)
    {
        int random = rand()%100;

        if(random < 25)
        {
            set_direction(Ghost::LEFT);
        }else if(random < 50)
        {
            set_direction(Ghost::UP);
        }else if(random < 75)
        {
            set_direction(Ghost::RIGHT);
        }else
        {
            set_direction(Ghost::DOWN);
        }

        last_game_time_saved = elapsed;
    }
    ghost_guard_animation->set_row(this->direction());
}

/**
 * [Ghost::get_playerx Receive the player's horizontal position.
 * This information is used at Ghost Guard artificial intelligence.]
 * @method Ghost::get_playerx
 * @param  player_horizontal_position [That's the player's horizontal position.]
 */
void Ghost::get_playerx(const unsigned int player_horizontal_position)
{
    this->player_horizontal_position = player_horizontal_position;
}
/**
 * [Ghost::get_playery Receive the player's vertical position.
 * This information is used at Ghost Guard artificial intelligence.]
 * @method Ghost::get_playery
 * @param  player_vertical_position [That's the player's vertical position.]
 */
void Ghost::get_playery(const unsigned int player_vertical_position)
{
    this->player_vertical_position = player_vertical_position;
}
/**
 * [Ghost::damage Returns the ghost guard attack damage value.]
 * @method Ghost::damage
 * @return [description]
 */
double Ghost::damage()
{
    return GHOST_GUARD_DAMAGE;
}
/**
 * [Ghost::update_self Updates the ghost guard position on the map and walk.]
 * @method Ghost::update_self
 * @param  elapsed            [Elapsed time since the game start.]
 */
void Ghost::update_self(unsigned long elapsed)
{
    set_x(this->x());
    set_y(this->y());

    update_direction(elapsed);
    ghost_guard_animation->update(elapsed);
    walk();
}
/**
 * [Ghost::change_animation It is the animation of the ghost guard
 * that will be loaded on the screen.]
 * @method Ghost::change_animation
 */
void Ghost::change_animation()
{
    ghost_guard_animation.reset(new Animation(GHOST_GUARD_3_RUNNING_PATH,
                                              0, 0, 70, 70, 8,
                                              GHOST_GUARD_SPEED_IN_MILISECONDS_HARD,
                                              true));
}
