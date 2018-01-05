///scr_allclients_send_errormessage( message);
//update all players, tell them to load
for (var i=0; i<global.max_server_players; i+=1)
{
    if is_undefined(list_sockets[| i]) == false and list_sockets[| i] != -1 {
        scr_cpacket_failed_action( i, argument0);
    }
}
