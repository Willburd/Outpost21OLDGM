///scr_castshadows_main( lightx, lighty, radius, offsetx, offsety , light offsetx, light offsety);
//called inside the surface!!! DOES NOT CLEAR ALPHA!
        
var xoff = argument3;
var yoff = argument4;

var lx = (argument0 + argument5) - xoff;       // the light position
var ly = (argument1 + argument6) - yoff;
var rad = argument2;



//draw_arrow(0,0,lx,ly,10);   
//draw_rectangle(lx-10,ly-10,lx+10,ly+10,true);

var nearest_test = instance_nearest(argument0,argument1,obj_wall);
if instance_exists(nearest_test) {
    if point_distance(nearest_test.x,nearest_test.y,argument0,argument1) <= rad {
        
        //collect instances
        vertex_begin(VBuffer, VertexFormat);
        with obj_wall {
            if visible == true and scr_inview(x,y,0,50) {
                //get loaded instance!
                var get_inst = id;
                
                //shadow exclusions
                if get_inst.visible == true {
                    if get_inst.object_index == obj_door {
                        var alpha = 1-(get_inst.panel_slide/16);
                    }
                    else if get_inst.object_index == obj_window
                    {
                        var alpha = 0.6;
                    }
                    else if get_inst.object_index == obj_fence {
                        var alpha = 0;
                    }
                    else
                    {
                        //default wall
                        var alpha = 1;
                    }
                
                    // get corners of the 
                    if alpha > 0 {
                        var shadow_walltop = 50;
                        
                        if get_inst.image_angle == 0 {
                            //vertical walls
                            /*
                            var yoffset = clamp((argument1+56) - get_inst.y,0,50);
                            var px1 = get_inst.x     -  xoff;     // top left
                            var py1 = get_inst.y-32 - yoffset  -  yoff;
                            var yoffset = clamp((argument1-11) - get_inst.y,0,50); //aligned
                            var px2 = get_inst.x     -  xoff;    // bottom right
                            var py2 = get_inst.y+32 - yoffset  -  yoff;
                            */
                            
                            var px1 = (get_inst.x     -  xoff);     // top left
                            var py1 = (get_inst.y-32  -  yoff - shadow_walltop);
                            var yoffset = clamp((argument1-11) - get_inst.y,0,shadow_walltop); //aligned
                            var px2 = (get_inst.x     -  xoff);    // bottom right
                            var py2 = (get_inst.y+32 - yoffset  -  yoff);
                        }
                        else 
                        {
                            //horizontal walls
                            /*var yoffset = clamp((argument1+21) - (get_inst.y),0,50); //aligned
                            var px1 = get_inst.x-32  -  xoff;     // top left
                            var py1 = get_inst.y - yoffset        -  yoff;
                            var px2 = get_inst.x+32  -  xoff;    // bottom right
                            var py2 = get_inst.y - yoffset        -  yoff;*/
                            
                            var yoffset = clamp((argument1+21) - (get_inst.y),0,shadow_walltop); //aligned
                            var px1 = (get_inst.x-32  -  xoff);     // top left
                            var py1 = (get_inst.y     -  yoff - shadow_walltop);
                            var px2 = (get_inst.x+32  -  xoff);    // bottom right
                            var py2 = (get_inst.y     -  yoff - yoffset);
                        }
                        
                        //sign test to only project the minimum we need to!
                        if( !SignTest( px1,py1, px2,py1, lx,ly) ){
                            ProjectShadow(other.VBuffer,  px1,py1, px2,py1, lx,ly, alpha );
                        }
                        if( !SignTest( px2,py1, px2,py2, lx,ly) ){
                            ProjectShadow(other.VBuffer,  px2,py1, px2,py2, lx,ly, alpha );
                        }
                        if( !SignTest( px2,py2, px1,py2, lx,ly) ){
                            ProjectShadow(other.VBuffer,  px2,py2, px1,py2, lx,ly, alpha );
                        }
                        if( !SignTest( px1,py2, px1,py1, lx,ly) ){
                            ProjectShadow(other.VBuffer,  px1,py2, px1,py1, lx,ly, alpha );                      
                        }
                    }
                }
            }
        }
        
        vertex_end(VBuffer);    
        vertex_submit(VBuffer,pr_trianglelist,-1);        
    }
}
