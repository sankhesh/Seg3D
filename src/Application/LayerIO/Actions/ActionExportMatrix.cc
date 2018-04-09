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

// Boost includes
#include <boost/filesystem.hpp>

#include <sstream>
#include <iomanip>
#include <fstream>

// Application includes
#include <Application/LayerIO/Actions/ActionExportMatrix.h>
#include <Application/LayerIO/LayerIO.h>
#include <Application/Layer/LayerManager.h>
#include <Application/ProjectManager/ProjectManager.h>

// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
CORE_REGISTER_ACTION( Seg3D, ExportMatrix )

namespace Seg3D
{

bool ActionExportMatrix::validate( Core::ActionContextHandle& context )
{
  if ( this->file_path_.empty() )
  {
    context->report_error( std::string("File path is empty.") );
    return false;
  }

  if ( this->matrix_.empty() )
  {
    context->report_error( std::string("No matrix available to save.") );
    return false;
  }
  return true; // validated
}

bool ActionExportMatrix::run( Core::ActionContextHandle& context, Core::ActionResultHandle& result )
{
  std::string message = std::string( "Exporting matrix." );
  
  Core::ActionProgressHandle progress = 
  Core::ActionProgressHandle( new Core::ActionProgress( message ) );
  
  progress->begin_progress_reporting();
  
  boost::filesystem::path filename = boost::filesystem::path( this->file_path_ );

  std::ofstream outputfile;
  outputfile.exceptions( std::ofstream::failbit | std::ofstream::badbit );
  
  try
  {
    outputfile.open( filename.string().c_str() );            
    
    std::ios_base::fmtflags ff;
    ff = outputfile.flags();
    ff |= outputfile.showpoint; // write floating-point values including always the decimal point
    ff |= outputfile.fixed; // write floating point values in fixed-point notation
    outputfile.flags(ff);

	int inx = 0;
	//need input matrix dimensions
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			outputfile << matrix_[inx] << "\t";
			inx++;
		}
		outputfile << std::endl;
	}
  }     
  catch (...)
  {
    context->report_error( "Could not open and write to file: " + filename.string() );
    return false;
  }


  outputfile.close();
  
  progress->end_progress_reporting();
  
  return true;
}

void ActionExportMatrix::Dispatch( Core::ActionContextHandle context,
                                   const std::string& file_path,
                                   const std::vector<double>& matrix )
{
  // Create new action
  ActionExportMatrix* action = new ActionExportMatrix(file_path, matrix);
  Core::ActionDispatcher::PostAction( Core::ActionHandle( action ), context );
}

} // end namespace Seg3D
