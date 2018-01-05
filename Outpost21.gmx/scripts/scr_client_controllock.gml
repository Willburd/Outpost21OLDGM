///scr_client_controllock();
//returns if controls are locked!
var getlock = false 
with obj_client {
    getlock = player_input_locked;
}
return getlock;
