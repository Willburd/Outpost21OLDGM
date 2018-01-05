///scr_inventory_object_depthordering();
//call event15 in all gui objects, and have them see if they are the highest in draw order themselves!
//actual depth check
gml_pragma("forceinline");
global.client_top_gui_window = noone; //reset this to the beginning!
with obj_gui_element_parent event_user(15);
