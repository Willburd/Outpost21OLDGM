///scr_inventory_openwindow( entity to load inventory, previous inventory id);
//make the opened inventory
var return_id = noone;
var allow_new_inventory = true;
with obj_inventory_parent {
    if my_entity == argument0 {
        //automatically put it on top
        scr_inventory_object_depthsetting();
        //don't spawn a new one
        allow_new_inventory = false;
    }
}

if allow_new_inventory == true {
    with instance_create(x,y,obj_inventory_container) {
        return_id = id;
        my_entity = argument0; //alarm0 in this object will load the inventory!
        if instance_exists(argument1) and (argument1.object_index == obj_inventory_parent or object_get_parent(argument1) == obj_inventory_parent) {
            ds_queue_enqueue(argument1.my_child,id); //send up the chain that this is a child inventory!
        }
    }
}

return return_id;
