/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xc3576ebc */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/s240324/Oscilloscope_Project/fpga/SignalGenerator/DispMux.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_3620187407;

unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_2941962287_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    unsigned char t11;
    int t12;
    int t13;
    int t15;
    char *t16;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;

LAB0:    xsi_set_current_line(25, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 1632U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 3880);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(26, ng0);
    t1 = (t0 + 6388);
    t6 = (t0 + 3976);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 2U);
    xsi_driver_first_trans_fast(t6);
    goto LAB3;

LAB5:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 1832U);
    t5 = *((char **)t2);
    t4 = *((unsigned char *)t5);
    t11 = (t4 == (unsigned char)3);
    if (t11 != 0)
        goto LAB7;

LAB9:
LAB8:    goto LAB3;

LAB7:    xsi_set_current_line(29, ng0);
    t2 = (t0 + 2152U);
    t6 = *((char **)t2);
    t2 = (t0 + 6390);
    t12 = xsi_mem_cmp(t2, t6, 2U);
    if (t12 == 1)
        goto LAB11;

LAB15:    t8 = (t0 + 6392);
    t13 = xsi_mem_cmp(t8, t6, 2U);
    if (t13 == 1)
        goto LAB12;

LAB16:    t10 = (t0 + 6394);
    t15 = xsi_mem_cmp(t10, t6, 2U);
    if (t15 == 1)
        goto LAB13;

LAB17:
LAB14:    xsi_set_current_line(33, ng0);
    t1 = (t0 + 6402);
    t5 = (t0 + 3976);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 2U);
    xsi_driver_first_trans_fast(t5);

LAB10:    goto LAB8;

LAB11:    xsi_set_current_line(30, ng0);
    t16 = (t0 + 6396);
    t18 = (t0 + 3976);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    memcpy(t22, t16, 2U);
    xsi_driver_first_trans_fast(t18);
    goto LAB10;

LAB12:    xsi_set_current_line(31, ng0);
    t1 = (t0 + 6398);
    t5 = (t0 + 3976);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 2U);
    xsi_driver_first_trans_fast(t5);
    goto LAB10;

LAB13:    xsi_set_current_line(32, ng0);
    t1 = (t0 + 6400);
    t5 = (t0 + 3976);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 2U);
    xsi_driver_first_trans_fast(t5);
    goto LAB10;

LAB18:;
}

static void work_a_2941962287_3212880686_p_1(char *t0)
{
    char t5[16];
    char t15[16];
    char t17[16];
    char t21[16];
    char t25[16];
    char *t1;
    char *t2;
    char *t3;
    char *t6;
    char *t7;
    int t8;
    unsigned int t9;
    unsigned char t10;
    char *t12;
    char *t13;
    char *t14;
    char *t16;
    char *t18;
    char *t19;
    int t20;
    char *t22;
    int t23;
    char *t24;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned char t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;

LAB0:    xsi_set_current_line(44, ng0);
    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t1 = (t0 + 6340U);
    t3 = (t0 + 6404);
    t6 = (t5 + 0U);
    t7 = (t6 + 0U);
    *((int *)t7) = 0;
    t7 = (t6 + 4U);
    *((int *)t7) = 1;
    t7 = (t6 + 8U);
    *((int *)t7) = 1;
    t8 = (1 - 0);
    t9 = (t8 * 1);
    t9 = (t9 + 1);
    t7 = (t6 + 12U);
    *((unsigned int *)t7) = t9;
    t10 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t2, t1, t3, t5);
    if (t10 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t1 = (t0 + 6340U);
    t3 = (t0 + 6423);
    t6 = (t5 + 0U);
    t7 = (t6 + 0U);
    *((int *)t7) = 0;
    t7 = (t6 + 4U);
    *((int *)t7) = 1;
    t7 = (t6 + 8U);
    *((int *)t7) = 1;
    t8 = (1 - 0);
    t9 = (t8 * 1);
    t9 = (t9 + 1);
    t7 = (t6 + 12U);
    *((unsigned int *)t7) = t9;
    t10 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t2, t1, t3, t5);
    if (t10 != 0)
        goto LAB7;

LAB8:    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t1 = (t0 + 6340U);
    t3 = (t0 + 6437);
    t6 = (t5 + 0U);
    t7 = (t6 + 0U);
    *((int *)t7) = 0;
    t7 = (t6 + 4U);
    *((int *)t7) = 1;
    t7 = (t6 + 8U);
    *((int *)t7) = 1;
    t8 = (1 - 0);
    t9 = (t8 * 1);
    t9 = (t9 + 1);
    t7 = (t6 + 12U);
    *((unsigned int *)t7) = t9;
    t10 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t2, t1, t3, t5);
    if (t10 != 0)
        goto LAB11;

