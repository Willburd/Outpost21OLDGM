///scr_allclients_send_errormessage( message);
//update all players, tell them to load
for (var i=0; i<global.max_server_players; i+=1)
{
    if scr_socket_verify( i) {
        scr_cpacket_failed_action( i, argument0);
    }
}
