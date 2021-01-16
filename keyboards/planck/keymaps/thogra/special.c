// special.c

// Include required headers
#include "special.h"


// ------------------------------------------------------------------
//
//                           Definitions
//
// ------------------------------------------------------------------

// Internal variables
Key   _key                            = {0, MOD_NONE, 0, MOD_NONE};
bool  _shift      = false;
bool  _shiftEvent = false;





// ------------------------------------------------------------------
//
//                               Key
//
// ------------------------------------------------------------------

// +++++++
// Methods
// +++++++

// -------
// pressed
// -------
void pressed
(
  Key          key,
  keyrecord_t* record
)
{
  // If key was pressed (or method was called from pressedShift() indicated by shift event)
  if (record->event.pressed || _shiftEvent==true)
  {
    // Key pressed without 'shift', or ..
    _shiftEvent = false;
    if (_shift == false) 
    {
      // Set the modifiers
      if (key.keycodeModifier & MOD_ALT)      register_code(KC_LALT);
      else                                    unregister_code(KC_LALT);
      if (key.keycodeModifier & MOD_ALTGR)    register_code(KC_RALT);
      else                                    unregister_code(KC_RALT);
      if (key.keycodeModifier & MOD_CTRL)     register_code(KC_LCTL);
      else                                    unregister_code(KC_LCTL);
      if (key.keycodeModifier & MOD_SHIFT)    register_code(KC_LSHIFT);
      else                                    unregister_code(KC_LSHIFT);

      // Set key code
      register_code(key.keycode);
    } 
    
    // .. key pressed with 'shift' modifier
    else
    {
      // Set the modifiers
      if (key.shiftedKeycodeModifier & MOD_ALT)     register_code(KC_LALT);
      else                                          unregister_code(KC_LALT);
      if (key.shiftedKeycodeModifier & MOD_ALTGR)   register_code(KC_RALT);
      else                                          unregister_code(KC_RALT);
      if (key.shiftedKeycodeModifier & MOD_CTRL)    register_code(KC_LCTL);
      else                                          unregister_code(KC_LCTL);
      if (key.shiftedKeycodeModifier & MOD_SHIFT)   register_code(KC_LSHIFT);
      else                                          unregister_code(KC_LSHIFT);

      // Set key code
      register_code(key.shiftedKeycode);
    };
    
    // Update the global key information
    _key.keycode                = key.keycode;
    _key.keycodeModifier        = key.keycodeModifier;
    _key.shiftedKeycode         = key.shiftedKeycode;
    _key.shiftedKeycodeModifier = key.shiftedKeycodeModifier;
  }
  
  // .. else key was released
  else
  {
    // Key released without 'shift', or ..
    if (_shift == false)
    {
      // Unregister key code 
      unregister_code(key.keycode);
      
      // Unregister modifiers
      if (key.shiftedKeycodeModifier & MOD_ALT)     unregister_code(KC_LALT);
      if (key.shiftedKeycodeModifier & MOD_ALTGR)   unregister_code(KC_RALT);
      if (key.shiftedKeycodeModifier & MOD_CTRL)    unregister_code(KC_LCTL);
      unregister_code(KC_LSHIFT);
    }

    // .. key released with 'shift' modifier
    else
    {
      // Unregister key code 
      unregister_code(key.shiftedKeycode);

      // Unregister modifiers
      if (key.shiftedKeycodeModifier & MOD_ALT)     unregister_code(KC_LALT);
      if (key.shiftedKeycodeModifier & MOD_ALTGR)   unregister_code(KC_RALT);
      if (key.shiftedKeycodeModifier & MOD_CTRL)    unregister_code(KC_LCTL);

      // .. but shift needs to be set
      register_code(KC_LSHIFT);
    };
    
    // Update the global key information
    _key.keycode                = 0;
    _key.keycodeModifier        = MOD_NONE;
    _key.shiftedKeycode         = 0;
    _key.shiftedKeycodeModifier = MOD_NONE;
  };
};



// ------------
// pressedShift
// ------------
void pressedShift
(
  keyrecord_t*  record
)
{
  // Update shift indicator
  if (record->event.pressed)     _shift = true;
  else                           _shift = false;

  // If currently one of the special key definitions is pressed
  if (_key.keycode!=0 || _key.shiftedKeycode!=0)
  {
    _shiftEvent = true;
    pressed(_key, record);
  }

  // Any other key was pressed together with 'shift' - just apply 'shift'
  else
  {  
    _shiftEvent = false;
    if (_shift == true)     register_code(KC_LSHIFT);
		else                    unregister_code(KC_LSHIFT);
  };
};