LAB12:
LAB3:    t1 = (t0 + 3896);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(45, ng0);
    t7 = (t0 + 6406);
    t12 = (t0 + 6418);
    t16 = ((IEEE_P_2592010699) + 4024);
    t18 = (t17 + 0U);
    t19 = (t18 + 0U);
    *((int *)t19) = 0;
    t19 = (t18 + 4U);
    *((int *)t19) = 11;
    t19 = (t18 + 8U);
    *((int *)t19) = 1;
    t20 = (11 - 0);
    t9 = (t20 * 1);
    t9 = (t9 + 1);
    t19 = (t18 + 12U);
    *((unsigned int *)t19) = t9;
    t19 = (t21 + 0U);
    t22 = (t19 + 0U);
    *((int *)t22) = 0;
    t22 = (t19 + 4U);
    *((int *)t22) = 4;
    t22 = (t19 + 8U);
    *((int *)t22) = 1;
    t23 = (4 - 0);
    t9 = (t23 * 1);
    t9 = (t9 + 1);
    t22 = (t19 + 12U);
    *((unsigned int *)t22) = t9;
    t14 = xsi_base_array_concat(t14, t15, t16, (char)97, t7, t17, (char)97, t12, t21, (char)101);
    t22 = (t0 + 1032U);
    t24 = *((char **)t22);
    t26 = ((IEEE_P_2592010699) + 4024);
    t27 = (t0 + 6276U);
    t22 = xsi_base_array_concat(t22, t25, t26, (char)97, t14, t15, (char)97, t24, t27, (char)101);
    t9 = (12U + 5U);
    t28 = (t9 + 3U);
    t29 = (20U != t28);
    if (t29 == 1)
        goto LAB5;

LAB6:    t30 = (t0 + 4040);
    t31 = (t30 + 56U);
    t32 = *((char **)t31);
    t33 = (t32 + 56U);
    t34 = *((char **)t33);
    memcpy(t34, t22, 20U);
    xsi_driver_first_trans_fast_port(t30);
    goto LAB3;

LAB5:    xsi_size_not_matching(20U, t28, 0);
    goto LAB6;

LAB7:    xsi_set_current_line(50, ng0);
    t7 = (t0 + 6425);
    t12 = (t0 + 1192U);
    t13 = *((char **)t12);
    t14 = ((IEEE_P_2592010699) + 4024);
    t16 = (t17 + 0U);
    t18 = (t16 + 0U);
    *((int *)t18) = 0;
    t18 = (t16 + 4U);
    *((int *)t18) = 11;
    t18 = (t16 + 8U);
    *((int *)t18) = 1;
    t20 = (11 - 0);
    t9 = (t20 * 1);
    t9 = (t9 + 1);
    t18 = (t16 + 12U);
    *((unsigned int *)t18) = t9;
    t18 = (t0 + 6292U);
    t12 = xsi_base_array_concat(t12, t15, t14, (char)97, t7, t17, (char)97, t13, t18, (char)101);
    t9 = (12U + 8U);
    t29 = (20U != t9);
    if (t29 == 1)
        goto LAB9;

LAB10:    t19 = (t0 + 4040);
    t22 = (t19 + 56U);
    t24 = *((char **)t22);
    t26 = (t24 + 56U);
    t27 = *((char **)t26);
    memcpy(t27, t12, 20U);
    xsi_driver_first_trans_fast_port(t19);
    goto LAB3;

LAB9:    xsi_size_not_matching(20U, t9, 0);
    goto LAB10;

LAB11:    xsi_set_current_line(54, ng0);
    t7 = (t0 + 6439);
    t12 = (t0 + 1352U);
    t13 = *((char **)t12);
    t14 = ((IEEE_P_2592010699) + 4024);
    t16 = (t17 + 0U);
    t18 = (t16 + 0U);
    *((int *)t18) = 0;
    t18 = (t16 + 4U);
    *((int *)t18) = 11;
    t18 = (t16 + 8U);
    *((int *)t18) = 1;
    t20 = (11 - 0);
    t9 = (t20 * 1);
    t9 = (t9 + 1);
    t18 = (t16 + 12U);
    *((unsigned int *)t18) = t9;
    t18 = (t0 + 6308U);
    t12 = xsi_base_array_concat(t12, t15, t14, (char)97, t7, t17, (char)97, t13, t18, (char)101);
    t9 = (12U + 8U);
    t29 = (20U != t9);
    if (t29 == 1)
        goto LAB13;

LAB14:    t19 = (t0 + 4040);
    t22 = (t19 + 56U);
    t24 = *((char **)t22);
    t26 = (t24 + 56U);
    t27 = *((char **)t26);
    memcpy(t27, t12, 20U);
    xsi_driver_first_trans_fast_port(t19);
    goto LAB3;

LAB13:    xsi_size_not_matching(20U, t9, 0);
    goto LAB14;

}


extern void work_a_2941962287_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2941962287_3212880686_p_0,(void *)work_a_2941962287_3212880686_p_1};
	xsi_register_didat("work_a_2941962287_3212880686", "isim/FULL_BENCH_isim_beh.exe.sim/work/a_2941962287_3212880686.didat");
	xsi_register_executes(pe);
}
