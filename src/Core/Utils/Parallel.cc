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

#include <vector>

#include <Core/Utils/Parallel.h>

namespace Core
{

class ParallelPrivate
{
public:
  int num_threads_;
  boost::function< void ( int, int ) > function_;
};

Parallel::Parallel( boost::function< void ( int, int ) > function, int num_threads ) :
  private_( new ParallelPrivate )
{
  if ( num_threads == -1 )
  {
    this->private_->num_threads_ =  boost::thread::hardware_concurrency();
  }
  else
  {
    this->private_->num_threads_ = num_threads;
  }
  
  if ( this->private_->num_threads_ < 1 ) 
  {
    this->private_->num_threads_ = 1;
  }
}

void Parallel::run()
{
  std::vector< boost::thread* > threads( this->private_->num_threads_ );

  for ( int i = 0; i < this->private_->num_threads_; i++ )
  {
    threads[ i ] = new boost::thread( boost::bind( this->private_->function_, i, 
      this->private_->num_threads_ ) );
  }

  for ( int i = 0; i < this->private_->num_threads_; i++ )
  {
    threads[ i ]->join();
    delete threads[ i ];
  }
}

} // end namespace Core