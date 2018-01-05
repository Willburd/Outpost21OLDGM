///scr_item_get_contextmenu( entity id, storagebox entity id, object_index , triggering index -1 is get names instead);
//shows a context action name, or does the action based on argument2

switch argument2 { //use object index to decode
    default:
    case obj_puppet_genericitem:
        //default context menu
        if argument3 == -1 {
            show_debug_message("Context menu names request, entity: " + string(argument0));
        
            //load the context menu!
            context_menu[0] = "Place";
            context_menu[1] = "Throw";
        }
        else
        {
            if argument3 == 0 {
                show_debug_message("Context menu event 0, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.placing;
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 1 {
                show_debug_message("Context menu event 0, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.throwing;
                }
                
                //cancel context
                instance_destroy();
            }
        }
    break;
    
    case obj_puppet_toolbox:
        //default context menu
        if argument3 == -1 {
            show_debug_message("Context menu names request, entity: " + string(argument0));
        
            //load the context menu!
            context_menu[0] = "Open";
            context_menu[1] = "Place";
            context_menu[2] = "Throw";
            context_menu[3] = "Load";
        }
        else
        {
            if argument3 == 0 {
                show_debug_message("Context menu event 0, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_inventory_container) {
                    my_entity = argument0; //alarm0 in this object will load the inventory!
                    other.storagebox_entity.my_child = id; //send up the chain that this is a child inventory!
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 1 {
                show_debug_message("Context menu event 1, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.placing;
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 2 {
                show_debug_message("Context menu event 2, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.throwing;
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 3 {
                show_debug_message("Context menu event 3, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.load;
                }
                
                //cancel context
                instance_destroy();
            }
        }
    break;
    
    case obj_puppet_cup:
        //default context menu
        if argument3 == -1 {
            show_debug_message("Context menu names request, entity: " + string(argument0));
        
            //load the context menu!
            context_menu[0] = "Open";
            context_menu[1] = "Place";
            context_menu[2] = "Throw";
            context_menu[3] = "Fill";
        }
        else
        {
            if argument3 == 0 {
                show_debug_message("Context menu event 0, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_inventory_container) {
                    my_entity = argument0; //alarm0 in this object will load the inventory!
                    other.storagebox_entity.my_child = id; //send up the chain that this is a child inventory!
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 1 {
                show_debug_message("Context menu event 1, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.placing;
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 2 {
                show_debug_message("Context menu event 2, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.throwing;
                }
                
                //cancel context
                instance_destroy();
            }
            else if argument3 == 3 {
                show_debug_message("Context menu event 3, entity: " + string(argument0));
            
                //make the targeting controls
                with instance_create(x,y,obj_location_target) {
                    my_entity = argument0; //set by context menu on create
                    storagebox_entity = argument1;
                    target_mode = enum_targeter.fill;
                }
                
                //cancel context
                instance_destroy();
            }
        }
    break;
}
