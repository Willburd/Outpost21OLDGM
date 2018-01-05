///scr_template_entity_set_inventorylimits( entity map, inventory size, is size, holds size, is liquid, hold liquid, item class, item class storage, keep_existing_inventory);
gml_pragma("forceinline");
enum enum_itemsize {
    none,
    tiny,
    small,
    medium, //most appliances and containers
    large, //player sized objects in bins and lockers, furniture
    service_cart, //carts
    huge, //vehicles 
}

enum enum_itemclass {
    generic,
    tools,
    sheets,
    food,
    machines,
    machine_parts,
    body,
    body_parts,
    clothing,
    rifle,
    pistol,
    ship,
}

var input_map = argument0;

//clear out inventory or not.
if argument8 == false {
    var inventory_map = ds_map_create();
    ds_map_replace_map( input_map, "contains_map", inventory_map); //inventory sub map!
}

input_map[? "contains_max"] = argument1; //inventory slots
input_map[? "is_size"] = argument2; //pickup size
input_map[? "contains_size"] = argument3; //contains a maximum pickup size of
input_map[? "is_liquid"] = argument4;
input_map[? "contains_type_liquid"] = argument5; 
input_map[? "is_class"] = argument6; //any class
input_map[? "contains_class"] = argument7;
