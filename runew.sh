gnome-terminal --tab --title="tab 0" -- rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world  
gnome-terminal --tab --title="tab 1" -- rosrun second_assignment service  
gnome-terminal --tab --title="tab 2" -- rosrun second_assignment controller
gnome-terminal --tab --title="tab 3" -- rosrun second_assignment userinterface