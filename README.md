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

There are 3 different nodes to assure communication.
`userinterface` node asks user for input,
`controller` node provides both autonomous wander, and user-input task,
`service` node checks request and provides corresponding response.

`service` service has the structure of `char` request and `float32` response. Response is an increase/decrease value to the velocity.
`vel` message is used for sending the service's response to the `controller`.

Flowchart
---------
![alt text](https://i.ibb.co/TwpwYrT/flowchart.png)

