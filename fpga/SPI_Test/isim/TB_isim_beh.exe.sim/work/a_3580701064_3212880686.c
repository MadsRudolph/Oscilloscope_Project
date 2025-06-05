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
static const char *ng0 = "C:/Users/s240324/Oscilloscope_Project/fpga/SPI_Test/Skifte_reg_til_Parallel.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_3580701064_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned char t9;
    char *t10;
    int t11;
    unsigned char t12;
    int t13;
    int t14;
    char *t15;

LAB0:    xsi_set_current_line(24, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 4376);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(25, ng0);
    t1 = (t0 + 4504);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = 0;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB5:    xsi_set_current_line(27, ng0);
    t2 = (t0 + 1672U);
    t5 = *((char **)t2);
    t4 = *((unsigned char *)t5);
    t9 = (t4 == (unsigned char)3);
    if (t9 != 0)
        goto LAB7;

LAB9:    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t11 = *((int *)t2);
    t4 = (t11 <= 8);
    if (t4 == 1)
        goto LAB12;

LAB13:    t3 = (unsigned char)0;

LAB14:    if (t3 != 0)
        goto LAB10;

LAB11:    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t11 = *((int *)t2);
    t3 = (t11 == 9);
    if (t3 != 0)
        goto LAB15;

LAB16:
LAB8:    goto LAB3;

LAB7:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 4504);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    *((int *)t10) = 0;
    xsi_driver_first_trans_fast(t2);
    goto LAB8;

LAB10:    xsi_set_current_line(30, ng0);
    t1 = (t0 + 2152U);
    t6 = *((char **)t1);
    t13 = *((int *)t6);
    t14 = (t13 + 1);
    t1 = (t0 + 4504);
    t7 = (t1 + 56U);
    t8 = *((char **)t7);
    t10 = (t8 + 56U);
    t15 = *((char **)t10);
    *((int *)t15) = t14;
    xsi_driver_first_trans_fast(t1);
    goto LAB8;

LAB12:    t1 = (t0 + 1672U);
    t5 = *((char **)t1);
    t9 = *((unsigned char *)t5);
    t12 = (t9 == (unsigned char)2);
    t3 = t12;
    goto LAB14;

LAB15:    xsi_set_current_line(32, ng0);
    t1 = (t0 + 4504);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = 0;
    xsi_driver_first_trans_fast(t1);
    goto LAB8;

}

static void work_a_3580701064_3212880686_p_1(char *t0)
{
    char t20[16];
    char t21[16];
    unsigned char t1;
    char *t2;
    char *t3;
    unsigned char t4;
    unsigned char t5;
    char *t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    int t15;
    unsigned char t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t22;
    int t23;
    unsigned int t24;
    unsigned char t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;

LAB0:    xsi_set_current_line(40, ng0);
    t2 = (t0 + 1352U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = (t4 == (unsigned char)3);
    if (t5 == 1)
        goto LAB5;

LAB6:    t2 = (t0 + 1672U);
    t6 = *((char **)t2);
    t7 = *((unsigned char *)t6);
    t8 = (t7 == (unsigned char)3);
    t1 = t8;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:    t2 = (t0 + 992U);
    t4 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t2, 0U, 0U);
    if (t4 == 1)
        goto LAB10;

LAB11:    t1 = (unsigned char)0;

LAB12:    if (t1 != 0)
        goto LAB8;

LAB9:
LAB3:    t2 = (t0 + 4392);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(41, ng0);
    t2 = (t0 + 7424);
    t10 = (t0 + 4568);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    memcpy(t14, t2, 8U);
    xsi_driver_first_trans_fast(t10);
    goto LAB3;

LAB5:    t1 = (unsigned char)1;
    goto LAB7;

LAB8:    xsi_set_current_line(43, ng0);
    t3 = (t0 + 2152U);
    t9 = *((char **)t3);
    t15 = *((int *)t9);
    t8 = (t15 <= 8);
    if (t8 != 0)
        goto LAB13;

LAB15:
LAB14:    goto LAB3;

LAB10:    t3 = (t0 + 1672U);
    t6 = *((char **)t3);
    t5 = *((unsigned char *)t6);
    t7 = (t5 == (unsigned char)2);
    t1 = t7;
    goto LAB12;

LAB13:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 1192U);
    t10 = *((char **)t3);
    t16 = *((unsigned char *)t10);
    t3 = (t0 + 1832U);
    t11 = *((char **)t3);
    t17 = (7 - 7);
    t18 = (t17 * 1U);
    t19 = (0 + t18);
    t3 = (t11 + t19);
    t13 = ((IEEE_P_2592010699) + 4024);
    t14 = (t21 + 0U);
    t22 = (t14 + 0U);
    *((int *)t22) = 7;
    t22 = (t14 + 4U);
    *((int *)t22) = 1;
    t22 = (t14 + 8U);
    *((int *)t22) = -1;
    t23 = (1 - 7);
    t24 = (t23 * -1);
    t24 = (t24 + 1);
    t22 = (t14 + 12U);
    *((unsigned int *)t22) = t24;
    t12 = xsi_base_array_concat(t12, t20, t13, (char)99, t16, (char)97, t3, t21, (char)101);
    t24 = (1U + 7U);
    t25 = (8U != t24);
    if (t25 == 1)
        goto LAB16;

LAB17:    t22 = (t0 + 4568);
    t26 = (t22 + 56U);
    t27 = *((char **)t26);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    memcpy(t29, t12, 8U);
    xsi_driver_first_trans_fast(t22);
    goto LAB14;

LAB16:    xsi_size_not_matching(8U, t24, 0);
    goto LAB17;

}

static void work_a_3580701064_3212880686_p_2(char *t0)
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
    int t11;
    unsigned char t12;

LAB0:    xsi_set_current_line(52, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t4 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t4 == 1)
        goto LAB7;

LAB8:    t3 = (unsigned char)0;

LAB9:    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 4408);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(53, ng0);
    t1 = (t0 + 7432);
    t6 = (t0 + 4632);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 8U);
    xsi_driver_first_trans_fast(t6);
    goto LAB3;

LAB5:    xsi_set_current_line(55, ng0);
    t2 = (t0 + 1832U);
    t6 = *((char **)t2);
    t2 = (t0 + 4632);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t6, 8U);
    xsi_driver_first_trans_fast(t2);
    goto LAB3;

LAB7:    t2 = (t0 + 2152U);
    t5 = *((char **)t2);
    t11 = *((int *)t5);
    t12 = (t11 == 8);
    t3 = t12;
    goto LAB9;

}

static void work_a_3580701064_3212880686_p_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(60, ng0);

LAB3:    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t1 = (t0 + 4696);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 4424);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_3580701064_3212880686_init()
{
	static char *pe[] = {(void *)work_a_3580701064_3212880686_p_0,(void *)work_a_3580701064_3212880686_p_1,(void *)work_a_3580701064_3212880686_p_2,(void *)work_a_3580701064_3212880686_p_3};
	xsi_register_didat("work_a_3580701064_3212880686", "isim/TB_isim_beh.exe.sim/work/a_3580701064_3212880686.didat");
	xsi_register_executes(pe);
}
