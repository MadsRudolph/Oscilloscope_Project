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
static const char *ng0 = "C:/Users/s240324/Oscilloscope_Project/fpga/SPI_Test/ProtokolBlok.vhd";
extern char *IEEE_P_2592010699;

char *ieee_p_2592010699_sub_1697423399_503743352(char *, char *, char *, char *, char *, char *);
char *ieee_p_2592010699_sub_795620321_503743352(char *, char *, char *, char *, char *, char *);


static void work_a_2629034234_3212880686_p_0(char *t0)
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
    unsigned char t10;
    unsigned char t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(32, ng0);
    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t4 = xsi_signal_has_event(t1);
    if (t4 == 1)
        goto LAB7;

LAB8:    t3 = (unsigned char)0;

LAB9:    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 7184);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(34, ng0);
    t1 = (t0 + 7328);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)0;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB5:    xsi_set_current_line(36, ng0);
    t2 = (t0 + 2472U);
    t6 = *((char **)t2);
    t11 = *((unsigned char *)t6);
    t2 = (t0 + 7328);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t12 = (t8 + 56U);
    t13 = *((char **)t12);
    *((unsigned char *)t13) = t11;
    xsi_driver_first_trans_fast(t2);
    goto LAB3;

LAB7:    t2 = (t0 + 1032U);
    t5 = *((char **)t2);
    t9 = *((unsigned char *)t5);
    t10 = (t9 == (unsigned char)3);
    t3 = t10;
    goto LAB9;

}

static void work_a_2629034234_3212880686_p_1(char *t0)
{
    char t13[16];
    char t30[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned char t8;
    unsigned int t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    unsigned char t22;
    unsigned char t23;
    unsigned char t24;
    unsigned char t25;
    unsigned char t26;
    unsigned char t27;
    char *t28;
    char *t29;
    static char *nl0[] = {&&LAB3, &&LAB7, &&LAB4, &&LAB5, &&LAB6};

LAB0:    xsi_set_current_line(47, ng0);
    t1 = (t0 + 12655);
    t3 = (t0 + 7392);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t1, 8U);
    xsi_driver_first_trans_fast(t3);
    xsi_set_current_line(50, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t8 = *((unsigned char *)t2);
    t1 = (char *)((nl0) + t8);
    goto **((char **)t1);

LAB2:    t1 = (t0 + 7200);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(52, ng0);
    t3 = (t0 + 7456);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)2;
    xsi_driver_first_trans_fast(t3);
    xsi_set_current_line(54, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12663);
    t8 = 1;
    if (8U == 8U)
        goto LAB11;

LAB12:    t8 = 0;

LAB13:    if (t8 != 0)
        goto LAB8;

LAB10:    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12484U);
    t3 = (t0 + 3592U);
    t4 = *((char **)t3);
    t3 = (t0 + 12548U);
    t5 = ieee_p_2592010699_sub_1697423399_503743352(IEEE_P_2592010699, t13, t2, t1, t4, t3);
    t6 = (t13 + 12U);
    t9 = *((unsigned int *)t6);
    t14 = (1U * t9);
    t7 = (t0 + 12671);
    t8 = 1;
    if (t14 == 8U)
        goto LAB19;

LAB20:    t8 = 0;

LAB21:    if (t8 != 0)
        goto LAB17;

LAB18:    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12484U);
    t3 = (t0 + 3752U);
    t4 = *((char **)t3);
    t3 = (t0 + 12548U);
    t5 = ieee_p_2592010699_sub_795620321_503743352(IEEE_P_2592010699, t13, t2, t1, t4, t3);
    t6 = (t13 + 12U);
    t9 = *((unsigned int *)t6);
    t14 = (1U * t9);
    t7 = (t0 + 12679);
    t23 = 1;
    if (t14 == 8U)
        goto LAB33;

LAB34:    t23 = 0;

LAB35:    if (t23 == 1)
        goto LAB30;

LAB31:    t22 = (unsigned char)0;

LAB32:    if (t22 == 1)
        goto LAB27;

LAB28:    t8 = (unsigned char)0;

LAB29:    if (t8 != 0)
        goto LAB25;

