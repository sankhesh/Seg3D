/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2016 Scientific Computing and Imaging Institute,
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

#ifndef APPLICATION_LAYER_ACTIONS_ACTIONDUPLICATELAYER_H
#define APPLICATION_LAYER_ACTIONS_ACTIONDUPLICATELAYER_H

// Core includes
#include <Core/Action/Action.h>

// Application includes
#include <Application/Layer/LayerManager.h>

namespace Seg3D
{

class ActionDeleteSandbox : public Core::Action
{

CORE_ACTION
( 
  CORE_ACTION_TYPE( "DeleteSandbox", "Delete a sandbox." )
  CORE_ACTION_ARGUMENT( "sandbox", "The ID of the sandbox to be deleted." )
)
  
  // -- Constructor/Destructor --
public:
  ActionDeleteSandbox()
  {
    this->add_parameter( this->sandbox_ );
  }

  // -- Functions that describe action --
public:
  virtual bool validate( Core::ActionContextHandle& context ) override;
  virtual bool run( Core::ActionContextHandle& context, 
    Core::ActionResultHandle& result ) override;
  
private:
  // The ID of the sandbox.
  SandboxID sandbox_;

public:
  /// DISPATCH:
  /// Create and dispatch an ActionDeleteSandbox.
  static void Dispatch( Core::ActionContextHandle context, SandboxID sandbox ); 
};
  
} // end namespace Seg3D

#endif
