// special.c

// Include required headers
#include "special.h"


// ------------------------------------------------------------------
//
//                           Definitions
//
// ------------------------------------------------------------------

// Internal variables
Key   _key        = {0, false, 0, true};
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
    // Key pressed with 'shift', or ..
    _shiftEvent = false;
    if (_shift == false) 
    {
      if (key.keycodeNeedsShift == true)     register_code(KC_LSHIFT);
      else                                   unregister_code(KC_LSHIFT);
      register_code(key.keycode);
    } 
    
    // .. key pressed with 'shift' modifier
    else
    {
      if (key.shiftedKeycodeNeedsShift == true)     register_code(KC_LSHIFT);
      else                                          unregister_code(KC_LSHIFT);
      register_code(key.shiftedKeycode);
    };
    
    // Update the global key information
    _key.keycode                  = key.keycode;
    _key.keycodeNeedsShift        = key.keycodeNeedsShift;
    _key.shiftedKeycode           = key.shiftedKeycode;
    _key.shiftedKeycodeNeedsShift = key.shiftedKeycodeNeedsShift;
  }
  
  // .. else key was released
  else
  {
    // Key released with 'shift', or ..
    if (_shift == false)
    {
      unregister_code(key.keycode);
      unregister_code(KC_LSHIFT);
    }

    // .. key released with 'shift' modifier
    else
    {
      unregister_code(key.shiftedKeycode);
      register_code(KC_LSHIFT);
    };
    
    // Update the global key information
    _key.keycode                  = 0;
    _key.keycodeNeedsShift        = false;
    _key.shiftedKeycode           = 0;
    _key.shiftedKeycodeNeedsShift = false;
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

