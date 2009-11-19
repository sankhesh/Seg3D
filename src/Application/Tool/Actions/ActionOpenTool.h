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

#ifndef APPLICATION_TOOL_ACTIONS_ACTIONOPENTOOL_H
#define APPLICATION_TOOL_ACTIONS_ACTIONOPENTOOL_H

#include <Application/Action/Action.h>
#include <Application/Action/ActionFactory.h>

namespace Seg3D {

class ActionOpenTool : public Action {

// -- Constructor/Destructor --
  public:
    ActionOpenTool() :
      Action("OpenTool",Action::APPLICATION_E)
    {
      add_argument(tool_);
      add_parameter("id",toolid_);
    }
    
    virtual ~ActionOpenTool() 
    {}

    void set(const std::string& tool,const std::string& toolid)
    {
      tool_.value() = tool;
      toolid_.value() = toolid;
    }

// -- Functions that describe action --
    virtual bool validate(ActionContextHandle& context);
    virtual bool run(ActionContextHandle& context) const;
    
// -- Action parameters --
  protected:
    ActionParameter<std::string> tool_;
    ActionParameter<std::string> toolid_;
};

typedef boost::shared_ptr<ActionOpenTool> ActionOpenToolHandle;

}

#endif