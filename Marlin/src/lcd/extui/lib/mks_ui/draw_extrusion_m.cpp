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
#include "../../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "lv_conf.h"
#include "draw_ui.h"
//#include "../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../lvgl/src/lv_objx/lv_img.h"
//#include "../lvgl/src/lv_core/lv_disp.h"
//#include "../lvgl/src/lv_core/lv_refr.h"

#include "../../../../MarlinCore.h"
#include "../../../../gcode/queue.h"
#include "../../../../module/temperature.h"

extern lv_group_t * g;
static lv_obj_t * scr;

#define ID_T_EXTRUCT      1
#define ID_T_FILAMENT     2
#define ID_T_RETURN       3

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  switch (obj->mks_obj_id) {
    case ID_T_EXTRUCT:
    if (event == LV_EVENT_CLICKED) {
      // nothing to do
    }
    else if (event == LV_EVENT_RELEASED) {
      lv_clear_tool();
      lv_draw_extrusion();
    }
    break;
    case ID_T_FILAMENT:
    if (event == LV_EVENT_CLICKED) {
      // nothing to do
    }
    else if (event == LV_EVENT_RELEASED) {
      uiCfg.desireSprayerTempBak = thermalManager.temp_hotend[uiCfg.curSprayerChoose].target;
      lv_clear_tool();
      lv_draw_filament_change();
    }
    break;
    case ID_T_RETURN:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        TERN_(MKS_TEST, curent_disp_ui = 1);
        lv_clear_tool();
        lv_draw_tool();
      }
      break;
    }
  }

  void lv_draw_extrusion_m(void) {
    scr = lv_screen_create(EXTRUSION_UI_M);

    lv_obj_t *buttonExtrusion, *buttonFilament;
    lv_obj_t *buttonBack;

  if (disp_state_stack._disp_state[disp_state_stack._disp_index] != EXTRUSION_UI_M) {
    disp_state_stack._disp_index++;
    disp_state_stack._disp_state[disp_state_stack._disp_index] = EXTRUSION_UI_M;
  }
  disp_state = EXTRUSION_UI_M;

  scr = lv_obj_create(NULL, NULL);

  lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  (void)lv_label_create(scr, TITLE_XPOS, TITLE_YPOS, creat_title_text());

  lv_refr_now(lv_refr_get_disp_refreshing());

  // Create image buttons

  buttonExtrusion = lv_imgbtn_create(scr, "F:/bmp_extruct.bin", INTERVAL_V, titleHeight, event_handler, ID_T_EXTRUCT);
  buttonFilament = lv_imgbtn_create(scr, "F:/bmp_filamentchange.bin", BTN_X_PIXEL + INTERVAL_V * 2, titleHeight, event_handler, ID_T_FILAMENT);
  buttonBack = lv_imgbtn_create(scr, "F:/bmp_return.bin", BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_T_RETURN);

  lv_obj_set_pos(buttonFilament, INTERVAL_V, titleHeight);
  lv_obj_set_pos(buttonExtrusion, BTN_X_PIXEL + INTERVAL_V * 2, titleHeight);
  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
// #endif

  // Create labels on the image buttons

  lv_obj_t *labelExtrusion  = lv_label_create_empty(buttonExtrusion);
  lv_obj_t *labelFilament   = lv_label_create_empty(buttonFilament);
  lv_obj_t *label_Back      = lv_label_create_empty(buttonBack);

  if (gCfgItems.multiple_language != 0) {
    lv_label_set_text(labelExtrusion, tool_menu.extrude);
    lv_obj_align(labelExtrusion, buttonExtrusion, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelFilament, tool_menu.filament);
    lv_obj_align(labelFilament, buttonFilament, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(label_Back, common_menu.text_back);
    lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
  }

  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) {
      lv_group_add_obj(g, buttonExtrusion);
      lv_group_add_obj(g, buttonFilament);
      lv_group_add_obj(g, buttonBack);
    }
  #endif
}

#endif // HAS_TFT_LVGL_UI
