///scr_inventory_object_interaldepthcalculate( mouse in this window);
//updates the depth check to see if this window is valid, uses a single input so that the object calling can say if you even pressed anything!
gml_pragma("forceinline");
if argument0 == true and ( instance_exists(global.client_top_gui_window) == false or depth < global.client_top_gui_window.depth ) {
    global.client_top_gui_window = id;
}
