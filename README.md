Research Track 1 - Assignment 2 - Solution
================================

This is yet another simple and portable robot simulator which runs in a circuit. The requirements of the assignment are by using ROS and C++,
- to make robot move autonomously in the circuit as in the first assignment,
- to have a node to control the robot, and an additional node to interact with user to increase/decrease of the robot speed and reset position.

Installing and running
----------------------
Choose a directory to work in, then clone the repo by typing
```bash
git clone https://github.com/EbruBaglan/secondassignment01
```

After you download and build the workspace, first initialize roscore by hitting,
```bash
$ roscore &
```
then go to the main directory on package and just hit

```bash
$ ./runew.sh
```
The simulation environment and all the nodes within are initiated just by that.

You will be at the user interface asking for increase/decrease/reset command.

Here is the video for run and proof that code works:
https://youtu.be/xC3xZsW8AZs

Structure
---------
![alt text](https://i.ibb.co/cbtbdBN/structure.png)



There are 2 nodes to assure communication.
`userinterface` node asks user for input,
`controller` node provides both autonomous movement, and user-input movement.

There is one service.
`service` service has the structure of `char` request and `float32` response. Response is the increase/decrease value to the velocity.

How it works?
---------
Automous moving part is straighforward. As long as there is no obstacle in front, robot keeps moving. When the front distance lowers to a certain distance, robot checks right and left surroundings. Whichever side is the farthest, robots turns toward that direction.

When user inputs a value, userinterface calls the service with the request char. Controller node, checks the request in the service structure, and puts an increment/decrement response into service, and it itself uses it in linear.x velocity assignment, and publishes it into cmd_vel.

Flowchart
---------
![alt text](https://i.ibb.co/TwpwYrT/flowchart.png)

