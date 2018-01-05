///scr_menu_overlap_check(x,y)
var returner = false;
var exception_id = id;
with obj_inventory_container {
    if exception_id != id {
        var mouse_guix = argument0;
        var mouse_guiy = argument1;
        var gui_size = 16; //tile size
        var tlx = -30; //pulls alignment to one way. because i did the art in gui_sizex chunks
        var tly = 0;
        if inventory_slots_hor_max == 0 inventory_slots_hor_max = 1; //prevent divide by 0
        var inventory_slots_ver_max = inventory_slots_tot_max div inventory_slots_hor_max;
        
        //the entire window is the click zone
        if point_in_rectangle(mouse_guix,mouse_guiy,guix-(gui_size*2)-3 , guiy-gui_size, guix + ((inventory_slots_hor_max-1)*gui_size) + 3, guiy + (inventory_slots_ver_max*gui_size)) {
            returner = true;
        }
    }
}

return returner;
