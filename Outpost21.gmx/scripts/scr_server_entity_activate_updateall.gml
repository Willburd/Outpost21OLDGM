///scr_server_entity_activate_updateall(send entity id, state value);
//update all players, tell them to unload
for (var i=0; i<global.max_server_players; i+=1)
{
    if scr_socket_verify( i) {
        //mark all player flags as update forced!
        scr_cpacket_entity_activate(i,argument0,argument1);
    }
}
