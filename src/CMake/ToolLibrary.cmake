#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2009 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

SET(TOOL_LIBRARY_LIST "" CACHE INTERNAL "list of libraries" FORCE)
SET(TOOL_LIST "" CACHE INTERNAL "list of tools" FORCE)

SET(TOOLINTERFACE_LIBRARY_LIST "" CACHE INTERNAL "list of libraries" FORCE)
SET(TOOLINTERFACE_LIST "" CACHE INTERNAL "list of tool interfaces" FORCE)


MACRO(ADD_LIBRARY_TOOLS library)
  SET(TOOL_LIBRARY_LIST_TEMP ${TOOL_LIBRARY_LIST} ${library})
  SET(TOOL_LIBRARY_LIST ${TOOL_LIBRARY_LIST_TEMP} CACHE INTERNAL "list of libraries")

  SET(TOOL_LIST_TEMP ${TOOL_LIST} ${ARGN})
  SET(TOOL_LIST ${TOOL_LIST_TEMP} CACHE INTERNAL "list of tools")
ENDMACRO(ADD_LIBRARY_TOOLS)


MACRO(ADD_LIBRARY_TOOLINTERFACES library)
  SET(TOOLINTERFACE_LIBRARY_LIST_TEMP ${TOOLINTERFACE_LIBRARY_LIST} ${library})
  SET(TOOLINTERFACE_LIBRARY_LIST ${TOOLINTERFACE_LIBRARY_LIST_TEMP} CACHE INTERNAL "list of libraries")

  SET(TOOLINTERFACE_LIST_TEMP ${TOOLINTERFACE_LIST} ${ARGN})
  SET(TOOLINTERFACE_LIST ${TOOLINTERFACE_LIST_TEMP} CACHE INTERNAL "list of tool interfaces")
ENDMACRO(ADD_LIBRARY_TOOLINTERFACES)


MACRO(BUILD_REGISTER_TOOLS_LIBRARY)

  SET(TOOLLIST "")
  FOREACH(TOOL ${TOOL_LIST})
    STRING(REPLACE ".cc" "" TOOLTEMP ${TOOL})
    STRING(REPLACE ".h" "" TOOLFILE ${TOOLTEMP})
    SET(TOOLLIST ${TOOLLIST} ${TOOLFILE})
  ENDFOREACH(TOOL ${TOOL_LIST})
  LIST(REMOVE_DUPLICATES TOOLLIST)

  SET(TOOLINTERFACELIST "")
  FOREACH(TOOLINTERFACE ${TOOLINTERFACE_LIST})
    STRING(REPLACE ".cc" "" TOOLINTERFACETEMP ${TOOLINTERFACE})
    STRING(REPLACE ".h" "" TOOLINTERFACEFILE ${TOOLINTERFACETEMP})
    SET(TOOLINTERFACELIST ${TOOLINTERFACELIST} ${TOOLINTERFACEFILE})
  ENDFOREACH(TOOLINTERFACE ${TOOLINTERFACE_LIST})
  LIST(REMOVE_DUPLICATES TOOLINTERFACELIST)

  SET(DECLARATIONS "")
  SET(IMPLEMENTATIONS "")

  FOREACH(TOOL ${TOOLLIST})
    STRING(CONFIGURE "extern void register_tool_@TOOL();\n" DECLARATION)
    SET(DECLARATIONS "${DECLARATIONS} ${DECLARATION}")

    STRING(CONFIGURE "  register_tool_@TOOL@();\n" IMPLEMENTATION)
    SET(IMPLEMENTATIONS "${IMPLEMENTATIONS} ${IMPLEMENTATION}")
  ENDFOREACH(TOOL ${TOOLLIST})
  
  FOREACH(TOOLINTERFACE ${TOOLINTERFACELIST})
    STRING(CONFIGURE "extern void register_toolinterface_@TOOLINTERFACE();\n" DECLARATION)
    SET(DECLARATIONS "${DECLARATIONS} ${DECLARATION}")

    STRING(CONFIGURE "  register_toolinterface_@TOOLINTERFACE@();\n" IMPLEMENTATION)
    SET(IMPLEMENTATIONS "${IMPLEMENTATIONS} ${IMPLEMENTATION}")
  ENDFOREACH(TOOLINTERFACE ${TOOLINTERFACELIST})
  
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Configuration/ToolLibraryInit.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/Init/ToolLibraryInit.h
                 @ONLY)
                 
ENDMACRO(BUILD_REGISTER_TOOLS_LIBRARY)