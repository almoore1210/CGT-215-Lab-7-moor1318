// CGT-215-Lab-7-moor1318.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {

	//create window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	//create ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 200));
	ball.setRadius(20);
	ball.setVelocity(Vector2f(0.5, 0.5));
	world.AddPhysicsBody(ball);

	//create floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	//create ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(730, 20));
	ceiling.setCenter(Vector2f(390, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//create left wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 600));
	leftWall.setCenter(Vector2f(10, 270));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	//create right wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 600));
	rightWall.setCenter(Vector2f(790, 270));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	//create middle box
	PhysicsRectangle middleBox;
	middleBox.setSize(Vector2f(100, 100));
	middleBox.setCenter(Vector2f(400, 250));
	middleBox.setStatic(true);
	world.AddPhysicsBody(middleBox);

	//starting at 0 messed it up, have to start at 1
	int thudCount(1);
	int bang(1);

	//count bounces on outside walls
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	//count hits to middle box
	middleBox.onCollision = [&bang](PhysicsBodyCollisionResult result) {
		cout << "bang " << bang << endl;
		bang++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {

		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());

		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		//exit when ball hits middle box 3 times
		if (bang >= 3) {
			cout << "Ball hit middle box 3 times, exiting program." << endl;
			break;
		}

		//draw everything
		window.clear(Color(0, 0, 0));

		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(middleBox);

		window.display();
	}
}