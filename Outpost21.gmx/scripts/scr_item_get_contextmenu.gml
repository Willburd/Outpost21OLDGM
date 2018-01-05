///scr_item_get_contextmenu( entity id, storagebox entity id, object_index , triggering index -1 is get names instead);
//shows a context action name, or does the action based on argument2

enum enum_contextoptions {
    open,
    grab,
    drop,
    release_grab,
    throw,
    fill,
    load,
    construct,
    deconstruct,
    activate_nopower,
    activate_powered,
    arm,
    equip,
    unequip,
    prog_card,
    prog_door,
    
    electro_menu,
    printer_menu,
    fab_menu,
}

var fabmenu_type = 0;


if argument3 == -1 {
    
    var queue_construct_context_menu = ds_queue_create();

    switch argument2 { //use object index to decode
        
        default:
        case obj_puppet_genericitem:
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
    
        
        case obj_puppet_player:
            //default context menu
            show_debug_message("Context menu names request, DEFAULT, entity: " + string(argument0));
        
            //load the context menu!
            if global.client_grab_entity == -1 
            or is_undefined(obj_client.list_entity_cache[| global.client_grab_entity]) 
            or obj_client.list_entity_cache[| global.client_grab_entity] != my_instance {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.release_grab);
            }
            ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
        break;
        
        case obj_puppet_assistbox:
        case obj_puppet_cargobox:
        case obj_puppet_commsbox:
        case obj_puppet_weatherbox:
        case obj_puppet_labbox:
        case obj_puppet_medicbox:
        case obj_puppet_toolbox:
        case obj_puppet_minebox:
        case obj_puppet_secbox:
        case obj_puppet_atmobox:
        case obj_puppet_hydrobox:
        case obj_puppet_janibox:
            //default context menu
            show_debug_message("Context menu names request, toolbox, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
            ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
        break;
        
        case obj_puppet_securitytool:
            //default context menu
            show_debug_message("Context menu names request, SECTOOL, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Insert card", enum_contextoptions.open);
                ds_queue_enqueue(queue_construct_context_menu, "Program card", enum_contextoptions.prog_card);
                ds_queue_enqueue(queue_construct_context_menu, "Program door", enum_contextoptions.prog_door);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                ds_queue_enqueue(queue_construct_context_menu, "Insert card", enum_contextoptions.open);
            }
        break;
        
        case obj_puppet_cup:
            //default context menu
            show_debug_message("Context menu names request, cup, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                ds_queue_enqueue(queue_construct_context_menu, "Fill",  enum_contextoptions.fill);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
            }
        break;
        
        case obj_puppet_coffeepack:
            //default context menu
            show_debug_message("Context menu names request, cup, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        case obj_puppet_coffee_hot:
        case obj_puppet_coffee_cold:
        case obj_puppet_coffee_microwaved:
        case obj_puppet_borb:
            //default context menu
            show_debug_message("Context menu names request, LIQUIDS, entity: " + string(argument0));
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Spill", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Splash", enum_contextoptions.throw);
            }
        break;
        
        case obj_puppet_powercell:
            //default context menu
            show_debug_message("Context menu names request, powercell, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        case obj_puppet_laserrifle:
            //default context menu
            show_debug_message("Context menu names request, laser rifle, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Arm",   enum_contextoptions.arm);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
            }
        break;
        
        case obj_puppet_wrench:
            //default context menu
            show_debug_message("Context menu names request, cup, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                if global.equiped_entity == argument0 {
                    ds_queue_enqueue(queue_construct_context_menu, "Unequip", enum_contextoptions.unequip);
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Equip", enum_contextoptions.equip);
                }
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        
        
        case obj_furniture_stool:
            //machine context menu
            show_debug_message("Context menu names request, stool, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory == true {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                //grab or deconstruct
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        case obj_furniture_table:
            //machine context menu
            show_debug_message("Context menu names request, table, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory == true {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
            }
            else
            {
                if global.client_grab_entity == -1 
                or is_undefined(obj_client.list_entity_cache[| global.client_grab_entity]) 
                or obj_client.list_entity_cache[| global.client_grab_entity] != my_instance {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                }
                ds_queue_enqueue(queue_construct_context_menu, "Place item on", enum_contextoptions.open);
            }
        break;
        
        case obj_furniture_locker:
            //machine context menu
            show_debug_message("Context menu names request, locker, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory == true {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
            else
            {
                if global.client_grab_entity == -1 
                or is_undefined(obj_client.list_entity_cache[| global.client_grab_entity]) 
                or obj_client.list_entity_cache[| global.client_grab_entity] != my_instance {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                }
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
        break;
        
        case obj_furniture_trashbin:
            //machine context menu
            show_debug_message("Context menu names request, trashbin, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory == true {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
            else
            {
                if global.client_grab_entity == -1 
                or is_undefined(obj_client.list_entity_cache[| global.client_grab_entity]) 
                or obj_client.list_entity_cache[| global.client_grab_entity] != my_instance {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                }
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
        break;
        
        case obj_puppet_janitorcart:
            //machine context menu
            show_debug_message("Context menu names request, janitor cart, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory == true {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
            else
            {
                if global.client_grab_entity == -1 
                or is_undefined(obj_client.list_entity_cache[| global.client_grab_entity]) 
                or obj_client.list_entity_cache[| global.client_grab_entity] != my_instance {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Release", enum_contextoptions.release_grab);
                }
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
            }
        break;
        
        case obj_puppet_microwave:
            //machine context menu
            show_debug_message("Context menu names request, microwave, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Cook",  enum_contextoptions.activate_nopower);
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        case obj_puppet_coffeemaker:
            //machine context menu
            show_debug_message("Context menu names request, coffeemaker, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
            }
            else
            {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Brew",  enum_contextoptions.activate_nopower);
                ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
            }
        break;
        
        
        
        
        case obj_puppet_conduit:
            //machine context menu
            show_debug_message("Context menu names request, conduit or basic machine, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                if global.equiped_object == obj_puppet_wrench ds_queue_enqueue(queue_construct_context_menu, "Install", enum_contextoptions.construct);
            }
            else
            {
                //grab or deconstruct
                if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench {
                    ds_queue_enqueue(queue_construct_context_menu, "Uninstall", enum_contextoptions.grab);
                }
                else if my_instance.constructed == false
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
            }
        break;
        
        case obj_machine_STC:
            //machine context menu
            show_debug_message("Context menu names request, STC, entity: " + string(argument0));
        
            //load the context menu!
            
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if global.equiped_object == obj_puppet_wrench ds_queue_enqueue(queue_construct_context_menu, "Install", enum_contextoptions.construct);
            }
            else {
                if my_instance.constructed == true {
                    if my_instance.goal_state_value == 0 {
                        ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                        ds_queue_enqueue(queue_construct_context_menu, "Assemble",  enum_contextoptions.activate_nopower);
                        ds_queue_enqueue(queue_construct_context_menu, "Uninstall", enum_contextoptions.grab);
                    }
                }
                else
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
            }
        break;
        
        case obj_machine_genorator:
            //machine context menu
            show_debug_message("Context menu names request, conduit or basic machine, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        case obj_machine_outdoorlamp:
            //machine context menu
            show_debug_message("Context menu names request, light outdoor, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        case obj_machine_indoorlamp:
            //machine context menu
            show_debug_message("Context menu names request, light indoor, entity: " + string(argument0));
        
            //load the context menu!
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
                if global.equiped_object == obj_puppet_wrench ds_queue_enqueue(queue_construct_context_menu, "Install", enum_contextoptions.construct);
            }
            else
            {
                if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench {
                    ds_queue_enqueue(queue_construct_context_menu, "Open", enum_contextoptions.open);
                    ds_queue_enqueue(queue_construct_context_menu, "Uninstall", enum_contextoptions.grab);
                }
                else if my_instance.constructed == false
                {
                    ds_queue_enqueue(queue_construct_context_menu, "Grab", enum_contextoptions.grab);
                }
            }
        break;
        
        
        case obj_machine_chargingstation:
            //machine context menu
            show_debug_message("Context menu names request, charging station, entity: " + string(argument0));
        
            //load the context menu!
            if my_instance.constructed == true {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Energize",  enum_contextoptions.activate_powered);
            }
            
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench  {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        
        case obj_machine_fabricator:
            //machine context menu
            show_debug_message("Context menu names request, charging station, entity: " + string(argument0));
        
            //load the context menu!
            if my_instance.constructed == true {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Fabrication",  enum_contextoptions.fab_menu);
            }
            
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench  {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        
        case obj_machine_blueprinter:
            //machine context menu
            show_debug_message("Context menu names request, printer, entity: " + string(argument0));
        
            //load the context menu!
            if my_instance.constructed == true {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Print Blueprint",  enum_contextoptions.printer_menu);
            }
            
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench  {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        
        case obj_machine_elecassem:
            //machine context menu
            show_debug_message("Context menu names request, electro assembler, entity: " + string(argument0));
        
            //load the context menu!
            if my_instance.constructed == true {
                ds_queue_enqueue(queue_construct_context_menu, "Open",  enum_contextoptions.open);
                if my_instance.goal_state_value == 0 ds_queue_enqueue(queue_construct_context_menu, "Fabrication",  enum_contextoptions.electro_menu);
            }
            
            if menu_is_inventory {
                ds_queue_enqueue(queue_construct_context_menu, "Place", enum_contextoptions.drop);
                ds_queue_enqueue(queue_construct_context_menu, "Throw", enum_contextoptions.throw);
                ds_queue_enqueue(queue_construct_context_menu, "Construct", enum_contextoptions.construct);
            }
            else if my_instance.constructed == true and global.equiped_object == obj_puppet_wrench  {
                ds_queue_enqueue(queue_construct_context_menu, "Deconstruct", enum_contextoptions.deconstruct);
            }
        break;
        
        
        case obj_puppet_laserpoint:
            //do not queue anything!
        break;
    }
    
    
    //dequeue and make list! names and storage!
    var index = 0;
    if ds_queue_size(queue_construct_context_menu) > 0 {
        while ds_queue_size(queue_construct_context_menu) > 0 {
            context_menu[index,0] = ds_queue_dequeue(queue_construct_context_menu); //dequeue name
            context_menu[index,1] = ds_queue_dequeue(queue_construct_context_menu); //dequeue entry type
            show_debug_message("Context menu setup:");
            show_debug_message(" -name: " + string(context_menu[index,0]));
            show_debug_message(" -link: " + string(context_menu[index,1]));
            //next index
            index += 1;
        }   
    }
    else
    {
        //remove menu it's empty anyway
        instance_destroy();
    }
    
    
    //cleanup
    ds_queue_destroy(queue_construct_context_menu);
}
else
{
    switch argument3 {
        case enum_contextoptions.open:
            show_debug_message("Context menu event OPEN, entity: " + string(argument0));
            //make the opened inventory
            var getinv = scr_inventory_openwindow( argument0, storagebox_id);
            //setup raidus control 
            with getinv {
                if other.menu_is_inventory == false {
                    //map based context container open
                    in_inventory = false; //by default it doesn't radius disable
                    out_of_inv_x = x;
                    out_of_inv_y = y;
                }
            }
            //cancel context
            instance_destroy();
        break;
    
        case enum_contextoptions.grab:
            show_debug_message("Context menu event GRAB, entity: " + string(argument0));
            //place in player inventory!!!
            scr_spacket_entity_store( argument0, argument1);
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.drop:
            show_debug_message("Context menu event DROP, entity: " + string(argument0));
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                passed_object = other.my_object;
                target_mode = enum_targeter.placing;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.release_grab:
            show_debug_message("Context menu event RELEASE GRAB, entity: " + string(argument0));
            //release grab on object
            scr_spacket_player_release_grab();
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.construct:
            show_debug_message("Context menu event CONSTRUCT, entity: " + string(argument0));
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                passed_object = other.my_object;
                target_mode = enum_targeter.construct;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.deconstruct:
            show_debug_message("Context menu event DECONSTRUCT, entity: " + string(argument0));
            //release grab on object
            scr_spacket_entity_deconstruct(my_entity);
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.throw:
            show_debug_message("Context menu event THROW, entity: " + string(argument0));
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                passed_object = other.my_object;
                target_mode = enum_targeter.throwing;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.load:
            show_debug_message("Context menu event LOAD, entity: " + string(argument0));
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                target_mode = enum_targeter.load;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.fill:
            show_debug_message("Context menu event FILL, entity: " + string(argument0));
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                target_mode = enum_targeter.fill;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.activate_powered:
            show_debug_message("Context menu event activate (requires power/conduit), entity: " + string(argument0));
            //make the targeting controls
            with my_instance {
                if instance_exists(my_conduit) {
                    if my_conduit.power_level - machine_power_draw > 0 {
                        my_conduit.power_level -= machine_power_draw
                        scr_spacket_entity_interact(entityid,id,0);
                    }
                    else
                    {
                        scr_client_errormessage("Not enough power!");
                    }
                }
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.activate_nopower:
            show_debug_message("Context menu event activate (any time), entity: " + string(argument0));
            //make the targeting controls
            with my_instance {
                scr_spacket_entity_interact(entityid,id,0);
            }
            //stc fix
            if my_instance.object_index == obj_machine_STC {
                //close current inventory for the machine
                with obj_inventory_parent {
                    if string(my_entity) == string(other.my_entity) {
                        //remove inventory
                        instance_destroy();
                    }
                }
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.equip:
            show_debug_message("Context menu event EQUIP, entity: " + string(argument0));
            //make the targeting controls
            if global.equiped_entity != argument0 {
                global.equiped_entity = argument0;
                global.equiped_object = argument2;
                global.equiped_ammo = -1;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.unequip:
            show_debug_message("Context menu event UNEQUIP, entity: " + string(argument0));
            //make the targeting controls
            if global.equiped_entity == argument0 {
                global.equiped_entity = -1
                global.equiped_object = noone;
                global.equiped_ammo = -1;
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.arm:
            show_debug_message("Context menu event EQUIP, entity: " + string(argument0));
            //equip weapon
            global.equiped_entity = argument0;
            global.equiped_object = other.my_object;
            global.equiped_ammo = -1;
            
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                my_entity = argument0; //set by context menu on create
                storagebox_entity = argument1;
                passed_object = other.my_object;
                target_mode = enum_targeter.shooting;
                scr_spacket_entity_interact(argument0,id,0); //request ammo count! 
            }
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.prog_card:
            show_debug_message("Context menu event program card, entity: " + string(argument0));
            //make programming menu, ask the card reader to check its inventory and return a menu based on the card inside it
            scr_spacket_entity_interact( argument0, obj_puppet_securitytool, 0); //trigger event in security object, this returns the security data in the card and makes a menu!
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.prog_door:
            show_debug_message("Context menu event program door, entity: " + string(argument0));
            
            //make the targeting controls
            with instance_create(x,y,obj_location_target) {
                target_mode = enum_targeter.door_security;
            }
            
            //cancel context
            instance_destroy();
        break;
        
        case enum_contextoptions.electro_menu:
            if fabmenu_type == 0 fabmenu_type = 2; //set to printer menu
        case enum_contextoptions.printer_menu:
            if fabmenu_type == 0 fabmenu_type = 1; //set to printer menu
        case enum_contextoptions.fab_menu:
            show_debug_message("Context menu event FABMENU, entity: " + string(argument0));
            //make programming menu, ask the card reader to check its inventory and return a menu based on the card inside it
            with my_instance {
                if instance_exists(my_conduit) {
                    if my_conduit.power_level - machine_power_draw > 0 {
                        my_conduit.power_level -= machine_power_draw;
                        
                        if instance_exists(obj_craftingmenu) == false {
                            with instance_create(x,y,obj_craftingmenu) {
                                //location to be on screen
                                var mouse_guix = device_mouse_x_to_gui(0);
                                var mouse_guiy = device_mouse_y_to_gui(0);
                                guix = mouse_guix;
                                guiy = 32//mouse_guiy;
                                
                                ///setup the entity!
                                my_entity = argument0;
                                menu_is_inventory = true;
                                context_menu_width = 0;
                                
                                if fabmenu_type == 0 {
                                    for (k=0; k<array_height_2d(global.crafting_array); k+=1)
                                    {
                                        context_menu[k,0] = global.crafting_array[k,0]; //server handles what is made, the event just passes an index!
                                        context_menu[k,1] = -1;
                                        context_menu[k,2] = false; //locked
                                    }
                                }
                                else if fabmenu_type == 1 
                                {
                                    for (k=0; k<array_height_2d(global.blueprint_array); k+=1)
                                    {
                                        context_menu[k,0] = global.blueprint_array[k,0]; //server handles what is made, the event just passes an index!
                                        context_menu[k,1] = -1;
                                        context_menu[k,2] = false; //locked
                                    }
                                }
                                else if fabmenu_type == 2 
                                {
                                    for (k=0; k<array_height_2d(global.electro_crafting_array); k+=1)
                                    {
                                        context_menu[k,0] = global.electro_crafting_array[k,0]; //server handles what is made, the event just passes an index!
                                        context_menu[k,1] = -1;
                                        context_menu[k,2] = false; //locked
                                    }
                                }
                                event_user(0);
                            }
                        }
                        else
                        {
                            show_message_async("Multiple crafting windows attempted to spawn at once!?");
                        }
                    }
                    else
                    {
                        scr_client_errormessage("Not enough power!");
                    }
                }
            }
            
            //cancel context
            instance_destroy();
        break;
    }
}


