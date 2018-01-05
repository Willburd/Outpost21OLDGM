///scr_tooltip_construct( object_index, entity number);
if instance_exists(obj_tooltip) == false instance_create(x,y,obj_tooltip);

with obj_tooltip {
    if last_used_index != argument1 and image_alpha >= 0 {
        //update so we don't spam packets
        network_query = "";
        last_used_index = argument1;
        image_alpha = -0.5
        
        //reset security pips
        for (var i=0; i<ds_list_size(global.list_security_levels)+10; i+=1)
        {
            list_security_dots[ i] = -1;
        }
    
        //load new data
        switch argument0 {
            default:
                var get_str = global.obj_names[| argument0];
                if is_undefined(get_str) {
                    tooltip_text = "";
                }
                else
                {
                    tooltip_text = get_str;
                }
            break;
        
            case obj_puppet_player:
                tooltip_text = "Player: ";
                scr_spacket_entity_interact(argument1,id,0); //request name of character
            break;
            
            case obj_puppet_powercell:
                tooltip_text = "Powercell %";
                scr_spacket_entity_interact(argument1,id,0); //request power charge
            break;
            
            case obj_puppet_securitycard:
                tooltip_text = "Security Card";
                scr_spacket_entity_interact(argument1,id,0); //request security level status in card
            break;
        }
    }
    
    //fade in and out
    if instance_exists(obj_contextmenu) == false image_alpha = clamp(image_alpha+0.15,0,0.80);
}