LAB26:    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12484U);
    t3 = (t0 + 3912U);
    t4 = *((char **)t3);
    t3 = (t0 + 12548U);
    t5 = ieee_p_2592010699_sub_1697423399_503743352(IEEE_P_2592010699, t13, t2, t1, t4, t3);
    t6 = (t13 + 12U);
    t9 = *((unsigned int *)t6);
    t14 = (1U * t9);
    t7 = (t0 + 12687);
    t8 = 1;
    if (t14 == 8U)
        goto LAB41;

LAB42:    t8 = 0;

LAB43:    if (t8 != 0)
        goto LAB39;

LAB40:    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12484U);
    t3 = (t0 + 4072U);
    t4 = *((char **)t3);
    t3 = (t0 + 12548U);
    t5 = ieee_p_2592010699_sub_1697423399_503743352(IEEE_P_2592010699, t13, t2, t1, t4, t3);
    t6 = (t13 + 12U);
    t9 = *((unsigned int *)t6);
    t14 = (1U * t9);
    t7 = (t0 + 12695);
    t8 = 1;
    if (t14 == 8U)
        goto LAB49;

LAB50:    t8 = 0;

LAB51:    if (t8 != 0)
        goto LAB47;

LAB48:    xsi_set_current_line(70, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)0;
    xsi_driver_first_trans_fast(t1);

LAB9:    goto LAB2;

LAB4:    xsi_set_current_line(75, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t8 = *((unsigned char *)t2);
    t22 = (t8 == (unsigned char)3);
    if (t22 != 0)
        goto LAB55;

LAB57:    xsi_set_current_line(80, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);

LAB56:    goto LAB2;

LAB5:    xsi_set_current_line(84, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t8 = *((unsigned char *)t2);
    t22 = (t8 == (unsigned char)3);
    if (t22 != 0)
        goto LAB58;

LAB60:    xsi_set_current_line(89, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);

LAB59:    goto LAB2;

LAB6:    xsi_set_current_line(94, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t8 = *((unsigned char *)t2);
    t22 = (t8 == (unsigned char)3);
    if (t22 != 0)
        goto LAB61;

LAB63:    xsi_set_current_line(99, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)4;
    xsi_driver_first_trans_fast(t1);

LAB62:    goto LAB2;

LAB7:    xsi_set_current_line(105, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 12548U);
    t3 = (t0 + 4392U);
    t4 = *((char **)t3);
    t3 = (t0 + 12548U);
    t5 = ieee_p_2592010699_sub_1697423399_503743352(IEEE_P_2592010699, t30, t2, t1, t4, t3);
    t6 = (t0 + 4552U);
    t7 = *((char **)t6);
    t6 = (t0 + 12548U);
    t10 = ieee_p_2592010699_sub_1697423399_503743352(IEEE_P_2592010699, t13, t5, t30, t7, t6);
    t11 = (t13 + 12U);
    t9 = *((unsigned int *)t11);
    t14 = (1U * t9);
    t8 = (8U != t14);
    if (t8 == 1)
        goto LAB64;

LAB65:    t12 = (t0 + 7392);
    t16 = (t12 + 56U);
    t17 = *((char **)t16);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    memcpy(t19, t10, 8U);
    xsi_driver_first_trans_fast(t12);
    xsi_set_current_line(107, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 12703);
    t23 = 1;
    if (8U == 8U)
        goto LAB75;

LAB76:    t23 = 0;

LAB77:    if (t23 == 1)
        goto LAB72;

LAB73:    t22 = (unsigned char)0;

LAB74:    if (t22 == 1)
        goto LAB69;

LAB70:    t8 = (unsigned char)0;

LAB71:    if (t8 != 0)
        goto LAB66;

LAB68:    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    t1 = (t0 + 1512U);
    t3 = *((char **)t1);
    t22 = 1;
    if (8U == 8U)
        goto LAB86;

LAB87:    t22 = 0;

LAB88:    if (t22 == 1)
        goto LAB83;

LAB84:    t8 = (unsigned char)0;

LAB85:    if (t8 != 0)
        goto LAB81;

LAB82:    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    t1 = (t0 + 1512U);
    t3 = *((char **)t1);
    t22 = 1;
    if (8U == 8U)
        goto LAB97;

LAB98:    t22 = 0;

LAB99:    if ((!(t22)) == 1)
        goto LAB94;

LAB95:    t8 = (unsigned char)0;

LAB96:    if (t8 != 0)
        goto LAB92;

LAB93:    xsi_set_current_line(117, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);

LAB67:    goto LAB2;

LAB8:    xsi_set_current_line(55, ng0);
    t6 = (t0 + 7520);
    t7 = (t6 + 56U);
    t10 = *((char **)t7);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t6);
    xsi_set_current_line(56, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 7584);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(57, ng0);
    t1 = (t0 + 7648);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    goto LAB9;

LAB11:    t9 = 0;

LAB14:    if (t9 < 8U)
        goto LAB15;
    else
        goto LAB13;

LAB15:    t4 = (t2 + t9);
    t5 = (t1 + t9);
    if (*((unsigned char *)t4) != *((unsigned char *)t5))
        goto LAB12;

LAB16:    t9 = (t9 + 1);
    goto LAB14;

LAB17:    xsi_set_current_line(59, ng0);
    t16 = (t0 + 1512U);
    t17 = *((char **)t16);
    t16 = (t0 + 7712);
    t18 = (t16 + 56U);
    t19 = *((char **)t18);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t17, 8U);
    xsi_driver_first_trans_fast(t16);
    xsi_set_current_line(60, ng0);
    t1 = (t0 + 7776);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    goto LAB9;

LAB19:    t15 = 0;

LAB22:    if (t15 < t14)
        goto LAB23;
    else
        goto LAB21;

LAB23:    t11 = (t5 + t15);
    t12 = (t7 + t15);
    if (*((unsigned char *)t11) != *((unsigned char *)t12))
        goto LAB20;

LAB24:    t15 = (t15 + 1);
    goto LAB22;

LAB25:    xsi_set_current_line(62, ng0);
    t16 = (t0 + 1512U);
    t19 = *((char **)t16);
    t16 = (t0 + 7840);
    t20 = (t16 + 56U);
    t21 = *((char **)t20);
    t28 = (t21 + 56U);
    t29 = *((char **)t28);
    memcpy(t29, t19, 8U);
    xsi_driver_first_trans_fast(t16);
    xsi_set_current_line(63, ng0);
    t1 = (t0 + 7648);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(64, ng0);
    t1 = (t0 + 7776);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB9;

LAB27:    t16 = (t0 + 2632U);
    t18 = *((char **)t16);
    t26 = *((unsigned char *)t18);
    t27 = (t26 == (unsigned char)3);
    t8 = t27;
    goto LAB29;

LAB30:    t16 = (t0 + 2792U);
    t17 = *((char **)t16);
    t24 = *((unsigned char *)t17);
    t25 = (t24 == (unsigned char)3);
    t22 = t25;
    goto LAB32;

LAB33:    t15 = 0;

LAB36:    if (t15 < t14)
        goto LAB37;
    else
        goto LAB35;

LAB37:    t11 = (t5 + t15);
    t12 = (t7 + t15);
    if (*((unsigned char *)t11) != *((unsigned char *)t12))
        goto LAB34;

LAB38:    t15 = (t15 + 1);
    goto LAB36;

LAB39:    xsi_set_current_line(66, ng0);
    t16 = (t0 + 1512U);
    t17 = *((char **)t16);
    t16 = (t0 + 7904);
    t18 = (t16 + 56U);
    t19 = *((char **)t18);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t17, 8U);
    xsi_driver_first_trans_fast(t16);
    goto LAB9;

