///scr_inventoryobject_removeentity( entity id);
//removes an item from all on screen inventories
var get_item_entity = argument0;

with obj_inventory_parent {
    var i = 0;
    var begin_pullback = 0;
    for (i=0; i<inventory_sized; i+=1)
    {
        if begin_pullback == false {
            if array_inventory[i,0] == argument0 {
                array_inventory[i,0] = -1; //entity id
                array_inventory[i,1] = -1; //object_index
                
                i -= 1; //pull back one slot so we can go backwards and pushback this one
                begin_pullback = true; //flag for inventory pushback
            }
            else
            {
                //keep itterating...
            }
        }
        else
        {
            //begin pushing inventory backwards to fill the lost slot
            if i < inventory_sized-1 {
                array_inventory[i,0] = array_inventory[i+1,0]; //entity id
                array_inventory[i,1] = array_inventory[i+1,1]; //object_index
            }
            else
            {
                array_inventory[i,0] = -1; //entity id
                array_inventory[i,1] = -1; //object_index
            }
        }
    }
}
