///scr_inview(x,y,view,border);
gml_pragma("forceinline");
var border = argument3;
return point_in_rectangle(argument0,argument1,view_xview[argument2]-border,view_yview[argument2]-border,view_xview[argument2]+view_wview[argument2]+border,view_yview[argument2]+view_hview[argument2]+border);
