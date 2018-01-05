///scr_server_entity_flag_updateall();
for (var im = 0; im<ds_list_size(list_entities); im += 1) {
    if is_undefined(list_entities[| im]) == false and ds_exists(list_entities[| im],ds_type_map) {
        //mark all player flags as update forced!
        scr_item_updateflag_allplayers(im,true);
    }
}
