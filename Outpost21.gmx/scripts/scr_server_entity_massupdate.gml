///scr_server_entity_massupdate(entity id);
//handle dying entities!!!
//show_debug_message("Mass entity update: " + string(argument0));
var get_map = list_entities[| string(argument0)];

if scr_ds_map_verify(get_map) and is_undefined(get_map[? "object_index"]) == false {
    //get data
    var object = asset_get_index(get_map[? "object_index"]);
    var getx = get_map[? "x"]; 
    var gety = get_map[? "y"]; 
    
    //garbage collection first, destroyed entities are moved up to x-2000,y-2000, first before being sanity checked and removed
    if getx <= item_abyss_pos and gety <= item_abyss_pos {
        
        //countdown to full removal
        if getx > item_abyss_pos-128 {
        
            //keep moving until safe to remove forever.
            get_map[? "x"] -= 56;
            get_map[? "inside_of_id"] = -1;
            get_map[? "spd"] = 0;
            
            //drop to all clients, multiple times as a sanity check!
            for (var i=0; i<global.max_server_players; i+=1)
            {
                if scr_socket_verify( i) {
                    show_debug_message("garbage collection: Dropped entity: " + string(argument0));
                    scr_cpacket_entity_drop(i,argument0);
                }
            }
        } 
        else
        {
            //removed from gameplay
            show_debug_message("garbage collection: REMOVED entity: " + string(argument0));
            with get_map[? "SS_collision"] instance_destroy(); //remove entity collisions
            ds_map_destroy(get_map);
            list_entities[| string(argument0)] = -1; //cleared entity
        }
    }
    
    if scr_ds_map_verify(get_map) {
    
        //check to see if garbage collection didn't nuke us
        if get_map[? "entity_last_process_cycle"] != global.server_processing_cycle {
        
            //show_debug_message(" -allowed processing cycle: " + string(global.server_processing_cycle));
        
            //entities in storage don't need to be updated with physics and collisions
            if getx > item_abyss_pos and gety > item_abyss_pos {
            
                //drag entity with me!
                if is_undefined(get_map[? "grabbing_entity"]) == false 
                and get_map[? "grabbing_entity"] != -1 {
                    var get_dragged_map = list_entities[| get_map[? "grabbing_entity"] ]; //decode map from item!
                    
                    if scr_ds_map_verify(get_dragged_map) //drag map exists!
                    and get_dragged_map[? "x"] != item_abyss_pos and get_dragged_map[? "y"] != item_abyss_pos { //not in the item abyss
                    
                        if get_dragged_map[? "inside_of_id"] == -1 and get_map[? "inside_of_id"] == -1 {
                        
                            //drag around!
                            var get_dis = point_distance(get_dragged_map[? "x"],get_dragged_map[? "y"],get_map[? "x"],get_map[? "y"]);
                            if get_dis > global.place_grab_range {
                                //release grab, too far!
                                show_debug_message(" Grab was released by: " + string(get_map[? "grabbing_entity"]) + " was too far away! Dis: " + string(get_dis));
                                get_map[? "grabbing_entity"] = -1;
                                
                                //inform player of grab change if it's a player!!
                                var get_socket = get_map[? "player_socket"];
                                if scr_socket_verify( get_socket) {
                                    scr_cpacket_entity_grab_update(get_socket,-1);
                                }
                            }
                            else if get_dis > 48 {
                                //pull around!
                                var dir_to_grab = point_direction(get_dragged_map[? "x"],get_dragged_map[? "y"],get_map[? "x"],get_map[? "y"]);
                                get_dragged_map[? "x"] += lengthdir_x(get_dis/2,dir_to_grab);
                                get_dragged_map[? "y"] += lengthdir_y(get_dis/2,dir_to_grab); 
                                
                                var get_socket = get_dragged_map[? "player_socket"];
                                if scr_socket_verify( get_socket) {
                                    //pull player around!
                                    var getx = get_dragged_map[? "x"]; 
                                    var gety = get_dragged_map[? "y"]; 
                                    var getpreviousx = get_dragged_map[? "last_update_x"]; 
                                    var getpreviousy = get_dragged_map[? "last_update_y"]; 
                                    //if distance is big enough
                                    if point_distance(getx,gety,getpreviousx,getpreviousy) > 3 {
                                        scr_cpacket_location_sync(get_socket,getx,gety,0,0);
                                    }
                                }
                            }
                            else if get_dis < 24 {
                                //pushing around!
                                var dir_to_grab = point_direction(get_dragged_map[? "x"],get_dragged_map[? "y"],get_map[? "x"],get_map[? "y"]);
                                dir_to_grab = round(dir_to_grab/4)*4; //snap directions
                                
                                get_dragged_map[? "x"] -= lengthdir_x(get_dis*1.2,dir_to_grab);
                                get_dragged_map[? "y"] -= lengthdir_y(get_dis*1.2,dir_to_grab);
                                
                                var get_socket = get_dragged_map[? "player_socket"];
                                if scr_socket_verify( get_socket) {
                                    //pull player around!
                                    var getx = get_dragged_map[? "x"]; 
                                    var gety = get_dragged_map[? "y"]; 
                                    var getpreviousx = get_dragged_map[? "last_update_x"]; 
                                    var getpreviousy = get_dragged_map[? "last_update_y"]; 
                                    //if distance is big enough
                                    if point_distance(getx,gety,getpreviousx,getpreviousy) > 3 {
                                        scr_cpacket_location_sync(get_socket,getx,gety,0,0);
                                    }
                                }
                            }
                        }
                        else
                        {
                            //release grab, this was put in an inventory, or the dragger was?!
                            show_debug_message(" Grab was released by: " + string(get_map[? "grabbing_entity"]) + " grab, or grabber, placed into inventory!");
                            get_map[? "grabbing_entity"] = -1;
                            
                            //inform player of grab change if it's a player!!
                            var get_socket = get_map[? "player_socket"];
                            if scr_socket_verify( get_socket) {
                                scr_cpacket_entity_grab_update(get_socket,-1);
                            }
                        }
                    }
                    else
                    {
                        //release grab, this stopped existing...
                        show_debug_message(" Grab was released by: " + string(get_map[? "grabbing_entity"]) + " grabbed object stopped existing?!");
                        get_map[? "grabbing_entity"] = -1;
                        
                        //inform player of grab change if it's a player!!
                        var get_socket = get_map[? "player_socket"];
                        if scr_socket_verify( get_socket) {
                            scr_cpacket_entity_grab_update(get_socket,-1);
                        }
                    }
                    
                    //flag for updoot
                    if point_distance(get_dragged_map[? "x"],get_dragged_map[? "y"],get_dragged_map[? "last_update_x"],get_dragged_map[? "last_update_y"]) > 5 {
                        if is_undefined(get_map[? "grabbing_entity"]) == false 
                        and get_map[? "grabbing_entity"] != -1 {
                            scr_item_updateflag_allplayers(get_map[? "grabbing_entity"],true);
                        }
                    }
                }
            
                //entity processing cycle
                if get_map[? "inside_of_id"] == -1 {
                    //get data
                    var object = asset_get_index(get_map[? "object_index"]);
                    var getx = get_map[? "x"]; 
                    var gety = get_map[? "y"];
                    var getpreviousx = get_map[? "last_update_x"]; 
                    var getpreviousy = get_map[? "last_update_y"]; 
                    var getdir = get_map[? "dir"]; 
                    
                    var decel = get_map[? "SS_decelerator"];
                    if decel == 1 global.maximum_movement = 9999999; //decleration of 1 allows weird stuff.
                    var getspd = clamp(get_map[? "spd"],-global.maximum_movement,global.maximum_movement); 
                    
                    //store last location
                    get_map[? "last_update_x"] = get_map[? "x"];
                    get_map[? "last_update_y"] = get_map[? "y"];
                    
                    if get_map[? "constructed"] == false {
                        //handle object movement and collisions!
                        var forcex = lengthdir_x(getspd, getdir);
                        var forcey = lengthdir_y(getspd, getdir);
                        get_map[? "x"] = clamp(get_map[? "x"] + forcex, 10, global.map_xlimit);
                        get_map[? "y"] = clamp(get_map[? "y"] + forcey, 10, global.map_ylimit);
                    }
                    else
                    {
                        //constructed entities DO NOT MOVE
                        get_map[? "spd"] = 0;
                    }
                    
                    //update movements 
                    if (getspd > 1 or point_distance(getx,gety,getpreviousx,getpreviousy) > 0.20) and get_map[? "constructed"] == false { //constructed entities cannot move
                        //1 decel likely means it does some fancy shit.
                        if decel < 1 { 
                            //decelerate 
                            get_map[? "spd"] *= decel;
                        
                            //stop if needed
                            if get_map[? "spd"] < global.forced_movement_minimum_cutoff get_map[? "spd"] = 0;
                        }
                        
                        //restore missing collision
                        if instance_exists(get_map[? "SS_collision"]) == false {
                            get_map[? "SS_collision"] = instance_create(get_map[? "x"],get_map[? "y"],obj_serverside_entity);
                            
                            with get_map[? "SS_collision"] {
                                entity_id = argument0;
                            }
                        }
                        
                        //update collision server objects  
                        with get_map[? "SS_collision"] {
                            //we are not in an object
                            sprite_index = spr_serverside_entitycol;
                        
                            //update col
                            x = get_map[? "x"];
                            y = get_map[? "y"];
                            
                            //get potential collisions
                            if get_map[? "SS_collision_ignores_walls"] == false {
                                var collision_found = collision_line(get_map[? "last_update_x"],get_map[? "last_update_y"],x,y,obj_serverside_colwall,true,true);
                                if collision_found == noone {
                                    collision_found = collision_rectangle(x-5,y-5,x+5,y+5,obj_serverside_colwall,true,true);
                                }
                            }
                            else
                            {
                                collision_found = noone;
                            }
                            
                            
                            if collision_found != noone {
                                //do wall damage calc
                                var wall_breaks = false;
                                
                                if wall_breaks == true {
                                    //break wall
                                    
                                }
                                else
                                {
                                    //bounce off!
                                    get_map[? "x"] = get_map[? "last_update_x"]
                                    get_map[? "y"] = get_map[? "last_update_y"]
                                    x = get_map[? "x"];
                                    y = get_map[? "y"];
                                    
                                    //reflect angle (update this later with some kind of entity type specific thing like EXPLODE instead
                                    var xoffset = lengthdir_x( getspd, getdir);
                                    var yoffset = lengthdir_y( getspd, getdir);
                                    
                                    if collision_found.image_angle == 0 or collision_found.image_angle == 180 {
                                        xoffset *= -1;
                                        yoffset *=  1;
                                    }
                                    else
                                    {
                                        xoffset *=  1;
                                        yoffset *= -1;
                                    }
                                    
                                    //set new direction, half speed
                                    get_map[? "dir"] = point_direction(0,0,xoffset,yoffset);
                                    get_map[? "spd"] *= get_map[? "SS_bouncyness"];
                                }
                            }
                            
                            //update col with new data from collision
                            x = get_map[? "x"];
                            y = get_map[? "y"];
                            
                        }
                        
                        //set update flag
                        scr_item_updateflag_allplayers(argument0,true); //force an update!
                    }
                }
                else
                {
                    with get_map[? "SS_collision"] {
                            //we are inside an object, hide me.
                            sprite_index = spr_nocol;
                    }
                }
            }
        }
        
        
        
        
        
        
        
        
        
        //internal entity updates!
        var object = asset_get_index(get_map[? "object_index"]);
        switch object {
            case obj_puppet_coffee_hot:
            case obj_puppet_coffee_microwaved:
                if get_map[? "entity_last_process_cycle"] != global.server_processing_cycle {
                    if get_map[? "coffee_hot"] > 0 {
                        get_map[? "coffee_hot"] -= 1
                    }
                    else
                    {
                        //make new entity, remove old one
                        var new_entity_map = scr_entity_template_library(obj_puppet_coffee_cold,get_map[? "x"],get_map[? "y"],0,0,false,-1);
                        var new_entity_id = scr_server_entity_add(new_entity_map);
                        scr_server_entity_remove(string(argument0));
                        
                        //if the previous coffee was in an entity before!
                        if get_map[? "inside_of_id"] != -1 {
                            //store this entity inside of it!
                            new_entity_map[? "inside_of_id"] = get_map[? "inside_of_id"];
                            var get_storagebox_map = list_entities[| get_map[? "inside_of_id"] ];
                            var get_storagebox_inventory = get_storagebox_map[? "contains_map"];
                            ds_map_add_map(get_storagebox_inventory,string(new_entity_id),string(new_entity_id));
                        }
                    }
                }
            break;
            
            case obj_machine_indoorlamp:
                if get_map[? "entity_last_process_cycle"] != global.server_processing_cycle {
                    //old entity fix
                    if is_undefined(get_map[? "light_charge"]) == true get_map[? "light_charge"] = 0;
                    
                    if get_map[? "light_charge"] > 0 {
                        get_map[? "light_charge"] -= 1;
                    }
                    else
                    {
                        //check for a battery and recharge if possible!
                        var get_inventory_map = get_map[? "contains_map"];
                        
                        //loop through all slots and refill energy 
                        var inv_size = ds_map_size(get_inventory_map);
                        
                        //refill light!
                        get_map[? "light_charge"] = 10; //personal check loop, refills to 10 so we recheck in 10 steps
                        
                        //find batteries to drain!
                        var current_key = ds_map_find_first(get_inventory_map);
                        for (var i=0; i<inv_size; i+=1)
                        {
                            var item_map = list_entities[| current_key];
                            if asset_get_index(item_map[? "object_index"]) == obj_puppet_powercell {
                                //discharge and cook something, once the client end is done trigger again and cook!
                                if item_map[? "Charge"] > 0 {
                                    //discharge
                                    item_map[? "Charge"] -= 1;
                                    
                                    //refill light!
                                    get_map[? "light_charge"] = 6480; //overwrites the personal timing!
                                    get_map[? "machine_has_power"] = true;
                                    //transmit data to clients
                                    var transmission_list = ds_list_create();
                                    transmission_list[| 0] = get_map[? "light_charge"] * 200; //compensates for batch size timings in the alarm
                                    var TXstring = ds_list_write(transmission_list);
                                    var TXbase64 = base64_encode(TXstring);
                                    ds_list_destroy(transmission_list);
                                    //update players to turn on their lights
                                    scr_server_storagebox_object_update_all_players(current_key,argument0);
                                    
                                    //break out of loop!
                                    break;
                                }
                            }
                            //next index
                            current_key = ds_map_find_next(get_inventory_map, current_key);
                        }
                        
                        //disable transmission
                        if is_undefined(get_map[? "machine_has_power"]) == true {
                            //catch crashes
                        }
                        else if get_map[? "machine_has_power"] == true
                        {
                            //was powered last check, but not this time!
                            if get_map[? "light_charge"] == 10 {
                                //we are no longer powered.
                                get_map[? "machine_has_power"] = false;
                                
                                //transmit data to clients
                                var transmission_list = ds_list_create();
                                transmission_list[| 0] = 0; 
                                var TXstring = ds_list_write(transmission_list);
                                var TXbase64 = base64_encode(TXstring);
                                ds_list_destroy(transmission_list);
                                //update players to turn off their lights
                                var t = 0;
                                while t < global.max_server_players {
                                    if scr_socket_verify( t) {
                                        scr_cpacket_entity_reply(t,argument0,obj_machine_indoorlamp,TXbase64,0,enum_entity_reply.is_object);
                                    }
                                    t += 1;
                                }
                            }
                        }
                    }
                }
            break;
            
            case obj_puppet_laserpoint:
                //only if not updated before
                if get_map[? "entity_last_process_cycle"] != global.server_processing_cycle {
                    if get_map[? "firetime"] > 0 {
                        get_map[? "firetime"] -= 1;
                    }
                    else
                    {
                        scr_server_entity_remove(argument0);
                    }
                }
            break;
            
            case obj_puppet_arrivalshuttle:
                if get_map[? "entity_last_process_cycle"] != global.server_processing_cycle {
                    //if the destination is unset pull up to the top!
                    if get_map[? "inside_of_id"] != -1 {
                        //cleanout
                        get_map[? "inside_of_id"] = -1;
                    
                        //reset location to help
                        get_map[? "y"] = 150;
                        get_map[? "x"] = 200;
                        
                        //loop around here for now.
                        get_map[? "dest_x"] = get_map[? "x"]+choose(-30,30);
                        get_map[? "dest_y"] = get_map[? "y"]+choose(-18,18);
                    }
                    else 
                    {
                        if get_map[? "dropoff_flag"] == false {
                            if instance_exists(get_map[? "dropoff_padid"]) {
                                var getinst = get_map[? "dropoff_padid"];
                                
                                var get_paddir = point_direction(get_map[? "x"],get_map[? "y"],getinst.x,getinst.y) + choose(-1,-2,0,2,1); //snapped angle manuvering
                                var get_paddis = clamp(point_distance(get_map[? "x"],get_map[? "y"],getinst.x,getinst.y) + choose(-1,-2,0,2,1),4,1000); //snapped angle manuvering
                                
                                get_map[? "dest_x"] = get_map[? "x"] + lengthdir_x(get_paddis,get_paddir);
                                get_map[? "dest_y"] = get_map[? "y"] + lengthdir_y(get_paddis,get_paddir);
                                
                                //landing check
                                if point_distance(get_map[? "x"],get_map[? "y"],getinst.x,getinst.y) < 10 and get_map[? "spd"] < 2 {
                                    //flag as released
                                    get_map[? "dropoff_flag"] = true; //release player
                                    
                                    //object dropping
                                    var get_inv = get_map[? "contains_map"];
                                    
                                    //get the player
                                    get_plyent = ds_map_find_first(get_inv);
                                    ds_map_delete(get_inv,string(get_plyent)); //remove 
                                    
                                    //release the player!
                                    var get_ply_map = list_entities[| get_plyent];
                                    if scr_ds_map_verify(get_ply_map) {
                                        get_ply_map[? "x"] = getinst.x+irandom_range(-32,32);
                                        get_ply_map[? "y"] = getinst.y+irandom_range(-8,8);
                                        get_ply_map[? "inside_of_id"] = -1; //let go!
                                        
                                        //transmit!
                                        scr_cpacket_playerentity_return( get_ply_map[? "player_socket"]
                                                                       , get_plyent
                                                                       , asset_get_index(get_ply_map[? "object_index"])
                                                                       , get_ply_map[? "x"]
                                                                       , get_ply_map[? "y"]
                                                                       , false);
                                        //send location for the client to set itself to!
                                        scr_cpacket_location_sync(get_ply_map[? "player_socket"],get_ply_map[? "x"],get_ply_map[? "y"],0,0);
                                    }
                                }
                                
                            }
                        }
                        else
                        {
                            if get_map[? "dropoff_waitcounter"] > 0 {
                                get_map[? "dropoff_waitcounter"] -= 1;
                            }
                            else if get_map[? "dropoff_waitcounter"] == 0 {
                                //set destination
                                get_map[? "dest_x"] = global.map_size+200;
                                get_map[? "dest_y"] = get_map[? "y"]-200;
                                //avoid reticking the countdown
                                get_map[? "dropoff_waitcounter"] -= 1;  
                            }
                            else
                            {
                                if get_map[? "x"] > global.map_size - 50 {
                                    //DONE!
                                    scr_server_entity_remove( argument0);
                                }
                            }
                        }
                    }
                    
                    
                    //get direction to goal
                    var get_dir = point_direction(get_map[? "x"],get_map[? "y"],get_map[? "dest_x"],get_map[? "dest_y"]) + choose(-1,-2,0,2,1);
                    
                    //distance controls movement speed
                    var get_spd = point_distance(get_map[? "x"],get_map[? "y"],get_map[? "dest_x"],get_map[? "dest_y"])/1000;
                    if point_distance(get_map[? "x"],get_map[? "y"],get_map[? "dest_x"],get_map[? "dest_y"]) < 10 get_map[? "spd"] *= 0.90; //slowdown!
                    
                    //create sub values for mixing
                    var get_hspeed = lengthdir_x(get_spd,get_dir);
                    var get_vspeed = lengthdir_y(get_spd,get_dir);
                    var cur_hspeed = lengthdir_x(get_map[? "spd"],get_map[? "dir"]);
                    var cur_vspeed = lengthdir_y(get_map[? "spd"],get_map[? "dir"]);
                    
                    //push in direction!
                    get_map[? "dir"] = point_direction(0,0,cur_hspeed+get_hspeed,cur_vspeed+get_vspeed);
                    get_map[? "spd"] = clamp(point_distance(0,0,cur_hspeed+get_hspeed,cur_vspeed+get_vspeed), 0,8);
                } 
            break;
        }
        
        
        //this code only runs once for the first player and all the rest update from it!
        get_map[? "entity_last_process_cycle"] = global.server_processing_cycle;
        
        
        
        
        
        
        
        
        
        
        
        
        
        //check if inside of an object that can display it!
        var inside_id = get_map[? "inside_of_id"];
        var inside_a_display_entity = false;
        var inside_a_inventory_entity = false;
        var host_update_list = -1;
        var host_entity_wants_update = false;
        
        if is_undefined(inside_id) == false 
        and scr_ds_map_verify(list_entities[| inside_id]) {
            var container_map = list_entities[| inside_id];
            
            //fix old entities 
            if is_undefined(container_map[? "contains_display"]) == true container_map[? "contains_display"] = false; 
            
            //fix location data
            if is_undefined(container_map[? "contains_display_x"]) == true container_map[? "contains_display_x"] = 0; //relative to own x
            if is_undefined(container_map[? "contains_display_y"]) == true container_map[? "contains_display_y"] = 0; //relative to own y
            if is_undefined(container_map[? "contains_display_d"]) == true container_map[? "contains_display_d"] = 0; //relative to own depth   
            
            var inside_a_inventory_entity = true;
            var inside_a_display_entity = container_map[? "contains_display"];
            
            var host_update_list = container_map[? "needs_update"];
        }
        //central update loop (goes to all players)
        if getx > item_abyss_pos or gety > item_abyss_pos or inside_a_display_entity == true { //if something removed the entity before this, protect entity removal
            
            //standard update proceedure. see if in range of player, and then update if so!
            for (var i=0; i<global.max_server_players; i+=1)
            {
                if scr_socket_verify( i) {
                    //get if our host object is updating
                    var host_entity_wants_update = false;
                    if ds_exists(host_update_list,ds_type_list) {
                        var host_entity_wants_update = host_update_list[| i];
                        if is_undefined(host_entity_wants_update ) == true host_entity_wants_update = true;
                    }
                    
                    //get player map
                    var player_number = i;
                    var player_entity = list_player[| list_sockets[|  player_number] ]; 
                    
                    
                    if is_undefined(player_entity) == false {
                        var player_map = list_entities[| player_entity]; //get the data structure from the entity list
                        
                        if scr_ds_map_verify(player_map) {
                            //get if this is the same entity as the player that we are sending it to!
                            var is_player = (player_map == get_map);
                            var plyx = player_map[? "x"];
                            var plyy = player_map[? "y"];
                            
                            //if a player is inside another entity then use that entity x and y
                            var get_ply_hostent = player_map[? "inside_of_id"];
                            if get_ply_hostent != -1 {
                                var get_ply_hostmap = list_entities[| get_ply_hostent];    
                            
                                if scr_ds_map_verify(get_ply_hostmap) {
                                    var plyx = get_ply_hostmap[? "x"];
                                    var plyy = get_ply_hostmap[? "y"];
                                }
                            }
                        
                            //check if the object has been marked as recently updated
                            var update = false;
                            
                            //check for updated
                            var get_updatelist = get_map[? "needs_update"];
                            if get_updatelist[| player_number] == true update = true; //allow update!
                            
                            
                            //checking the distance does most of the work.
                            if inside_a_display_entity == false {
                                //not inside a display container
                                var entity_distance = point_distance(plyx,plyy,get_map[? "x"],get_map[? "y"]);
                            }
                            else
                            {
                                //inside a display container   
                                var entity_distance = point_distance(plyx,plyy,container_map[? "x"],container_map[? "y"]);
                            }
                            
                            
                            //ranged activation
                            if entity_distance < global.entity_activation_range or get_map[? "constructed"] == true { //always try to load constructed entityies
                                //if it can be updated do so!
                                if update == true or (host_entity_wants_update == true and inside_a_display_entity == true) {
                                    //do not send the afterimage of yourself.
                                    if is_player == false {
                                        //transmit location!
                                        //show_debug_message("Player: " + string(player_entity) + " Loaded entity: " + string(argument0));
                                        //pretty much anything done to an object flags this.
                                        if inside_a_display_entity == false {
                                            //normal entity drawing
                                            scr_cpacket_entity_load( player_map[? "player_socket"] 
                                                                   , argument0
                                                                   , asset_get_index(get_map[? "object_index"])
                                                                   , get_map[? "x"]
                                                                   , get_map[? "y"]
                                                                   , get_map[? "dir"]
                                                                   , get_map[? "spd"]
                                                                   , get_map[? "constructed"]
                                                                   , 0);
                                        }
                                        else
                                        {
                                            //on display in an object
                                            scr_cpacket_entity_load( player_map[? "player_socket"] 
                                                                   , argument0
                                                                   , asset_get_index(get_map[? "object_index"])
                                                                   , container_map[? "x"] + container_map[? "contains_display_x"]
                                                                   , container_map[? "y"] + container_map[? "contains_display_y"]
                                                                   , 0
                                                                   , 0
                                                                   , 0
                                                                   , container_map[? "contains_display_d"]);
                                        }
                                        //set for clearing later, clear flag
                                        if ds_queue_head(post_update_queue) != argument0 ds_queue_enqueue(post_update_queue,argument0);
                                    }
                                    else if inside_a_inventory_entity == true {
                                        var get_hostent = get_map[? "inside_of_id"];
                                        
                                        if get_hostent != -1 {
                                            var get_hostmap = list_entities[| get_hostent];    
                                        
                                            if scr_ds_map_verify(get_hostmap) {
                                                var ply_socket = player_map[? "player_socket"];
                                                var host_update_list = get_hostmap[? "needs_update"];
                                            
                                                if host_update_list[| ply_socket] == true or update == true { //host or player wants update
                                                    
                                                    //on display in an object
                                                    scr_cpacket_entity_load( ply_socket
                                                                           , get_hostent
                                                                           , asset_get_index(get_hostmap[? "object_index"])
                                                                           , get_hostmap[? "x"]
                                                                           , get_hostmap[? "y"]
                                                                           , 0
                                                                           , 0
                                                                           , 0
                                                                           , 0);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if inside_a_display_entity == false and inside_id != -1 and update == true { //get_map[? "x"] == item_storage_pos and get_map[? "y"] == item_storage_pos 
                                //in storage, keep out of view from everyone!
                                //show_debug_message("Player: " + string(player_entity) + " inventory dropped entity: " + string(argument0));
                                scr_cpacket_entity_drop(player_map[? "player_socket"],argument0);
                                //set for clearing later, clear flag
                                if ds_queue_head(post_update_queue) != argument0 ds_queue_enqueue(post_update_queue,argument0);
                            }
                            else 
                            {
                                //hanging out at the edge of the activation range... maybe because unmoved or it's being weird, but it won't update yet.
                                if (update == false and host_entity_wants_update == false) and (inside_id == -1 or inside_a_display_entity == true) {
                                    scr_item_set_update_flag(argument0,player_number,true); //force an update!
                                }
                            }
                        }
                    }
                    else
                    {
                        //force updates if player is invalid.
                        //scr_item_set_update_flag(argument0,i,true);
                    }
                }
            }
        }
    }
}
else
{
    show_debug_message("Attempted to mass update a missing entity?")
}


