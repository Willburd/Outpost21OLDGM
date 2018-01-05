//scr_instance_in_rectangle(x1,t1,x2,y2,object);
var objects=ds_queue_create();
//instanceNumber=instance_number(argument4)
var X1 = argument0;
var Y1 = argument1;
var X2 = argument2;
var Y2 = argument3;
/*
for(i=0;i<instanceNumber;i+=1){
    instance=instance_find(argument4,i);
    if((instance.x<X1&&instance.x>X2)||(instance.x>X1&&instance.x<X2)){
        if((instance.y<Y1&&instance.y>Y2)||(instance.y>Y1&&instance.y<Y2)){
            ds_queue_enqueue(objects,instance);
        }
    }
}*/

//faster?
with argument4 {
    if point_in_rectangle(x,y,X1,Y1,X2,Y2) ds_queue_enqueue(objects,id);
}

//return is only needed if you put this in your own script.
return objects;
