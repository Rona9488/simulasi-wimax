/*
 * Dibbler - a portable DHCPv6
 *
 * authors: Tomasz Mrugalski <thomson@klub.com.pl>
 *          Marek Senderski <msend@o2.pl>
 * changes: Micha� Kowalczuk <michal@kowalczuk.eu>
 * changes: Micha� Kowalczuk <michal@kowalczuk.eu>
 *
 * $Id: Logger.h,v 1.15 2006-11-30 03:21:51 thomson Exp $
 *
 * Released under GNU GPL v2 licence
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\omnetpp-5.7.1-src-windows\omnetpp-5.7.1\include\omnetpp\cenvir.h"
#include <iostream>
#include <string>

#define Log(X) SLog(this,X)
#define SLog(OBJ, X) logger::log##X(omnetpp::simTime(), OBJ->getFullName(), omnetpp::cSimulation::getActiveSimulation()->getEnvir())

#define LogEnd logger :: endl

#define LOGMODE_DEFAULT LOGMODE_SIMTIME

namespace logger {
  const int Emerg=1;
  const int Alert=2;
  const int Crit=3;
  const int Error=4;
  const int Warning=5;
  const int Notice=6;
  const int Info=7;
  const int Debug=8;
  
  enum Elogmode {
    LOGMODE_FULL,
    LOGMODE_SHORT,
    LOGMODE_SYSLOG,
    LOGMODE_EVENTLOG, /* unix only */
    LOGMODE_PRECISE,
    LOGMODE_SIMTIME
  };
  
  using namespace std;
  ostream& logCont( omnetpp::simtime_t simtime_t, const char * name, omnetpp::cEnvir * evr);//ev--> evr in many places, simtime also now simtime_t type (MiM)
  ostream& logEmerg( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logAlert( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logCrit( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logError( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logWarning( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logNotice( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logInfo( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  ostream& logDebug( omnetpp::simtime_t simtime_t, const char * name,  omnetpp::cEnvir * evr);
  
  void Initialize(const char * file);
  void Terminate();
  void setLogName(string x);
  void setLogLevel(int x);
  void setLogMode(string x);
  void setEv( omnetpp::cEnvir * evr);
  void EchoOff();
  void EchoOn();
  string getLogName();
  int getLogLevel();
  void setSimTime( omnetpp::simtime_t x);
  bool willPrint(int x);
  
  ostream & endl (ostream & strum);
  
}

#endif
