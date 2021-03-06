// protocol.h
//
// Abstract base class for drouter client protocols
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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>

#include "drouter.h"

class Protocol : public QObject
{
 Q_OBJECT;
 public:
 enum Type {ProtocolD=0,ProtocolSa=1};
  Protocol(DRouter *router,Type type,QObject *parent=0);
  Type type() const;
  virtual void reload();

 private slots:
  void nodeAddedData(const SyNode &node);
  void nodeAboutToBeRemovedData(const SyNode &node);
  void srcChangedData(const SyNode &node,int slot,const SySource &src);
  void dstChangedData(const SyNode &node,int slot,const SyDestination &dst);
  void gpiChangedData(const SyNode &node,int slot,const SyGpioBundle &gpi);
  void gpoChangedData(const SyNode &node,int slot,const SyGpo &gpo);
  void clipAlarmChangedData(const SyNode &node,int slot,
			    SyLwrpClient::MeterType type,int chan,bool state);
  void silenceAlarmChangedData(const SyNode &node,int slot,
			       SyLwrpClient::MeterType type,int chan,
			       bool state);

 protected:
  virtual void processAddedNode(const SyNode &node);
  virtual void processAboutToBeRemovedNode(const SyNode &node);
  virtual void processChangedSource(const SyNode &node,int slot,
				    const SySource &src);
  virtual void processChangedDestination(const SyNode &node,int slot,
					 const SyDestination &dst);
  virtual void processClipAlarm(const SyNode &node,
				int slot,SyLwrpClient::MeterType type,
				int chan,bool state);
  virtual void processSilenceAlarm(const SyNode &node,
				   int slot,SyLwrpClient::MeterType type,
				   int chan,bool state);
  virtual void processChangedGpi(const SyNode &node,int slot,
				 const SyGpioBundle &gpi);
  virtual void processChangedGpo(const SyNode &node,int slot,const SyGpo &gpo);
  DRouter *router() const;

 private:
  Type protocol_type;
  DRouter *protocol_drouter;
};


#endif  // PROTOCOL_H
