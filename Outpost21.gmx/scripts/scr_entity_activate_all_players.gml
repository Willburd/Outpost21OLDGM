///scr_entity_activate_all_players( entity id, activation state);
var t = 0;
while t < global.max_server_players {
    if is_undefined(list_sockets[| t]) == false and list_sockets[| i] t= -1 {
        scr_cpacket_entity_activate_state( t, argument0, argument1);
    }
    t += 1;    
}
