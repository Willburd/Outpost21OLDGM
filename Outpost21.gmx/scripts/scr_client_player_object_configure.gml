///scr_client_player_object_configure( object_index from server)
//the server can return things like obj_player_puppet which is not correct
//this lets us turn those into client side things like obj_player
switch argument0 {
    case obj_puppet_player:
        return obj_player;
    break;
    
    default:
        scr_consoleout("Server assigned DEFAULT object");
        return obj_host_followpuppet;
    break;
}
