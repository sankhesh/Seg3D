/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
   University of Utah.

   
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifndef APPLICATION_INTERFACE_INTERFACE_H
#define APPLICATION_INTERFACE_INTERFACE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

// Core includes
#include <Utils/Core/Log.h>
#include <Utils/Singleton/Singleton.h>
#include <Utils/EventHandler/EventHandler.h>

#include <Application/Action/ActionContext.h>
#include <Application/Action/ActionDispatcher.h>

namespace Seg3D {
 
// CLASS INTERFACE: 
// Interface is the abstraction of the interface layer
// It manages the events and thread of the user interface.

class Interface; 
 
class Interface : public Utils::EventHandler {

// -- Constructor/Destructor --
  public:
    Interface();

// -- ActionContext --

    // CREATE_ACTION_CONTEXT:
    // Create a new action context
    ActionContextHandle create_action_context();

// -- Interface thread --    
    
    // IS_INTERFACE_THREAD:
    // Test whether the current thread is the interface thread

    static bool is_interface_thread()
      { return (instance()->is_eventhandler_thread()); }

// -- Singleton interface --
  public:
    
    // INSTANCE:
    // Get the singleton interface
    static Interface* instance() { instance_.instance(); }

  private:  
    static Utils::Singleton<Interface> instance_;
    
};

// RUNACTIONFROMINTERFACE:
// Function that runs an action with the interface context

void RunActionFromInterface(ActionHandle action)
{
  ActionDispatcher::instance()->run_action(action,
                              Interface::instance()->create_action_context());
}

} // end namespace Seg3D

#endif