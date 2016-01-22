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
 
#include <QtGui/QColor>
#include <QtGui/QBrush>

#include <Interface/Application/ControllerLogHistory.h>

namespace Seg3D
{

ControllerLogHistory::ControllerLogHistory( size_t log_history_size, QObject* parent ) :
  QAbstractTableModel( parent ), log_history_size_( log_history_size )
{
}

ControllerLogHistory::~ControllerLogHistory()
{
}

int ControllerLogHistory::rowCount( const QModelIndex& ) const
{
  return ( static_cast< int > ( log_history_.size() ) );
}

int ControllerLogHistory::columnCount( const QModelIndex& ) const
{
  return ( 1 );
}

QVariant ControllerLogHistory::data( const QModelIndex& index, int role ) const
{
  if ( !index.isValid() ) return QVariant();

  if ( role == Qt::TextAlignmentRole )
  {
    return int( Qt::AlignLeft | Qt::AlignVCenter );
  }
  else if ( role == Qt::DisplayRole )
  {
    int sz = static_cast< int > ( log_history_.size() );
    if ( index.row() < sz )
    {
      log_entry_type log_entry = log_history_[ sz - index.row() - 1 ];
      if ( index.column() == 0 )
      {
        return ( QString::fromStdString( log_entry.second ) );
      }
    }
    else
    {
      return QVariant();
    }
  }
  else if ( role == Qt::ForegroundRole )
  {
    int sz = static_cast< int > ( log_history_.size() );
    if ( index.row() < sz )
    {
      log_entry_type log_entry = log_history_[ sz - index.row() - 1 ];
      if ( index.column() == 0 )
      {
        if ( log_entry.first & Core::LogMessageType::ERROR_E ) return QBrush( QColor( 255, 0, 0 ) );
        if ( log_entry.first & Core::LogMessageType::WARNING_E ) return QBrush(
            QColor( 204, 51, 0 ) );
        if ( log_entry.first & Core::LogMessageType::MESSAGE_E ) return QBrush(
            QColor( 0, 0, 76 ) );
        return QBrush( QColor( 76, 0, 0 ) );
      }
    }
    else
    {
      return QVariant();
    }

  }
  else
  {
    return QVariant();
  }

  return QVariant();
}

QVariant ControllerLogHistory::headerData( int section, Qt::Orientation orientation, int role ) const
{
  if ( role != Qt::DisplayRole || orientation == Qt::Vertical )
  {
    return QVariant();
  }

  if ( section == 0 ) return QString( "Log entry" );
  else return QVariant();
}

void ControllerLogHistory::add_log_entry( int message_type, std::string& message )
{
  log_entry_type entry = std::make_pair( message_type, message );

  log_history_.push_front( entry );
  if ( log_history_.size() > log_history_size_ )
  {
    log_history_.pop_back();
  }

  beginResetModel();
  endResetModel();
}

} // end namespace Seg3D
