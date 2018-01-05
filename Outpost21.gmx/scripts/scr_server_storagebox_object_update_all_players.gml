///scr_server_storagebox_object_update_all_players( entity, storagebox entity);
var t = 0;
while t < global.max_server_players {
    if is_undefined(list_sockets[| t]) == false and list_sockets[| t] != -1 {
        scr_cpacket_storagebox_object_update( t, argument0, argument1);
    }
    t += 1;
}
