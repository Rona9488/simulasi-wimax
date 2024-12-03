
#include "XMLUtils.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddressResolver.h"

const inet::cXMLElement* getUniqueChild(const inet::cXMLElement *node, const char *name)
{
    const inet::cXMLElement *child = getUniqueChildIfExists(node, name);
    if(!child)
        throw inet::cRuntimeError("xml error: exactly one %s element expected", name);

    return child;
}

const inet::cXMLElement* getUniqueChildIfExists(const inet::cXMLElement *node, const char *name)
{
    inet::cXMLElementList list = node->getChildrenByTagName(name);
    if(list.size() > 1)
        throw inet::cRuntimeError("xml error: at most one %s element expected", name);
    else if(list.size() == 1)
        return (*list.begin());
    else
        return NULL;
}

bool parseBool(const char *text)
{
    if(!strcasecmp(text, "down"))
        return false;
    else if(!strcasecmp(text, "off"))
        return false;
    else if(!strcasecmp(text, "false"))
        return false;
    else if(!strcasecmp(text, "no"))
        return false;
    else if(!strcasecmp(text, "0"))
        return false;
    else if(!strcasecmp(text, "up"))
        return true;
    else if(!strcasecmp(text, "on"))
        return true;
    else if(!strcasecmp(text, "true"))
        return true;
    else if(!strcasecmp(text, "yes"))
        return true;
    else if(!strcasecmp(text, "1"))
        return true;
    else
        throw inet::cRuntimeError("unknown bool constant: %s", text);
}

void checkTags(const inet::cXMLElement *node, const char *allowed)
{
    std::vector<const char *> tags;

    inet::cStringTokenizer st(allowed, " ");
    const char *nt;
    while((nt = st.nextToken())!=NULL)
        tags.push_back(nt);

    for(inet::cXMLElement *child=node->getFirstChild(); child; child=child->getNextSibling())
    {
        unsigned int i;
        for(i = 0; i < tags.size(); i++)
            if(!strcmp(child->getTagName(), tags[i]))
                break;
        if(i == tags.size())
            throw inet::cException("subtag <%s> not expected in <%s>", child->getTagName(), node->getTagName());
    }
}

const char* getParameterStrValue(const inet::cXMLElement *ptr, const char *name, const char *def)
{
    const inet::cXMLElement *xvalue = getUniqueChildIfExists(ptr, name);
    if(xvalue)
        return xvalue->getNodeValue();
    else
        return def;
}

bool getParameterBoolValue(const inet::cXMLElement *ptr, const char *name, bool def)
{
    const inet::cXMLElement *xvalue = getUniqueChildIfExists(ptr, name);
    if(xvalue)
        return parseBool(xvalue->getNodeValue());
    else
        return def;
}

bool getParameterBoolValue(const inet::cXMLElement *ptr, const char *name)
{
    const inet::cXMLElement *xvalue = getUniqueChild(ptr, name);
    return parseBool(xvalue->getNodeValue());
}

const char* getParameterStrValue(const inet::cXMLElement *ptr, const char *name)
{
    const inet::cXMLElement *xvalue = getUniqueChild(ptr, name);
    return xvalue->getNodeValue();
}

int getParameterIntValue(const inet::cXMLElement *ptr, const char *name, int def)
{
    const inet::cXMLElement *xvalue = getUniqueChildIfExists(ptr, name);
    if(xvalue)
        return atoi(xvalue->getNodeValue());
    else
        return def;
}

int getParameterIntValue(const inet::cXMLElement *ptr, const char *name)
{
    const inet::cXMLElement *xvalue = getUniqueChild(ptr, name);
    return atoi(xvalue->getNodeValue());
}

IPAddress getParameterIPAddressValue(const inet::cXMLElement *ptr, const char *name, IPAddress def)
{
    const inet::cXMLElement *xvalue = getUniqueChildIfExists(ptr, name);
    if(xvalue)
        return IPAddress(xvalue->getNodeValue());
    else
        return def;
}

IPAddress getParameterIPAddressValue(const inet::cXMLElement *ptr, const char *name)
{
    const inet::cXMLElement *xvalue = getUniqueChild(ptr, name);
    return IPAddressResolver().resolve(xvalue->getNodeValue()).get4();
}

double getParameterDoubleValue(const inet::cXMLElement *ptr, const char *name, double def)
{
    const inet::cXMLElement *xvalue = getUniqueChildIfExists(ptr, name);
    if(xvalue)
        return strtod(xvalue->getNodeValue(), NULL);
    else
        return def;
}

double getParameterDoubleValue(const inet::cXMLElement *ptr, const char *name)
{
    const inet::cXMLElement *xvalue = getUniqueChild(ptr, name);
    return strtod(xvalue->getNodeValue(), NULL);
}
