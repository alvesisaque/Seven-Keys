#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <netinet/in.h>
#include <cassert>

#include "guard.hpp"
#include "room.hpp"
#include "map.hpp"

using namespace CppUnit;
using namespace std;

class TestGuard : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestGuard);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testConstructor(void);
        void testDestructor(void);

    private:

    };
    void setUp(){

    }
    void TestGuard::testConstructor(void) {
        Guard * GuardTestObj;
        Room * RoomTestObj;
        Map * MapTestObj;
        MapTestObj = new Map(4,1);
        RoomTestObj = new Room(MapTestObj, "sala 0", "None", nullptr, nullptr, nullptr, nullptr, 1);
        GuardTestObj =  new Guard(RoomTestObj, "guard", 0, 0, 60, false, "normal", 2);
        CPPUNIT_ASSERT(60 == GuardTestObj->mass());
        delete GuardTestObj;
        delete RoomTestObj;
        delete MapTestObj;
        //CPPUNIT_ASSERT(0 == GuardTestObj->);
        //CPPUNIT_ASSERT(0 == GuardTestObj->);
    }
    void TestGuard::testDestructor(void) {

    }
    void TestGuard::tearDown(void) {

    }
    CPPUNIT_TEST_SUITE_REGISTRATION( TestGuard );

    int main() {

        // informs test-listener about testresults
        CPPUNIT_NS::TestResult testresult;

        // register listener for collecting the test-results
        CPPUNIT_NS::TestResultCollector collectedresults;
        testresult.addListener (&collectedresults);

        // register listener for per-test progress output
        CPPUNIT_NS::BriefTestProgressListener progress;
        testresult.addListener (&progress);

        // insert test-suite at test-runner by registry
        CPPUNIT_NS::TestRunner testrunner;
        testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
        testrunner.run(testresult);

        // output results in compiler-format
        CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
        compileroutputter.write ();

        // return 0 if tests were successful
        return collectedresults.wasSuccessful() ? 0 : 1;
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
