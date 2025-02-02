/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#ifdef __cplusplus
  extern "C" { /* C-declarations for C++ */
#endif

extern void lv_draw_ready_print();
extern void mks_disp_test();
extern void disp_Limit_ok();
extern void disp_Limit_error();
extern void disp_det_error();
extern void disp_det_ok();
extern void lv_clear_ready_print();
extern void disp_ext_temp();
extern void disp_bed_temp();
extern void lv_temp_info();
extern void lv_temp_refr();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
