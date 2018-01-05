///scr_construction_alignment(x,y,constructing);
var return_list = ds_list_create();
//move me!
if argument2 == true {
    if passed_object == obj_floormounted_parent or object_get_parent(passed_object) == obj_floormounted_parent 
    or passed_object == obj_machine_parent or object_get_parent(passed_object) == obj_machine_parent 
    or passed_object == obj_machine_light_parent or object_get_parent(passed_object) == obj_machine_light_parent {
        //machines and conduits!
        return_list[| 0] = (64*round(argument0/64));
        return_list[| 1] = 32+(64*round((argument1-32)/64));
    }
    else if passed_object == obj_furniture_parent or object_get_parent(passed_object) == obj_furniture_parent {
        //begin furniture!
        return_list[| 0] = (16*round(argument0/16));
        return_list[| 1] = (16*round(argument1/16));
    }
    else
    {
        //pass through.
        return_list[| 0] = argument0; 
        return_list[| 1] = argument1;
    }
}
else
{
    //pass through.
    return_list[| 0] = argument0; 
    return_list[| 1] = argument1;
}

return return_list;
