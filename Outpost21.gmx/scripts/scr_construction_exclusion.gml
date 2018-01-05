///scr_construction_exclusion( object being constructed , x, y);
var returnval = true;

switch argument0 {
    
    case obj_furniture_stool:
    case obj_furniture_trashbin:
    case obj_furniture_table:
    case obj_furniture_locker:
        if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_machine_parent,false,true) != noone {
            // cannot build under a machine
            scr_client_errormessage("Cannot place over a machine.");
            returnval = false;
        }
        else if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_furniture_parent,false,true) != noone {
            // cannot build over other furniture
            scr_client_errormessage("Cannot place over other furniture.");
            returnval = false;
        }
    break;
    
    case obj_machine_indoorlamp:
        if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_floor,false,true) == noone {
            //cannot double place conduits
            scr_client_errormessage("Requires floor to be installed in.");
            returnval = false       
        }
        else if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_floormounted_parent,false,true) != noone {
            //cannot double place conduits
            scr_client_errormessage("Machine already installed in floor.");
            returnval = false       
        }
    break;

    case obj_puppet_conduit:
        if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_machine_parent,false,true) != noone { 
            // cannot build under a machine
            scr_client_errormessage("Cannot build over other machine.");
            returnval = false
        }
        else if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_floormounted_parent,false,true) != noone {
            //cannot double place conduits
            scr_client_errormessage("Machine already installed in floor.");
            returnval = false       
        }
    break;
    
    case obj_machine_STC:
        //cannot place atop another conduit
        if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_puppet_conduit,false,true) == noone {
            //requires a conduit under me!
            scr_client_errormessage("Requires a conduit beneath for power.");
            returnval = false;
        }
        else if collision_rectangle(argument1-1,argument2-1,argument1+1,argument2+1,obj_machine_parent,false,true) != noone { 
            // cannot build under a machine
            scr_client_errormessage("Cannot build over other machine.");
            returnval = false;
        }
    break;
    
    
    default:
        scr_client_errormessage("???Object with no construction check was used???");
        returnval = false;
    break;
}

return returnval;
