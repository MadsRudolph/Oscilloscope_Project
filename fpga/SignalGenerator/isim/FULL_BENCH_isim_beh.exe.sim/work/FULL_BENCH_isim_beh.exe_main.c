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

#include "xsi.h"

struct XSI_INFO xsi_info;

char *IEEE_P_3620187407;
char *IEEE_P_2592010699;
char *IEEE_P_3499444699;
char *STD_TEXTIO;
char *STD_STANDARD;
char *IEEE_P_3564397177;


int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    ieee_p_2592010699_init();
    ieee_p_3499444699_init();
    ieee_p_3620187407_init();
    work_a_0440160552_3212880686_init();
    work_a_4002409220_3212880686_init();
    work_a_3343343606_3212880686_init();
    work_a_2629034234_3212880686_init();
    work_a_3580701064_3212880686_init();
    work_a_3801684503_3212880686_init();
    work_a_0800547850_3212880686_init();
    std_textio_init();
    ieee_p_3564397177_init();
    xilinxcorelib_a_1380994670_2959432447_init();
    xilinxcorelib_a_4108295616_1709443946_init();
    xilinxcorelib_a_2347390556_0543512595_init();
    xilinxcorelib_a_0140052046_3212880686_init();
    work_a_2186922994_1482076668_init();
    work_a_0720361590_3212880686_init();
    work_a_3958530957_3366848769_init();
    work_a_0840209509_2117282823_init();
    work_a_2941962287_3212880686_init();
    work_a_1421884221_3212880686_init();
    work_a_3455286857_3212880686_init();
    work_a_3885981467_2372691052_init();


    xsi_register_tops("work_a_3885981467_2372691052");

    IEEE_P_3620187407 = xsi_get_engine_memory("ieee_p_3620187407");
    IEEE_P_2592010699 = xsi_get_engine_memory("ieee_p_2592010699");
    xsi_register_ieee_std_logic_1164(IEEE_P_2592010699);
    IEEE_P_3499444699 = xsi_get_engine_memory("ieee_p_3499444699");
    STD_TEXTIO = xsi_get_engine_memory("std_textio");
    STD_STANDARD = xsi_get_engine_memory("std_standard");
    IEEE_P_3564397177 = xsi_get_engine_memory("ieee_p_3564397177");

    return xsi_run_simulation(argc, argv);

}
