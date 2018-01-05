///scr_server_storagebox_object_update_all_players( entity, storagebox entity);
var t = 0;
while t < global.max_server_players {
    if scr_socket_verify( t) {
        scr_cpacket_storagebox_object_update( t, argument0, argument1);
    }
    t += 1;
}
