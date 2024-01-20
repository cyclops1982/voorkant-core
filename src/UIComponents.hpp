
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include "Backend.hpp"
#include <lvgl.h>
#include "generated/domains.hpp"

class UIEntity
{
public:
  UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent)
  {
    parentContainer = _parent;
    entity = _entity;
  }

protected:
  std::shared_ptr<HAEntity> entity;
  lv_obj_t* parentContainer;
};

static void btn_press_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
}

class UIButton : UIEntity
{
public:
  UIButton(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
    UIEntity(_entity, _parent)
  {
    // START BUTTON EXAMPLE
    lv_obj_t* btn = lv_btn_create(_parent); /*Add a button the current screen*/
    lv_obj_set_size(btn, 240, 50);
    lv_obj_center(btn);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(btn, btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&_entity)); /*Assign a callback to the button*/

    lv_obj_t* label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, _entity->name.c_str()); /*Set the labels text*/
    lv_obj_center(label);
  }

private:
};

class UISwitch : UIEntity
{
public:
  UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
    UIEntity(_entity, _parent)
  {
    // START BUTTON EXAMPLE
    lv_obj_t* switchcontainer = lv_obj_create(_parent);
    lv_obj_set_size(switchcontainer, 240, 50);
    lv_obj_center(switchcontainer);

    lv_obj_t* sw = lv_switch_create(switchcontainer); /*Add a button the current screen*/
    lv_obj_add_event_cb(sw, btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&_entity)); /*Assign a callback to the button*/
    lv_obj_add_flag(sw, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

    lv_obj_t* label = lv_label_create(switchcontainer); /*Add a label to the button*/
    lv_label_set_text(label, _entity->name.c_str()); /*Set the labels text*/
  }
};

#endif