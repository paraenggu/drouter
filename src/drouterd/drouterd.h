// drouterd.h
//
// Dynamic router service for Livewire networks
//
//   (C) Copyright 2017 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef DROUTERD_H
#define DROUTERD_H

#include <QList>
#include <QObject>

#include <sy/synode.h>

#include "drouter.h"
#include "protocol.h"

#define DROUTERD_USAGE "[options]\n"

class MainObject : public QObject
{
 Q_OBJECT;
 public:
  MainObject(QObject *parent=0);

 private slots:
  void signalData();

 private:
  QList<Protocol *> main_protocols;
  DRouter *main_drouter;
  QTimer *main_signal_timer;
};


#endif  // DROUTERD_H
