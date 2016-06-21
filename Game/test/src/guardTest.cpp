#include "../src/guard.cpp"
#include "../src/room.cpp"
#include "../src/map.cpp"

using namespace std;


class TestGuard{
public:
    TestGuard() {

    }
    void setUp(){
        Guard * GuardTestObj;
        Room * RoomTestObj;
        Map * MapTestObj;
        printf("declarou os objeto");
        MapTestObj = new Map(4,1);
        RoomTestObj = new Room(MapTestObj, "sala 0", "None", nullptr, nullptr, nullptr, nullptr, 1);
        GuardTestObj =  new Guard(RoomTestObj, "guard", 0, 0, 60, false, "normal", 2);
        printf("criou os objeto");
        delete GuardTestObj;
        delete RoomTestObj;
        delete MapTestObj;
        printf("deletou os objeto");
    }

};

int main() {
    TestGuard *testGuard = new TestGuard();
    testGuard->setUp();
}

    /*
    void get_playerx_test()
    {
        int player_horizontal_position = 0;
        Guard::get_playerx(player_horizontal_position);
        assert(this->player_horizontal_position == player_horizontal_position);
    }
    void get_playery_test()
    {
        int player_vertical_position = 0;
        Guard::get_playery(player_vertical_position);
        assert(this->player_vertical_position == player_vertical_position);
    }
    void set_direction_test(Direction direction_of_movement)
    {
        Direction direction_of_movement = Guard::RIGHT;
        Guard::set_direction(direction_of_movement);
        assert(this->direction_of_movement == direction_of_movement);
    }
    void walk_test()
    {
        int player_horizontal_position = 0;
        int player_vertical_position = 0;
        Guard::get_playerx(player_horizontal_position);
        Guard::get_playery(player_vertical_position);
        Guard::walk();
    }
    void update_direction_test()
    {
        unsigned long elapsed = 5001; //condition that is accepted by the 'if' of the method
        Direction direction_of_movement_before_update = this->direction_of_movement;
        Guard::update_direction(elapsed);
        assert(this->direction_of_movement != direction_of_movement_before_update);
    }
    void damage_test()
    {
        double Guard_damage;
        Guard_damage = Guard::damage();
        assert(Guard_damage == this->GUARD_DAMAGE);
    }
    void health()
    {
        double guard_health_to_test;
        guard_health_to_test = Guard::health();
        assert(guard_health_to_test == this->guard_health);
    }
    */
