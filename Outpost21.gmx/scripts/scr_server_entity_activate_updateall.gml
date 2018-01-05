///scr_server_entity_activate_updateall(send entity id, state value);
//update all players, tell them to unload
for (var i=0; i<global.max_server_players; i+=1)
{
    if is_undefined(list_sockets[| i]) == false and list_sockets[| i] != -1 {
        //mark all player flags as update forced!
        scr_cpacket_entity_activate(i,argument0,argument1);
    }
}
