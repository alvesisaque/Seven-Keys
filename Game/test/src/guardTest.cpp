#include "../src/guard.cpp"
#include "../src/room.cpp"
#include "../src/map.cpp"

using namespace std;


class TestGuard{
public:
    Guard * GuardTestObj;
    Room * RoomTestObj;
    Map * MapTestObj;

    TestGuard(){

    }

    void setUp(){
        tearDown();
        this->MapTestObj = new Map(4,1);
        this->RoomTestObj = new Room(MapTestObj, "sala 0", "None", nullptr, nullptr, nullptr, nullptr, 1);
        this->GuardTestObj =  new Guard(RoomTestObj, "guard", 0, 0, 60, false, "normal", 2);
        printf("criou os objetos");
    }

    void tearDown(){
        if(this->GuardTestObj != NULL){
            delete GuardTestObj;
        }else{
            //do nothing
        }

        if(this->RoomTestObj != NULL){
            delete RoomTestObj;
        }else{
            //do nothing
        }

        if(this->MapTestObj != NULL){
            delete MapTestObj;
        }else{
            //do nothing
        }
        printf("deletou os objetos");
    }
    void get_playerx_test()
    {
        this->setUp();
        int player_horizontal_position = 0;
        Guard::get_playerx(player_horizontal_position);
        assert(this->GuardTestObj->player_horizontal_position == player_horizontal_position);
    }
    void get_playery_test()
    {
        this->setUp();
        int player_vertical_position = 0;
        Guard::get_playery(player_vertical_position);
        assert(this->player_vertical_position == player_vertical_position);
    }
    void set_direction_test(Direction direction_of_movement)
    {
        this->setUp();
        Direction direction_of_movement = Guard::RIGHT;
        Guard::set_direction(direction_of_movement);
        assert(this->direction_of_movement == direction_of_movement);
    }
    void walk_test()
    {
        this->setUp();
        int player_horizontal_position = 0;
        int player_vertical_position = 0;
        Guard::get_playerx(player_horizontal_position);
        Guard::get_playery(player_vertical_position);
        Guard::walk();
    }
    void update_direction_test()
    {
        this->setUp();
        unsigned long elapsed = 5001; //condition that is accepted by the 'if' of the method
        Direction direction_of_movement_before_update = this->direction_of_movement;
        Guard::update_direction(elapsed);
        assert(this->direction_of_movement != direction_of_movement_before_update);
    }
    void damage_test()
    {
        this->setUp();
        double Guard_damage;
        Guard_damage = Guard::damage();
        assert(Guard_damage == this->GUARD_DAMAGE);
    }
    void health()
    {
        this->setUp();
        double guard_health_to_test;
        guard_health_to_test = Guard::health();
        assert(guard_health_to_test == this->guard_health);
    }
};

int main(){
    TestGuard *testGuard = new TestGuard();
    testGuard->setUp();
    return 0;
}



    /*

    */
