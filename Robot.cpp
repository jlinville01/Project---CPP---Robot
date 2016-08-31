/*
* RobotDriver.cpp
*
* Justin Linville
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
* Point in a 2D grid
*/
class Point {
public:
    // Make a point at (0, 0)
    Point();
    // Make a point at (x, y). If a coord is out of the range [0, 99], that coord is set to 0
    Point(int x, int y);
    // Get the x coordinate
    int getX();
    // Get the y coordinate
    int getY();
private:
    // x coordinate
    int xPos;
    // y coordinate
    int yPos;
};

class Robot {
public:
    // Make a robot with the given name located at 0, 0 with 100 energy units
    Robot(string name);
    // Make a robot with the given name located at x, y with 100 energy units
    Robot(string name, int x, int y);
    // Get the robot name
    string getName();
    // Get the x position
    int getPosX();
    // Get the y position
    int getPosY();
    // Get the current energy level
    int getEnergyLevel();
    // Increment the energy level by the given energy amount
    void charge(int energyUnits);
    // Set the destination where the task needs to be executed
    void setDestination(int x, int y);
    // Get the x coord of the destination
    int getDestX();
    // Get the y coord of the destination
    int getDestY();
    // Set the task description
    void setTask(string task);
    // Get the task description
    string getTask();

    bool executeTask();
    void status();
    void transferTaskToFriend(Robot& otherRobot);
private:
    string name;
    Point currentPosition;
    Point destinationPosition;
    int energyLevel;
    string task;
    int distanceToDestination();
};

int main() {
    vector<point2D> point2D;

    for (unsigned i = 0; i < 10; i++){
        point2D point = new point2D(i, i);
        point2D.insert(point);
    }

    moveAll(point2D, 5, 5);
    printAll(point2D);
    
    return 0;

}

/*
* Point class implementation
*/
Point::Point() {
    xPos = yPos = 0;
}

Point::Point(int x, int y) {
    if (x < 0 || x > 99) {
                    x = 0;
    }
    if (y < 0 || y > 99) {
                                    y = 0;
    }
    xPos = x;
    yPos = y;
}

int Point::getX() {
    return xPos;
}

int Point::getY() {
    return yPos;
}

/*
* Robot class implementation
*/

Robot::Robot(string name) {
    this->name = name;
    currentPosition = Point(0, 0);
    destinationPosition = Point(0, 0);
    energyLevel = 100;
    task = "none";
}
Robot::Robot(string name, int x, int y){
    this->name = name;
    currentPosition = Point(x, y);
    destinationPosition = Point(0, 0);
    energyLevel = 100;
    task = "none";
}
string Robot::getName(){
    return name;
}
int Robot::getPosX(){
    return currentPosition.getX();
}
int Robot::getPosY(){
    return currentPosition.getY();;
}
int Robot::getEnergyLevel(){
    return energyLevel;
}
void Robot::charge(int energyUnits){
    energyLevel += energyUnits;
}
void Robot::setDestination(int x, int y){
    destinationPosition = Point(x, y);
}
int Robot::getDestX(){
    return destinationPosition.getX();;
}
int Robot::getDestY(){
    return destinationPosition.getY();;
}
void Robot::setTask(string task){
    this->task = task;
}
string Robot::getTask(){
    return task;
}
bool Robot::executeTask(){
    int nrg = distanceToDestination();
    if (nrg <= this->energyLevel) {
        this->energyLevel -= nrg;
        this->currentPosition = destinationPosition;
        this->task = "Completed: " + task;
        return true;
    } else {
        int needed = nrg - this->energyLevel;
        cout << "Robot " << name << " unable to complete task.\n";
        cout << "Destination unreachable with current energy level.\n";
        cout << needed << " more energy units are needed to carry out this task.\n";
        return false;
    }
}
void Robot::status(){
    cout << "**************************************************************\n";
    cout << "Robot " << name << " located at (" << getPosX() << ", " << getPosY() << ")" << endl;
    cout << "Task: " << task << endl;
    cout << "Destination: (" << getDestX() << ", " << getDestY() << ")" << endl;
    cout << "Energy level: " << energyLevel << endl;
    cout << "**************************************************************\n"; 
}
void Robot::transferTaskToFriend(Robot& otherRobot){
    otherRobot.task = task;
    otherRobot.energyLevel += this->energyLevel;
    otherRobot.destinationPosition = this->destinationPosition;
    this->task = "Transferred to " + otherRobot.name;
    this->energyLevel = 0;
    this->destinationPosition = currentPosition;
}

int Robot::distanceToDestination(){
    int distX = abs(getDestX()-getPosX());
    int distY = abs(getDestY()-getPosY());
    double squareR = (distX + distY);
    return (squareR);
}

void moveAll(vector<int> v, int x, int y) {
    for (unsigned i = 0; i < v.size(); i++) {
        x[i]->moveX(x);
        x[i]->moveY(y);
    }
}

void printAll(vector<point2d> x) {
    for(int i = 0; i < x.size(); i++){
        x[i]->printLocation();
    }
}