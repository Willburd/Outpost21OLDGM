///scr_tooltip_update("text");
if instance_exists(obj_tooltip) == false instance_create(x,y,obj_tooltip);
with obj_tooltip {
    tooltip_text = argument0;
    if instance_exists(obj_contextmenu) == false image_alpha = clamp(image_alpha+0.15,0,0.80);
}
