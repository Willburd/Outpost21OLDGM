///scr_server_mapentity_makeobject( map entity id);
//add a server side collision entity to a wall or other map object!
var my_map = global.map_saved_constructions[? string(argument0)];

//decode a collision object out of it
var get_obj = asset_get_index(my_map[? "obj"]);
if get_obj == obj_door or object_get_parent(get_obj) == obj_door {
    with instance_create(my_map[? "x"],my_map[? "y"],obj_serverside_door) {
        show_debug_message(" -server side door created.");
        my_map[? "instance"] = id;
        wall_health_perc = my_map[? "health"];
        map_entity_id = argument0; 
        image_angle = my_map[? "angle"];
        if image_angle != 0 image_angle = 90;
    }
}
else if get_obj == obj_landingpad or object_get_parent(get_obj) == obj_landingpad {
    //default
    if is_undefined(my_map[? "landingpad_clearance"]) == true my_map[? "landingpad_clearance"] = enum_landingpad_setting.public;
    
    //add server side object
    with instance_create(my_map[? "x"],my_map[? "y"],obj_serverside_landingpad) {
        show_debug_message(" -server landingpad created.");
        landing_pad_clearance = my_map[? "landingpad_clearance"];
    }
}
else if get_obj == obj_wall or object_get_parent(get_obj) == obj_wall {
    with instance_create(my_map[? "x"],my_map[? "y"],obj_serverside_wall) {
        show_debug_message(" -server side wall created.");
        my_map[? "instance"] = id;
        wall_health_perc = my_map[? "health"];
        map_entity_id = argument0; 
        image_angle = my_map[? "angle"];
        if image_angle != 0 image_angle = 90;
    }
}
else
{
    //add no entry to the list!
    my_map[? "instance"] = noone;
}
