///scr_entity_template_library( object_index,x,y,z,dir,speed,indestructable,inside of id);
//makes an entity based on the object input!
var new_entity = -1;

switch argument0 {
    case obj_puppet_cup:
        new_entity = scr_template_entity(argument0,argument1,argument2,argument3,argument4,argument5,argument6,argument7);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits(new_entity,1,true,false,false,false,false,true);
        scr_template_entity_set_storageproperties(new_entity,false,true,false,false,false,false);
    break;
    
    case obj_puppet_toolbox:
        new_entity = scr_template_entity(argument0,argument1,argument2,argument3,argument4,argument5,argument6,argument7);
        //setup a default inventory for the cup! it can store one object!
        scr_template_entity_set_inventorylimits(new_entity,10,true,true,false,false,false,false);
        scr_template_entity_set_storageproperties(new_entity,false,false,true,false,false,false);
    break;
    
    case obj_puppet_borb:
        new_entity = scr_template_entity(argument0,argument1,argument2,argument3,argument4,argument5,argument6,argument7);
        scr_template_entity_set_inventorylimits(new_entity,0,false,false,false,false,false,false);
        scr_template_entity_set_storageproperties(new_entity,false,true,false,false,false,true);
    break;

    case obj_puppet_player:
        //make a new player
        new_entity = scr_template_entity(argument0,argument1,argument2,argument3,argument4,argument5,argument6,argument7);
        //setup a default inventory for the player!
        scr_template_entity_set_inventorylimits(new_entity,8,true,true,true,false,false,false);
        scr_template_entity_set_storageproperties(new_entity,false,false,false,true,false,false);
    break;
    
    default:
        //pop out generic item...
        new_entity = scr_template_entity(obj_puppet_genericitem,argument1,argument2,argument3,argument4,argument5,argument6,argument7);
        scr_template_entity_set_inventorylimits(new_entity,0,false,false,false,false,false,false);
        scr_template_entity_set_storageproperties(new_entity,false,false,true,false,false,false);
    break;
}



return new_entity;
