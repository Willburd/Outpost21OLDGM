///scr_server_entity_classstoragecheck( item class, storage allowed, clientid);
var allow_item = false;

switch argument1 {
    case enum_itemclass.generic:
    case enum_itemclass.ship:
        //allows all classes inside!
        allow_item = true;
    break;
    
    case enum_itemclass.tools:
        //only tools and related allowed
        if argument0 == enum_itemclass.tools allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold tools.");
        }
    break;
    
    case enum_itemclass.sheets:
        if argument0 == enum_itemclass.sheets allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold sheets.");
        }
    break;
    
    case enum_itemclass.food:
        if argument0 == enum_itemclass.food allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold food.");
        }
    break;
    
    case enum_itemclass.machines:
        if argument0 == enum_itemclass.machines allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold machines.");
        }
    break;
    
    case enum_itemclass.machine_parts:
        if argument0 == enum_itemclass.machine_parts allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold machine parts.");
        }
    break;
    
    case enum_itemclass.clothing:
        if argument0 == enum_itemclass.clothing allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold clothing.");
        }
    break;
    
    case enum_itemclass.rifle:
        if argument0 == enum_itemclass.rifle allow_item = true;
    case enum_itemclass.pistol:
        if argument0 == enum_itemclass.pistol allow_item = true;
        
        if allow_item == false {
            scr_cpacket_failed_action( argument2, "Object can only hold firearms.");
        }
    break;
}

return allow_item;
