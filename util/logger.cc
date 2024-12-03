#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "logger.h"
#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\omnetpp-5.7.1-src-windows\omnetpp-5.7.1\include\omnetpp\cenvir.h"

namespace logger {
    std::string logname = "Init";
    int logLevel = 8;
    Elogmode logmode = LOGMODE_DEFAULT; // default logmode
    std::ofstream logFile;             // file where wanted msgs are stored
    bool logFileMode = false;
    bool echo = false;                 // print copy of the message to the console
    int curLogEntry = 8;               // 8 - debug

    omnetpp::cEnvir* evr = nullptr;

    std::ostringstream buffer;

    // LogEnd
    std::ostream& endl(std::ostream& strum) {
        if (curLogEntry <= logLevel) {
            // log on the console
            if (echo)
                std::cout << buffer.str() << std::endl;

            // log to the file
            if (logFileMode)
                logFile << buffer.str() << std::endl;

            // log in the OMNeT++ environment
            if (evr) {
                EV << buffer.str();
            }
        }

        buffer.str(std::string());
        buffer.clear();

        return strum;
    }

    std::ostream& logCommon(int x) {
        static char lv[][10] = { "Emergency",
                                 "Alert    ",
                                 "Critical ",
                                 "Error    ",
                                 "Warning  ",
                                 "Notice   ",
                                 "Info     ",
                                 "Debug    " };

        curLogEntry = x;

        time_t teraz = time(NULL);
        struct tm* now = localtime(&teraz);

        switch (logmode) {
            case LOGMODE_FULL:
                buffer << (1900 + now->tm_year) << ".";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_mon + 1 << ".";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_mday << " ";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_hour << ":";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_min << ":";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_sec;
                break;
            case LOGMODE_SHORT:
                buffer.width(2); buffer.fill('0'); buffer << now->tm_min << ":";
                buffer.width(2); buffer.fill('0'); buffer << now->tm_sec;
                break;
            case LOGMODE_PRECISE: {
                int sec, usec;
#ifdef WIN32
                SYSTEMTIME now;
                GetSystemTime(&now);
                sec = now.wMinute * 60 + now.wSecond;
                usec = now.wMilliseconds * 1000;
#else
                struct timeval preciseTime;
                gettimeofday(&preciseTime, NULL);
                sec = preciseTime.tv_sec % 3600;
                usec = preciseTime.tv_usec;
#endif
                buffer.width(4); buffer.fill('0'); buffer << sec << "s,";
                buffer.width(6); buffer.fill('0'); buffer << usec << "us ";
                break;
            }
            case LOGMODE_SIMTIME:
                buffer << "[";
                buffer.width(5);
                buffer << std::setiosflags(std::ios::left);
                buffer << SIMTIME_DBL(omnetpp::simTime());
                buffer << "]" << std::resetiosflags(std::ios::left);
                break;
            case LOGMODE_SYSLOG:
            case LOGMODE_EVENTLOG:
                buffer << "SYSLOG/EventLog logging mode not supported yet.";
                break;
        }
        buffer << ' ';
        buffer.width(14);
        buffer << logname;
        buffer << ' ' << lv[x - 1] << " ";
        return buffer;
    }

    std::ostream& logCont(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        return buffer;
    }

    std::ostream& logEmerg(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(1);
    }
    std::ostream& logAlert(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(2);
    }
    std::ostream& logCrit(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(3);
    }
    std::ostream& logError(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(4);
    }
    std::ostream& logWarning(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(5);
    }
    std::ostream& logNotice(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(6);
    }
    std::ostream& logInfo(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(7);
    }
    std::ostream& logDebug(omnetpp::simtime_t simtime, const char* name, omnetpp::cEnvir* evr) {
        setSimTime(simtime); setLogName(name); setEv(evr); return logCommon(8);
    }

    void Initialize(const char* file) {
        logFileMode = true;
        logFile.open(file, std::ofstream::out | std::ofstream::app);
    }

    void Terminate() {
        logFileMode = false;
        logFile.close();
    }

    void EchoOn() {
        echo = true;
    }

    void EchoOff() {
        echo = false;
    }

    void setLogLevel(int x) {
        if (x > 8 || x < 1)
            return;
        logLevel = x;
    }

    void setLogName(std::string x) {
        logname = x;
    }

    std::string getLogName() {
        return logname;
    }

    int getLogLevel() {
        return logLevel;
    }

    void setSimTime(omnetpp::simtime_t x) {
        omnetpp::simTime() = SIMTIME_DBL(x); // Correct assignment
    }

    void setEv(omnetpp::cEnvir* x) {
        evr = x;
    }

    bool willPrint(int x) {
        return curLogEntry <= logLevel;
    }

    void setLogMode(std::string x) {
        if (x == "short") {
            logmode = LOGMODE_SHORT;
        } else if (x == "full") {
            logmode = LOGMODE_FULL;
        } else if (x == "precise") {
            logmode = LOGMODE_PRECISE;
        }
#ifdef WIN32
        else if (x == "eventlog") {
            logmode = LOGMODE_EVENTLOG;
        }
#endif
    }
}
