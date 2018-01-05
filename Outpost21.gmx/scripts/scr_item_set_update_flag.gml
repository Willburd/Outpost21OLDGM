///scr_item_set_update_flag( entity id, player number, true or false);
gml_pragma("forceinline");
var entity_map = list_entities[| string(argument0)];
var get_updatelist = entity_map[? "needs_update"];
get_updatelist[| argument1] = argument2;
