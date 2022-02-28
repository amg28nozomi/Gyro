/*****************************************************************//**
 * @file   InputBase.cpp
 * @brief  “ü—Íó‘Ô‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author —é–ØŠóŠC
 * @date   December 2021
 *********************************************************************/
#include "InputBase.h"

namespace AppFrame {
  namespace Application {

    InputBase::InputBase() {
      ++_connection;
      _state = State::Active;
    }

    InputBase::~InputBase() {
      --_connection;
    }
  } // Application
} // AppFrame