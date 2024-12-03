#ifndef __INET_XMLUTILS_H
#define __INET_XMLUTILS_H

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddress.h"

const inet::cXMLElement* getUniqueChild(const inet::cXMLElement *node, const char *name);
const inet::cXMLElement* getUniqueChildIfExists(const inet::cXMLElement *node, const char *name);

void checkTags(const inet::cXMLElement *node, const char *allowed);

bool getParameterBoolValue(const inet::cXMLElement *ptr, const char *name, bool def);
bool getParameterBoolValue(const inet::cXMLElement *ptr, const char *name);
int getParameterIntValue(const inet::cXMLElement *ptr, const char *name);
int getParameterIntValue(const inet::cXMLElement *ptr, const char *name, int def);
const char* getParameterStrValue(const inet::cXMLElement *ptr, const char *name);
const char* getParameterStrValue(const inet::cXMLElement *ptr, const char *name, const char *def);
IPAddress getParameterIPAddressValue(const inet::cXMLElement *ptr, const char *name);
IPAddress getParameterIPAddressValue(const inet::cXMLElement *ptr, const char *name, IPAddress def);
double getParameterDoubleValue(const inet::cXMLElement *ptr, const char *name);
double getParameterDoubleValue(const inet::cXMLElement *ptr, const char *name, double def);

bool parseBool(const char *text);

#endif
