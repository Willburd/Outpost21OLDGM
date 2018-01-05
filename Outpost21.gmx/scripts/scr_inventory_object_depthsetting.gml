///scr_inventory_object_depthsetting();
//raise window to top and push others down!
gml_pragma("forceinline");
if object_index != obj_gamecontrol { //do not set the main gui under this!
    with obj_gui_element_parent {
        depth += 5;
    }
    
    //set me!
    depth = -1000;
    global.client_top_gui_window = id;
}
