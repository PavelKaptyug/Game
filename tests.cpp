#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
//#include "tests.h"
#include "doctest.h"
#include "Character.h"
int TestLeft() {
	Character character(500, "lol.jpg", 3);
	character.moveLeft();
	return character.x;
}int TestRight() {
	Character character(500, "lol.jpg", 3);
	character.moveRight();
	return character.x;
}
TEST_CASE("Right") {
	CHECK(TestRight() == 610);
}
TEST_CASE("Left") {
	CHECK(TestLeft() == 570);
}

