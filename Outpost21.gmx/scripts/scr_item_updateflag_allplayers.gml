///scr_item_updateflag_allplayers( entity id, true or false);
var tm = 0;
while tm < global.max_server_players {
    if is_undefined( list_sockets[| tm] ) == false and list_sockets[| tm] != -1 {
        scr_item_set_update_flag( argument0, tm, argument1);
    }
    tm += 1;    
}