LAB41:    t15 = 0;

LAB44:    if (t15 < t14)
        goto LAB45;
    else
        goto LAB43;

LAB45:    t11 = (t5 + t15);
    t12 = (t7 + t15);
    if (*((unsigned char *)t11) != *((unsigned char *)t12))
        goto LAB42;

LAB46:    t15 = (t15 + 1);
    goto LAB44;

LAB47:    xsi_set_current_line(68, ng0);
    t16 = (t0 + 7968);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    *((unsigned char *)t20) = (unsigned char)2;
    xsi_driver_first_trans_fast(t16);
    goto LAB9;

LAB49:    t15 = 0;

LAB52:    if (t15 < t14)
        goto LAB53;
    else
        goto LAB51;

LAB53:    t11 = (t5 + t15);
    t12 = (t7 + t15);
    if (*((unsigned char *)t11) != *((unsigned char *)t12))
        goto LAB50;

LAB54:    t15 = (t15 + 1);
    goto LAB52;

LAB55:    xsi_set_current_line(76, ng0);
    t1 = (t0 + 8032);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(77, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 8096);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(78, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    goto LAB56;

LAB58:    xsi_set_current_line(85, ng0);
    t1 = (t0 + 8160);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(86, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 8224);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(87, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)4;
    xsi_driver_first_trans_fast(t1);
    goto LAB59;

LAB61:    xsi_set_current_line(95, ng0);
    t1 = (t0 + 8288);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(96, ng0);
    t1 = (t0 + 1512U);
    t2 = *((char **)t1);
    t1 = (t0 + 8352);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(97, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB62;

LAB64:    xsi_size_not_matching(8U, t14, 0);
    goto LAB65;

LAB66:    xsi_set_current_line(108, ng0);
    t6 = (t0 + 7456);
    t11 = (t6 + 56U);
    t12 = *((char **)t11);
    t16 = (t12 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = (unsigned char)3;
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(109, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB67;

LAB69:    t6 = (t0 + 1352U);
    t10 = *((char **)t6);
    t26 = *((unsigned char *)t10);
    t27 = (t26 == (unsigned char)3);
    t8 = t27;
    goto LAB71;

LAB72:    t6 = (t0 + 3432U);
    t7 = *((char **)t6);
    t24 = *((unsigned char *)t7);
    t25 = (t24 == (unsigned char)2);
    t22 = t25;
    goto LAB74;

LAB75:    t9 = 0;

LAB78:    if (t9 < 8U)
        goto LAB79;
    else
        goto LAB77;

LAB79:    t4 = (t2 + t9);
    t5 = (t1 + t9);
    if (*((unsigned char *)t4) != *((unsigned char *)t5))
        goto LAB76;

LAB80:    t9 = (t9 + 1);
    goto LAB78;

LAB81:    xsi_set_current_line(112, ng0);
    t5 = (t0 + 7520);
    t7 = (t5 + 56U);
    t10 = *((char **)t7);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(113, ng0);
    t1 = (t0 + 7968);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)0;
    xsi_driver_first_trans_fast(t1);
    goto LAB67;

LAB83:    t5 = (t0 + 3432U);
    t6 = *((char **)t5);
    t23 = *((unsigned char *)t6);
    t24 = (t23 == (unsigned char)3);
    t8 = t24;
    goto LAB85;

LAB86:    t9 = 0;

LAB89:    if (t9 < 8U)
        goto LAB90;
    else
        goto LAB88;

LAB90:    t1 = (t2 + t9);
    t4 = (t3 + t9);
    if (*((unsigned char *)t1) != *((unsigned char *)t4))
        goto LAB87;

LAB91:    t9 = (t9 + 1);
    goto LAB89;

LAB92:    xsi_set_current_line(115, ng0);
    t5 = (t0 + 7968);
    t7 = (t5 + 56U);
    t10 = *((char **)t7);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = (unsigned char)0;
    xsi_driver_first_trans_fast(t5);
    goto LAB67;

LAB94:    t5 = (t0 + 3432U);
    t6 = *((char **)t5);
    t23 = *((unsigned char *)t6);
    t24 = (t23 == (unsigned char)3);
    t8 = t24;
    goto LAB96;

LAB97:    t9 = 0;

LAB100:    if (t9 < 8U)
        goto LAB101;
    else
        goto LAB99;

LAB101:    t1 = (t2 + t9);
    t4 = (t3 + t9);
    if (*((unsigned char *)t1) != *((unsigned char *)t4))
        goto LAB98;

LAB102:    t9 = (t9 + 1);
    goto LAB100;

}

static void work_a_2629034234_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(126, ng0);

LAB3:    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 8416);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 7216);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2629034234_3212880686_p_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(127, ng0);

LAB3:    t1 = (t0 + 4392U);
    t2 = *((char **)t1);
    t1 = (t0 + 8480);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 7232);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2629034234_3212880686_p_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(128, ng0);

LAB3:    t1 = (t0 + 4552U);
    t2 = *((char **)t1);
    t1 = (t0 + 8544);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 7248);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_2629034234_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2629034234_3212880686_p_0,(void *)work_a_2629034234_3212880686_p_1,(void *)work_a_2629034234_3212880686_p_2,(void *)work_a_2629034234_3212880686_p_3,(void *)work_a_2629034234_3212880686_p_4};
	xsi_register_didat("work_a_2629034234_3212880686", "isim/TB_TOP34444_isim_beh.exe.sim/work/a_2629034234_3212880686.didat");
	xsi_register_executes(pe);
}
