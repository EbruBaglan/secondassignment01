Research Track 1 - Assignment 2 - Solution
================================

This is yet another simple and portable robot simulator which runs in a circuit. The requirements of the assignment are by using ROS and C++,
- to make robot move autonomously in the circuit as in the first assignment,
- to have a node to control the robot, and an additional node to interact with user to increase/decrease of the robot speed and reset position.

Installing and running
----------------------

After you download and build the workspace, you can run the simulation environment and all the nodes with

```bash
$ ./runew.sh
```
You will be at the user interface asking for increase/decrease/reset command.

Structure
---------
![alt text](https://i.ibb.co/SBRptpq/nodes.png)

There are 3 different nodes to assure communication.
`userinterface` node asks user for input,
`controller` node provides both autonomous wander, and user-input task,
`service` node checks request and provides corresponding response in the `service` service. (should have chosen some creative names)

There is one service.
`service` service has the structure of `char` request and `float32` response. Response is an increase/decrease value to the velocity, which is later sent to the `controller` through `/vel` topic from `userinterface` to `controller`.

There is one msg, sent through `/vel` topic.
`vel` mesg is used for sending the service's response to the `controller`.

How it works?
---------
Automous moving part is straighforward. As long as there is no obstacle in front, robot keeps moving. When the front distance lowers to a certain distance, robot checks right and left surroundings. Whichever side is the farthest, robots turns toward that direction.

When user inputs a value, userinterface call service with the request char. Service node, checks the request in the service structure, and puts an increment/decrement response into service structure. Userinterface receives this increment/decrement, and publishes this to controller node. Controller node, takes this and adds it into linear x velocity, and publishes into cmd_vel.

Flowchart
---------
![alt text](https://i.ibb.co/TwpwYrT/flowchart.png)

