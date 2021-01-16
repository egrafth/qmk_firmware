// special.h
#pragma once

// Include headers
#include "quantum.h"



// ------------------------------------------------------------------
//
//                               Structs
//
// ------------------------------------------------------------------

// -----------
// Struct: Key
// -----------
/** 
This struct can be used to define the behavior of a specific key when it is pressed - with and without
shift. The definition of key requires for components:
- The keycode when the key is pressed without 'shift' and ..
- .. if this keycode requires the 'shift' modifier
- The key codecode when the key is pressed with 'shift' and ..
- .. if this keycode requires the 'shift' modifier

This method allows to overwrite more or less any key using any os language.

Note: This works only properly when the special 'shift' key is used (SP_SHIFT) instead of CU_LSFT and CU_RSFT.

Examples:

1) Backspace / Del
If one needs a key that generates a 'backspace' when pressed without 'shift' and 'delete'
when pressed with 'shift' then definition looks like:

const Key specialBSPC = {KC_BSPC, false, KC_DEL, false};

2) M / p
This is maybe stupid but is explains the possibility of this struct. The key should generate a 'M' when
pressed without 'shift' and 'p' when pressed with 'shift'. The definition looks like:

const Key specialStupid = {KC_M, true, KC_P, false};
*/
typedef struct
{
  uint16_t  keycode;                     ///< Keycode when key is pressed without shift
  bool      keycodeNeedsShift;           ///< Does keycode needs shit modifier when key is pressed without shift
  uint16_t  shiftedKeycode;              ///< Keycode when key is pressed with shift
  bool      shiftedKeycodeNeedsShift;    ///< Does keycode needs shit modifier when key is pressed without shift
} Key;





// ------------------------------------------------------------------
//
//                             Functions
//
// ------------------------------------------------------------------

// -------
// pressed
// -------
/**
Simply use this method when a key defined by the struct 'Key' is pressed or released.
*/
void pressed
(
  Key           key,
  keyrecord_t*  record
);

// ------------
// pressedShift
// ------------
/**
Simply use this method when the special 'shift' key is pressed or released.
*/
void pressedShift
(
  keyrecord_t*  record
);





// ------------------------------------------------------------------
//
//                           Definitions
//
// ------------------------------------------------------------------
/**
This key is used internally by handling the key commands as well as the special shift method.
Do not use it unless you know what you are doing!!!
*/
extern Key _key;

/**
This variable is used internally in order to handle the special 'shift' key properly.
Do not use it unless you know what you are doing!!!
*/
extern bool _shift;

/**
This variable is used internally in order to handle the special 'shift' key properly.
Do not use it unless you know what you are doing!!!
*/
extern bool _shiftEvent;
