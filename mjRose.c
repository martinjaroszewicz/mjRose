//
//  mjRose.c
//  mjRose
//
//  Created by Martin Jaroszewicz on 7/20/14.
//  Copyright (c) 2014 com.martinjaroszewicz. All rights reserved.
// // This works with HOA Library

#include "m_pd.h"
#include <math.h>
#include <string.h>

static t_class *mjRose_class;

typedef struct _mjRose {
	t_object x_obj;
	//local variables
	t_float f_position;
	t_float f_mult;
	t_float f_n;
	t_float f_d;
	t_float f_z;
	t_outlet *l1_out, *l2_out, *l3_out, *l4_out;
} t_mjRose;




void mjRose_float(t_mjRose *x, t_float f){
    
    double n;
    double d;
    modf(x->f_n,&n);
    modf(x->f_d,&d);
    int z = x->f_z;
    int in = n;
    int id = d;
    if(in%in != 0 && id%id !=0){
        x->f_mult = M_PI*2*d;
    } else {
        x->f_mult = M_PI*d;
    }
    x->f_position = f;
    float position = x->f_position*x->f_mult;
    float rose = sinf((n/d)*position);
    float out_x = rose*cosf(position);
    float out_y = rose*sinf(position);
    float out_z = rose*sinf(z);
    outlet_float(x->l1_out, out_x);
    outlet_float(x->l2_out, out_y);
    outlet_float(x->l3_out, out_z);
    if (out_z == 0.0 && out_y == 0.0 && out_z == 0.0){
        outlet_bang(x->l4_out);
    }
}

void *mjRose_new(t_floatarg f){
    
    t_mjRose *x = (t_mjRose *)pd_new(mjRose_class);
    x->f_n = 1;
    x->f_d = 1;
    x->f_z = 0;
    x->l1_out = outlet_new(&x->x_obj, &s_float);
    x->l2_out = outlet_new(&x->x_obj, &s_float);
    x->l3_out = outlet_new(&x->x_obj, &s_float);
    x->l4_out = outlet_new(&x->x_obj, &s_bang);
    floatinlet_new(&x->x_obj, &x->f_n);
    floatinlet_new(&x->x_obj, &x->f_d);
    floatinlet_new(&x->x_obj, &x->f_z);
    post("mj Library by Martin Jaroszewicz.");
    post("© 2014 UCR Riverside");
    post("Version Beta 0.1 (August 9 2014) for PD-extended v.0.43.4");
    
    return (void *)x;
}

void mjRose_setup(void) {
    mjRose_class = class_new(gensym("mjRose"),
    (t_newmethod)mjRose_new,
            0, sizeof(t_mjRose),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);
    class_addfloat(mjRose_class, mjRose_float);
    
}
