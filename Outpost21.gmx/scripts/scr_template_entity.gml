///scr_template_entity(object, x,y,dir,speed,indestructable,inside of id, optional replacement_map);

var fresh_inventory = true;
if argument_count == 8 and ds_exists(argument[7],ds_type_map) {
    //load the entity in for refreshing
    var new_entity = argument[7];
    fresh_inventory = false;
}
else
{
    //make a new one!
    var new_entity = ds_map_create();
    fresh_inventory = true;
}

new_entity[? "object_index"] = object_get_name(argument[0]);
new_entity[? "entity_number"] = -1;
new_entity[? "x"] = argument[1];
new_entity[? "y"] = argument[2];
new_entity[? "last_update_x"] = argument[1];
new_entity[? "last_update_y"] = argument[2];
new_entity[? "dir"] = argument[3];
new_entity[? "spd"] = argument[4];
new_entity[? "needs_update"] = ds_list_create(); //is a list of player flags!
new_entity[? "indestructable"] = argument[5];
//external inventory control
new_entity[? "inside_of_id"] = argument[6]; //created inside another id?
new_entity[? "is_liquid"] = false;
new_entity[? "is_size"] = 0;
//self inventory
new_entity[? "grabbing_entity"] = -1
if fresh_inventory == true new_entity[? "contains_map"] = -1
new_entity[? "contains_max"] = 0;
new_entity[? "contains_type_liquid"] = false;
new_entity[? "contains_size"] = 0;
//item displaying
new_entity[? "contains_display"] = false; //if true the object will display its contents on or in it
new_entity[? "contains_display_x"] = 0; //relative to own x
new_entity[? "contains_display_y"] = 0; //relative to own y
new_entity[? "contains_display_d"] = 0; //relative to own depth
//server side collision entitys
new_entity[? "SS_collision"] = noone;//mass update handles this
new_entity[? "SS_collision_ignores_walls"] = false;
new_entity[? "SS_bouncyness"] = 0.5;
new_entity[? "SS_decelerator"] = global.forced_movement_decelerator;
//if constructed it does not move
if fresh_inventory == true new_entity[? "constructed"] = false;
new_entity[? "entity_last_process_cycle"] = 0;
return new_entity;
