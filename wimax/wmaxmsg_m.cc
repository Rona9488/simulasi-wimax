//
// Generated file, do not edit! Created by nedtool 5.7 from wimax/wmaxmsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "wmaxmsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

WMaxMacHeaderMsg_Base::WMaxMacHeaderMsg_Base() : ::omnetpp::cObject()
{
}

WMaxMacHeaderMsg_Base::WMaxMacHeaderMsg_Base(const WMaxMacHeaderMsg_Base& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

WMaxMacHeaderMsg_Base::~WMaxMacHeaderMsg_Base()
{
}

WMaxMacHeaderMsg_Base& WMaxMacHeaderMsg_Base::operator=(const WMaxMacHeaderMsg_Base& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void WMaxMacHeaderMsg_Base::copy(const WMaxMacHeaderMsg_Base& other)
{
}

void WMaxMacHeaderMsg_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    // field cid is abstract -- please do packing in customized class
    // field ht is abstract -- please do packing in customized class
    // field bwr is abstract -- please do packing in customized class
}

void WMaxMacHeaderMsg_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    // field cid is abstract -- please do unpacking in customized class
    // field ht is abstract -- please do unpacking in customized class
    // field bwr is abstract -- please do unpacking in customized class
}

class WMaxMacHeaderMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMacHeaderMsgDescriptor();
    virtual ~WMaxMacHeaderMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMacHeaderMsgDescriptor)

WMaxMacHeaderMsgDescriptor::WMaxMacHeaderMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMacHeaderMsg", "omnetpp::cObject")
{
    propertynames = nullptr;
}

WMaxMacHeaderMsgDescriptor::~WMaxMacHeaderMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMacHeaderMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMacHeaderMsg_Base *>(obj)!=nullptr;
}

const char **WMaxMacHeaderMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMacHeaderMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMacHeaderMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WMaxMacHeaderMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMacHeaderMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cid",
        "ht",
        "bwr",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int WMaxMacHeaderMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cid")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "ht")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "bwr")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMacHeaderMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "bool",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMacHeaderMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMacHeaderMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMacHeaderMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMacHeaderMsg_Base *pp = (WMaxMacHeaderMsg_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMacHeaderMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacHeaderMsg_Base *pp = (WMaxMacHeaderMsg_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMacHeaderMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacHeaderMsg_Base *pp = (WMaxMacHeaderMsg_Base *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCid());
        case 1: return bool2string(pp->getHt());
        case 2: return long2string(pp->getBwr());
        default: return "";
    }
}

bool WMaxMacHeaderMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMacHeaderMsg_Base *pp = (WMaxMacHeaderMsg_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setCid(string2long(value)); return true;
        case 1: pp->setHt(string2bool(value)); return true;
        case 2: pp->setBwr(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMacHeaderMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMacHeaderMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacHeaderMsg_Base *pp = (WMaxMacHeaderMsg_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDlMapMsg)

WMaxMsgDlMapMsg::WMaxMsgDlMapMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    IE_arraysize = 0;
    this->IE = 0;
}

WMaxMsgDlMapMsg::WMaxMsgDlMapMsg(const WMaxMsgDlMapMsg& other) : ::omnetpp::cPacket(other)
{
    IE_arraysize = 0;
    this->IE = 0;
    copy(other);
}

WMaxMsgDlMapMsg::~WMaxMsgDlMapMsg()
{
    delete [] this->IE;
}

WMaxMsgDlMapMsg& WMaxMsgDlMapMsg::operator=(const WMaxMsgDlMapMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDlMapMsg::copy(const WMaxMsgDlMapMsg& other)
{
    delete [] this->IE;
    this->IE = (other.IE_arraysize==0) ? nullptr : new WMaxDlMapIE[other.IE_arraysize];
    IE_arraysize = other.IE_arraysize;
    for (unsigned int i=0; i<IE_arraysize; i++)
        this->IE[i] = other.IE[i];
}

void WMaxMsgDlMapMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    b->pack(IE_arraysize);
    doParsimArrayPacking(b,this->IE,IE_arraysize);
}

void WMaxMsgDlMapMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    delete [] this->IE;
    b->unpack(IE_arraysize);
    if (IE_arraysize==0) {
        this->IE = 0;
    } else {
        this->IE = new WMaxDlMapIE[IE_arraysize];
        doParsimArrayUnpacking(b,this->IE,IE_arraysize);
    }
}

void WMaxMsgDlMapMsg::setIEArraySize(unsigned int size)
{
    WMaxDlMapIE *IE2 = (size==0) ? nullptr : new WMaxDlMapIE[size];
    unsigned int sz = IE_arraysize < size ? IE_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        IE2[i] = this->IE[i];
    IE_arraysize = size;
    delete [] this->IE;
    this->IE = IE2;
}

unsigned int WMaxMsgDlMapMsg::getIEArraySize() const
{
    return IE_arraysize;
}

WMaxDlMapIE& WMaxMsgDlMapMsg::getIE(unsigned int k)
{
    if (k>=IE_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", IE_arraysize, k);
    return this->IE[k];
}

void WMaxMsgDlMapMsg::setIE(unsigned int k, const WMaxDlMapIE& IE)
{
    if (k>=IE_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", IE_arraysize, k);
    this->IE[k] = IE;
}

class WMaxMsgDlMapMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDlMapMsgDescriptor();
    virtual ~WMaxMsgDlMapMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDlMapMsgDescriptor)

WMaxMsgDlMapMsgDescriptor::WMaxMsgDlMapMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDlMapMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDlMapMsgDescriptor::~WMaxMsgDlMapMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDlMapMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDlMapMsg *>(obj)!=nullptr;
}

const char **WMaxMsgDlMapMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDlMapMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDlMapMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgDlMapMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDlMapMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "IE",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgDlMapMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "IE")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDlMapMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WMaxDlMapIE",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDlMapMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDlMapMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDlMapMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDlMapMsg *pp = (WMaxMsgDlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIEArraySize();
        default: return 0;
    }
}

const char *WMaxMsgDlMapMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDlMapMsg *pp = (WMaxMsgDlMapMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDlMapMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDlMapMsg *pp = (WMaxMsgDlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getIE(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgDlMapMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDlMapMsg *pp = (WMaxMsgDlMapMsg *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgDlMapMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WMaxDlMapIE));
        default: return nullptr;
    };
}

void *WMaxMsgDlMapMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDlMapMsg *pp = (WMaxMsgDlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getIE(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgUlMapMsg)

WMaxMsgUlMapMsg::WMaxMsgUlMapMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    IE_arraysize = 0;
    this->IE = 0;
}

WMaxMsgUlMapMsg::WMaxMsgUlMapMsg(const WMaxMsgUlMapMsg& other) : ::omnetpp::cPacket(other)
{
    IE_arraysize = 0;
    this->IE = 0;
    copy(other);
}

WMaxMsgUlMapMsg::~WMaxMsgUlMapMsg()
{
    delete [] this->IE;
}

WMaxMsgUlMapMsg& WMaxMsgUlMapMsg::operator=(const WMaxMsgUlMapMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgUlMapMsg::copy(const WMaxMsgUlMapMsg& other)
{
    delete [] this->IE;
    this->IE = (other.IE_arraysize==0) ? nullptr : new WMaxUlMapIE[other.IE_arraysize];
    IE_arraysize = other.IE_arraysize;
    for (unsigned int i=0; i<IE_arraysize; i++)
        this->IE[i] = other.IE[i];
}

void WMaxMsgUlMapMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    b->pack(IE_arraysize);
    doParsimArrayPacking(b,this->IE,IE_arraysize);
}

void WMaxMsgUlMapMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    delete [] this->IE;
    b->unpack(IE_arraysize);
    if (IE_arraysize==0) {
        this->IE = 0;
    } else {
        this->IE = new WMaxUlMapIE[IE_arraysize];
        doParsimArrayUnpacking(b,this->IE,IE_arraysize);
    }
}

void WMaxMsgUlMapMsg::setIEArraySize(unsigned int size)
{
    WMaxUlMapIE *IE2 = (size==0) ? nullptr : new WMaxUlMapIE[size];
    unsigned int sz = IE_arraysize < size ? IE_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        IE2[i] = this->IE[i];
    IE_arraysize = size;
    delete [] this->IE;
    this->IE = IE2;
}

unsigned int WMaxMsgUlMapMsg::getIEArraySize() const
{
    return IE_arraysize;
}

WMaxUlMapIE& WMaxMsgUlMapMsg::getIE(unsigned int k)
{
    if (k>=IE_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", IE_arraysize, k);
    return this->IE[k];
}

void WMaxMsgUlMapMsg::setIE(unsigned int k, const WMaxUlMapIE& IE)
{
    if (k>=IE_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", IE_arraysize, k);
    this->IE[k] = IE;
}

class WMaxMsgUlMapMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgUlMapMsgDescriptor();
    virtual ~WMaxMsgUlMapMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgUlMapMsgDescriptor)

WMaxMsgUlMapMsgDescriptor::WMaxMsgUlMapMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgUlMapMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgUlMapMsgDescriptor::~WMaxMsgUlMapMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgUlMapMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgUlMapMsg *>(obj)!=nullptr;
}

const char **WMaxMsgUlMapMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgUlMapMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgUlMapMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgUlMapMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgUlMapMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "IE",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgUlMapMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "IE")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgUlMapMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WMaxUlMapIE",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgUlMapMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgUlMapMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgUlMapMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUlMapMsg *pp = (WMaxMsgUlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIEArraySize();
        default: return 0;
    }
}

const char *WMaxMsgUlMapMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUlMapMsg *pp = (WMaxMsgUlMapMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgUlMapMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUlMapMsg *pp = (WMaxMsgUlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getIE(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgUlMapMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUlMapMsg *pp = (WMaxMsgUlMapMsg *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgUlMapMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WMaxUlMapIE));
        default: return nullptr;
    };
}

void *WMaxMsgUlMapMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUlMapMsg *pp = (WMaxMsgUlMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getIE(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDCD)

WMaxMsgDCD::WMaxMsgDCD(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->confChangeCount = 0;
}

WMaxMsgDCD::WMaxMsgDCD(const WMaxMsgDCD& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgDCD::~WMaxMsgDCD()
{
}

WMaxMsgDCD& WMaxMsgDCD::operator=(const WMaxMsgDCD& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDCD::copy(const WMaxMsgDCD& other)
{
    this->confChangeCount = other.confChangeCount;
}

void WMaxMsgDCD::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->confChangeCount);
}

void WMaxMsgDCD::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->confChangeCount);
}

int WMaxMsgDCD::getConfChangeCount() const
{
    return this->confChangeCount;
}

void WMaxMsgDCD::setConfChangeCount(int confChangeCount)
{
    this->confChangeCount = confChangeCount;
}

class WMaxMsgDCDDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDCDDescriptor();
    virtual ~WMaxMsgDCDDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDCDDescriptor)

WMaxMsgDCDDescriptor::WMaxMsgDCDDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDCD", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDCDDescriptor::~WMaxMsgDCDDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDCDDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDCD *>(obj)!=nullptr;
}

const char **WMaxMsgDCDDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDCDDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDCDDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgDCDDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDCDDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "confChangeCount",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgDCDDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "confChangeCount")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDCDDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDCDDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDCDDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDCDDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDCD *pp = (WMaxMsgDCD *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgDCDDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDCD *pp = (WMaxMsgDCD *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDCDDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDCD *pp = (WMaxMsgDCD *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getConfChangeCount());
        default: return "";
    }
}

bool WMaxMsgDCDDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDCD *pp = (WMaxMsgDCD *)object; (void)pp;
    switch (field) {
        case 0: pp->setConfChangeCount(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgDCDDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgDCDDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDCD *pp = (WMaxMsgDCD *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgUCDMsg)

WMaxMsgUCDMsg::WMaxMsgUCDMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->confChangeCount = 0;
}

WMaxMsgUCDMsg::WMaxMsgUCDMsg(const WMaxMsgUCDMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgUCDMsg::~WMaxMsgUCDMsg()
{
}

WMaxMsgUCDMsg& WMaxMsgUCDMsg::operator=(const WMaxMsgUCDMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgUCDMsg::copy(const WMaxMsgUCDMsg& other)
{
    this->confChangeCount = other.confChangeCount;
}

void WMaxMsgUCDMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->confChangeCount);
}

void WMaxMsgUCDMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->confChangeCount);
}

int WMaxMsgUCDMsg::getConfChangeCount() const
{
    return this->confChangeCount;
}

void WMaxMsgUCDMsg::setConfChangeCount(int confChangeCount)
{
    this->confChangeCount = confChangeCount;
}

class WMaxMsgUCDMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgUCDMsgDescriptor();
    virtual ~WMaxMsgUCDMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgUCDMsgDescriptor)

WMaxMsgUCDMsgDescriptor::WMaxMsgUCDMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgUCDMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgUCDMsgDescriptor::~WMaxMsgUCDMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgUCDMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgUCDMsg *>(obj)!=nullptr;
}

const char **WMaxMsgUCDMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgUCDMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgUCDMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgUCDMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgUCDMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "confChangeCount",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgUCDMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "confChangeCount")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgUCDMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgUCDMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgUCDMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgUCDMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUCDMsg *pp = (WMaxMsgUCDMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgUCDMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUCDMsg *pp = (WMaxMsgUCDMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgUCDMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUCDMsg *pp = (WMaxMsgUCDMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getConfChangeCount());
        default: return "";
    }
}

bool WMaxMsgUCDMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUCDMsg *pp = (WMaxMsgUCDMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setConfChangeCount(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgUCDMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgUCDMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgUCDMsg *pp = (WMaxMsgUCDMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgRngReqMsg)

WMaxMsgRngReqMsg::WMaxMsgRngReqMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->purpose = 0;
    SfQos_arraysize = 0;
    this->SfQos = 0;
    SfCid_arraysize = 0;
    this->SfCid = 0;
}

WMaxMsgRngReqMsg::WMaxMsgRngReqMsg(const WMaxMsgRngReqMsg& other) : ::omnetpp::cPacket(other)
{
    SfQos_arraysize = 0;
    this->SfQos = 0;
    SfCid_arraysize = 0;
    this->SfCid = 0;
    copy(other);
}

WMaxMsgRngReqMsg::~WMaxMsgRngReqMsg()
{
    delete [] this->SfQos;
    delete [] this->SfCid;
}

WMaxMsgRngReqMsg& WMaxMsgRngReqMsg::operator=(const WMaxMsgRngReqMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgRngReqMsg::copy(const WMaxMsgRngReqMsg& other)
{
    this->purpose = other.purpose;
    this->rngReq = other.rngReq;
    this->myIP = other.myIP;
    delete [] this->SfQos;
    this->SfQos = (other.SfQos_arraysize==0) ? nullptr : new WMaxQos[other.SfQos_arraysize];
    SfQos_arraysize = other.SfQos_arraysize;
    for (unsigned int i=0; i<SfQos_arraysize; i++)
        this->SfQos[i] = other.SfQos[i];
    delete [] this->SfCid;
    this->SfCid = (other.SfCid_arraysize==0) ? nullptr : new int[other.SfCid_arraysize];
    SfCid_arraysize = other.SfCid_arraysize;
    for (unsigned int i=0; i<SfCid_arraysize; i++)
        this->SfCid[i] = other.SfCid[i];
}

void WMaxMsgRngReqMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->purpose);
    doParsimPacking(b,this->rngReq);
    doParsimPacking(b,this->myIP);
    b->pack(SfQos_arraysize);
    doParsimArrayPacking(b,this->SfQos,SfQos_arraysize);
    b->pack(SfCid_arraysize);
    doParsimArrayPacking(b,this->SfCid,SfCid_arraysize);
}

void WMaxMsgRngReqMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->purpose);
    doParsimUnpacking(b,this->rngReq);
    doParsimUnpacking(b,this->myIP);
    delete [] this->SfQos;
    b->unpack(SfQos_arraysize);
    if (SfQos_arraysize==0) {
        this->SfQos = 0;
    } else {
        this->SfQos = new WMaxQos[SfQos_arraysize];
        doParsimArrayUnpacking(b,this->SfQos,SfQos_arraysize);
    }
    delete [] this->SfCid;
    b->unpack(SfCid_arraysize);
    if (SfCid_arraysize==0) {
        this->SfCid = 0;
    } else {
        this->SfCid = new int[SfCid_arraysize];
        doParsimArrayUnpacking(b,this->SfCid,SfCid_arraysize);
    }
}

int WMaxMsgRngReqMsg::getPurpose() const
{
    return this->purpose;
}

void WMaxMsgRngReqMsg::setPurpose(int purpose)
{
    this->purpose = purpose;
}

WMaxRngReq& WMaxMsgRngReqMsg::getRngReq()
{
    return this->rngReq;
}

void WMaxMsgRngReqMsg::setRngReq(const WMaxRngReq& rngReq)
{
    this->rngReq = rngReq;
}

IPv6Address& WMaxMsgRngReqMsg::getMyIP()
{
    return this->myIP;
}

void WMaxMsgRngReqMsg::setMyIP(const IPv6Address& myIP)
{
    this->myIP = myIP;
}

void WMaxMsgRngReqMsg::setSfQosArraySize(unsigned int size)
{
    WMaxQos *SfQos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = SfQos_arraysize < size ? SfQos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        SfQos2[i] = this->SfQos[i];
    SfQos_arraysize = size;
    delete [] this->SfQos;
    this->SfQos = SfQos2;
}

unsigned int WMaxMsgRngReqMsg::getSfQosArraySize() const
{
    return SfQos_arraysize;
}

WMaxQos& WMaxMsgRngReqMsg::getSfQos(unsigned int k)
{
    if (k>=SfQos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", SfQos_arraysize, k);
    return this->SfQos[k];
}

void WMaxMsgRngReqMsg::setSfQos(unsigned int k, const WMaxQos& SfQos)
{
    if (k>=SfQos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", SfQos_arraysize, k);
    this->SfQos[k] = SfQos;
}

void WMaxMsgRngReqMsg::setSfCidArraySize(unsigned int size)
{
    int *SfCid2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = SfCid_arraysize < size ? SfCid_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        SfCid2[i] = this->SfCid[i];
    for (unsigned int i=sz; i<size; i++)
        SfCid2[i] = 0;
    SfCid_arraysize = size;
    delete [] this->SfCid;
    this->SfCid = SfCid2;
}

unsigned int WMaxMsgRngReqMsg::getSfCidArraySize() const
{
    return SfCid_arraysize;
}

int WMaxMsgRngReqMsg::getSfCid(unsigned int k) const
{
    if (k>=SfCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", SfCid_arraysize, k);
    return this->SfCid[k];
}

void WMaxMsgRngReqMsg::setSfCid(unsigned int k, int SfCid)
{
    if (k>=SfCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", SfCid_arraysize, k);
    this->SfCid[k] = SfCid;
}

class WMaxMsgRngReqMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgRngReqMsgDescriptor();
    virtual ~WMaxMsgRngReqMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgRngReqMsgDescriptor)

WMaxMsgRngReqMsgDescriptor::WMaxMsgRngReqMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgRngReqMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgRngReqMsgDescriptor::~WMaxMsgRngReqMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgRngReqMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgRngReqMsg *>(obj)!=nullptr;
}

const char **WMaxMsgRngReqMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgRngReqMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgRngReqMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int WMaxMsgRngReqMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgRngReqMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "purpose",
        "rngReq",
        "myIP",
        "SfQos",
        "SfCid",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int WMaxMsgRngReqMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "purpose")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "rngReq")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "myIP")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "SfQos")==0) return base+3;
    if (fieldName[0]=='S' && strcmp(fieldName, "SfCid")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgRngReqMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "WMaxRngReq",
        "IPv6Address",
        "WMaxQos",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgRngReqMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgRngReqMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgRngReqMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngReqMsg *pp = (WMaxMsgRngReqMsg *)object; (void)pp;
    switch (field) {
        case 3: return pp->getSfQosArraySize();
        case 4: return pp->getSfCidArraySize();
        default: return 0;
    }
}

const char *WMaxMsgRngReqMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngReqMsg *pp = (WMaxMsgRngReqMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgRngReqMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngReqMsg *pp = (WMaxMsgRngReqMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPurpose());
        case 1: {std::stringstream out; out << pp->getRngReq(); return out.str();}
        case 2: {std::stringstream out; out << pp->getMyIP(); return out.str();}
        case 3: {std::stringstream out; out << pp->getSfQos(i); return out.str();}
        case 4: return long2string(pp->getSfCid(i));
        default: return "";
    }
}

bool WMaxMsgRngReqMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngReqMsg *pp = (WMaxMsgRngReqMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPurpose(string2long(value)); return true;
        case 4: pp->setSfCid(i,string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgRngReqMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(WMaxRngReq));
        case 2: return omnetpp::opp_typename(typeid(IPv6Address));
        case 3: return omnetpp::opp_typename(typeid(WMaxQos));
        default: return nullptr;
    };
}

void *WMaxMsgRngReqMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngReqMsg *pp = (WMaxMsgRngReqMsg *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getRngReq()); break;
        case 2: return (void *)(&pp->getMyIP()); break;
        case 3: return (void *)(&pp->getSfQos(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgRngRspMsg)

WMaxMsgRngRspMsg::WMaxMsgRngRspMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->purpose = 0;
    oldCid_arraysize = 0;
    this->oldCid = 0;
    newCid_arraysize = 0;
    this->newCid = 0;
}

WMaxMsgRngRspMsg::WMaxMsgRngRspMsg(const WMaxMsgRngRspMsg& other) : ::omnetpp::cPacket(other)
{
    oldCid_arraysize = 0;
    this->oldCid = 0;
    newCid_arraysize = 0;
    this->newCid = 0;
    copy(other);
}

WMaxMsgRngRspMsg::~WMaxMsgRngRspMsg()
{
    delete [] this->oldCid;
    delete [] this->newCid;
}

WMaxMsgRngRspMsg& WMaxMsgRngRspMsg::operator=(const WMaxMsgRngRspMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgRngRspMsg::copy(const WMaxMsgRngRspMsg& other)
{
    this->purpose = other.purpose;
    this->rngRsp = other.rngRsp;
    delete [] this->oldCid;
    this->oldCid = (other.oldCid_arraysize==0) ? nullptr : new int[other.oldCid_arraysize];
    oldCid_arraysize = other.oldCid_arraysize;
    for (unsigned int i=0; i<oldCid_arraysize; i++)
        this->oldCid[i] = other.oldCid[i];
    delete [] this->newCid;
    this->newCid = (other.newCid_arraysize==0) ? nullptr : new int[other.newCid_arraysize];
    newCid_arraysize = other.newCid_arraysize;
    for (unsigned int i=0; i<newCid_arraysize; i++)
        this->newCid[i] = other.newCid[i];
}

void WMaxMsgRngRspMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->purpose);
    doParsimPacking(b,this->rngRsp);
    b->pack(oldCid_arraysize);
    doParsimArrayPacking(b,this->oldCid,oldCid_arraysize);
    b->pack(newCid_arraysize);
    doParsimArrayPacking(b,this->newCid,newCid_arraysize);
}

void WMaxMsgRngRspMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->purpose);
    doParsimUnpacking(b,this->rngRsp);
    delete [] this->oldCid;
    b->unpack(oldCid_arraysize);
    if (oldCid_arraysize==0) {
        this->oldCid = 0;
    } else {
        this->oldCid = new int[oldCid_arraysize];
        doParsimArrayUnpacking(b,this->oldCid,oldCid_arraysize);
    }
    delete [] this->newCid;
    b->unpack(newCid_arraysize);
    if (newCid_arraysize==0) {
        this->newCid = 0;
    } else {
        this->newCid = new int[newCid_arraysize];
        doParsimArrayUnpacking(b,this->newCid,newCid_arraysize);
    }
}

int WMaxMsgRngRspMsg::getPurpose() const
{
    return this->purpose;
}

void WMaxMsgRngRspMsg::setPurpose(int purpose)
{
    this->purpose = purpose;
}

WMaxRngRsp& WMaxMsgRngRspMsg::getRngRsp()
{
    return this->rngRsp;
}

void WMaxMsgRngRspMsg::setRngRsp(const WMaxRngRsp& rngRsp)
{
    this->rngRsp = rngRsp;
}

void WMaxMsgRngRspMsg::setOldCidArraySize(unsigned int size)
{
    int *oldCid2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = oldCid_arraysize < size ? oldCid_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        oldCid2[i] = this->oldCid[i];
    for (unsigned int i=sz; i<size; i++)
        oldCid2[i] = 0;
    oldCid_arraysize = size;
    delete [] this->oldCid;
    this->oldCid = oldCid2;
}

unsigned int WMaxMsgRngRspMsg::getOldCidArraySize() const
{
    return oldCid_arraysize;
}

int WMaxMsgRngRspMsg::getOldCid(unsigned int k) const
{
    if (k>=oldCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", oldCid_arraysize, k);
    return this->oldCid[k];
}

void WMaxMsgRngRspMsg::setOldCid(unsigned int k, int oldCid)
{
    if (k>=oldCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", oldCid_arraysize, k);
    this->oldCid[k] = oldCid;
}

void WMaxMsgRngRspMsg::setNewCidArraySize(unsigned int size)
{
    int *newCid2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = newCid_arraysize < size ? newCid_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        newCid2[i] = this->newCid[i];
    for (unsigned int i=sz; i<size; i++)
        newCid2[i] = 0;
    newCid_arraysize = size;
    delete [] this->newCid;
    this->newCid = newCid2;
}

unsigned int WMaxMsgRngRspMsg::getNewCidArraySize() const
{
    return newCid_arraysize;
}

int WMaxMsgRngRspMsg::getNewCid(unsigned int k) const
{
    if (k>=newCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", newCid_arraysize, k);
    return this->newCid[k];
}

void WMaxMsgRngRspMsg::setNewCid(unsigned int k, int newCid)
{
    if (k>=newCid_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", newCid_arraysize, k);
    this->newCid[k] = newCid;
}

class WMaxMsgRngRspMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgRngRspMsgDescriptor();
    virtual ~WMaxMsgRngRspMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgRngRspMsgDescriptor)

WMaxMsgRngRspMsgDescriptor::WMaxMsgRngRspMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgRngRspMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgRngRspMsgDescriptor::~WMaxMsgRngRspMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgRngRspMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgRngRspMsg *>(obj)!=nullptr;
}

const char **WMaxMsgRngRspMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgRngRspMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgRngRspMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int WMaxMsgRngRspMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgRngRspMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "purpose",
        "rngRsp",
        "oldCid",
        "newCid",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int WMaxMsgRngRspMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "purpose")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "rngRsp")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "oldCid")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "newCid")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgRngRspMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "WMaxRngRsp",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgRngRspMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgRngRspMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgRngRspMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngRspMsg *pp = (WMaxMsgRngRspMsg *)object; (void)pp;
    switch (field) {
        case 2: return pp->getOldCidArraySize();
        case 3: return pp->getNewCidArraySize();
        default: return 0;
    }
}

const char *WMaxMsgRngRspMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngRspMsg *pp = (WMaxMsgRngRspMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgRngRspMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngRspMsg *pp = (WMaxMsgRngRspMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPurpose());
        case 1: {std::stringstream out; out << pp->getRngRsp(); return out.str();}
        case 2: return long2string(pp->getOldCid(i));
        case 3: return long2string(pp->getNewCid(i));
        default: return "";
    }
}

bool WMaxMsgRngRspMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngRspMsg *pp = (WMaxMsgRngRspMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPurpose(string2long(value)); return true;
        case 2: pp->setOldCid(i,string2long(value)); return true;
        case 3: pp->setNewCid(i,string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgRngRspMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(WMaxRngRsp));
        default: return nullptr;
    };
}

void *WMaxMsgRngRspMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRngRspMsg *pp = (WMaxMsgRngRspMsg *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getRngRsp()); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgSbcReqMsg)

WMaxMsgSbcReqMsg::WMaxMsgSbcReqMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgSbcReqMsg::WMaxMsgSbcReqMsg(const WMaxMsgSbcReqMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgSbcReqMsg::~WMaxMsgSbcReqMsg()
{
}

WMaxMsgSbcReqMsg& WMaxMsgSbcReqMsg::operator=(const WMaxMsgSbcReqMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgSbcReqMsg::copy(const WMaxMsgSbcReqMsg& other)
{
}

void WMaxMsgSbcReqMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgSbcReqMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgSbcReqMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgSbcReqMsgDescriptor();
    virtual ~WMaxMsgSbcReqMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgSbcReqMsgDescriptor)

WMaxMsgSbcReqMsgDescriptor::WMaxMsgSbcReqMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgSbcReqMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgSbcReqMsgDescriptor::~WMaxMsgSbcReqMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgSbcReqMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgSbcReqMsg *>(obj)!=nullptr;
}

const char **WMaxMsgSbcReqMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgSbcReqMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgSbcReqMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgSbcReqMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgSbcReqMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgSbcReqMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgSbcReqMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgSbcReqMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgSbcReqMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgSbcReqMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcReqMsg *pp = (WMaxMsgSbcReqMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgSbcReqMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcReqMsg *pp = (WMaxMsgSbcReqMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgSbcReqMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcReqMsg *pp = (WMaxMsgSbcReqMsg *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgSbcReqMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcReqMsg *pp = (WMaxMsgSbcReqMsg *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgSbcReqMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgSbcReqMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcReqMsg *pp = (WMaxMsgSbcReqMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgSbcRspMsg)

WMaxMsgSbcRspMsg::WMaxMsgSbcRspMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgSbcRspMsg::WMaxMsgSbcRspMsg(const WMaxMsgSbcRspMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgSbcRspMsg::~WMaxMsgSbcRspMsg()
{
}

WMaxMsgSbcRspMsg& WMaxMsgSbcRspMsg::operator=(const WMaxMsgSbcRspMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgSbcRspMsg::copy(const WMaxMsgSbcRspMsg& other)
{
}

void WMaxMsgSbcRspMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgSbcRspMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgSbcRspMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgSbcRspMsgDescriptor();
    virtual ~WMaxMsgSbcRspMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgSbcRspMsgDescriptor)

WMaxMsgSbcRspMsgDescriptor::WMaxMsgSbcRspMsgDescriptor() : omnetpp::cClassDescriptor("WMaxMsgSbcRspMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgSbcRspMsgDescriptor::~WMaxMsgSbcRspMsgDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgSbcRspMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgSbcRspMsg *>(obj)!=nullptr;
}

const char **WMaxMsgSbcRspMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgSbcRspMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgSbcRspMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgSbcRspMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgSbcRspMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgSbcRspMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgSbcRspMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgSbcRspMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgSbcRspMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgSbcRspMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcRspMsg *pp = (WMaxMsgSbcRspMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgSbcRspMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcRspMsg *pp = (WMaxMsgSbcRspMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgSbcRspMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcRspMsg *pp = (WMaxMsgSbcRspMsg *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgSbcRspMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcRspMsg *pp = (WMaxMsgSbcRspMsg *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgSbcRspMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgSbcRspMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgSbcRspMsg *pp = (WMaxMsgSbcRspMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgPkmReq)

WMaxMsgPkmReq::WMaxMsgPkmReq(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->code = 0;
}

WMaxMsgPkmReq::WMaxMsgPkmReq(const WMaxMsgPkmReq& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgPkmReq::~WMaxMsgPkmReq()
{
}

WMaxMsgPkmReq& WMaxMsgPkmReq::operator=(const WMaxMsgPkmReq& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgPkmReq::copy(const WMaxMsgPkmReq& other)
{
    this->code = other.code;
}

void WMaxMsgPkmReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->code);
}

void WMaxMsgPkmReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->code);
}

int WMaxMsgPkmReq::getCode() const
{
    return this->code;
}

void WMaxMsgPkmReq::setCode(int code)
{
    this->code = code;
}

class WMaxMsgPkmReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgPkmReqDescriptor();
    virtual ~WMaxMsgPkmReqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgPkmReqDescriptor)

WMaxMsgPkmReqDescriptor::WMaxMsgPkmReqDescriptor() : omnetpp::cClassDescriptor("WMaxMsgPkmReq", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgPkmReqDescriptor::~WMaxMsgPkmReqDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgPkmReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgPkmReq *>(obj)!=nullptr;
}

const char **WMaxMsgPkmReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgPkmReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgPkmReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgPkmReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgPkmReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "code",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgPkmReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "code")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgPkmReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgPkmReqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgPkmReqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgPkmReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmReq *pp = (WMaxMsgPkmReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgPkmReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmReq *pp = (WMaxMsgPkmReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgPkmReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmReq *pp = (WMaxMsgPkmReq *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCode());
        default: return "";
    }
}

bool WMaxMsgPkmReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmReq *pp = (WMaxMsgPkmReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setCode(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgPkmReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgPkmReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmReq *pp = (WMaxMsgPkmReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgPkmRsp)

WMaxMsgPkmRsp::WMaxMsgPkmRsp(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->code = 0;
}

WMaxMsgPkmRsp::WMaxMsgPkmRsp(const WMaxMsgPkmRsp& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgPkmRsp::~WMaxMsgPkmRsp()
{
}

WMaxMsgPkmRsp& WMaxMsgPkmRsp::operator=(const WMaxMsgPkmRsp& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgPkmRsp::copy(const WMaxMsgPkmRsp& other)
{
    this->code = other.code;
}

void WMaxMsgPkmRsp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->code);
}

void WMaxMsgPkmRsp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->code);
}

int WMaxMsgPkmRsp::getCode() const
{
    return this->code;
}

void WMaxMsgPkmRsp::setCode(int code)
{
    this->code = code;
}

class WMaxMsgPkmRspDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgPkmRspDescriptor();
    virtual ~WMaxMsgPkmRspDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgPkmRspDescriptor)

WMaxMsgPkmRspDescriptor::WMaxMsgPkmRspDescriptor() : omnetpp::cClassDescriptor("WMaxMsgPkmRsp", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgPkmRspDescriptor::~WMaxMsgPkmRspDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgPkmRspDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgPkmRsp *>(obj)!=nullptr;
}

const char **WMaxMsgPkmRspDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgPkmRspDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgPkmRspDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgPkmRspDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgPkmRspDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "code",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgPkmRspDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "code")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgPkmRspDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgPkmRspDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgPkmRspDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgPkmRspDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmRsp *pp = (WMaxMsgPkmRsp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgPkmRspDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmRsp *pp = (WMaxMsgPkmRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgPkmRspDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmRsp *pp = (WMaxMsgPkmRsp *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCode());
        default: return "";
    }
}

bool WMaxMsgPkmRspDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmRsp *pp = (WMaxMsgPkmRsp *)object; (void)pp;
    switch (field) {
        case 0: pp->setCode(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgPkmRspDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgPkmRspDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgPkmRsp *pp = (WMaxMsgPkmRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgRegReq)

WMaxMsgRegReq::WMaxMsgRegReq(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgRegReq::WMaxMsgRegReq(const WMaxMsgRegReq& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgRegReq::~WMaxMsgRegReq()
{
}

WMaxMsgRegReq& WMaxMsgRegReq::operator=(const WMaxMsgRegReq& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgRegReq::copy(const WMaxMsgRegReq& other)
{
}

void WMaxMsgRegReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgRegReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgRegReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgRegReqDescriptor();
    virtual ~WMaxMsgRegReqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgRegReqDescriptor)

WMaxMsgRegReqDescriptor::WMaxMsgRegReqDescriptor() : omnetpp::cClassDescriptor("WMaxMsgRegReq", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgRegReqDescriptor::~WMaxMsgRegReqDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgRegReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgRegReq *>(obj)!=nullptr;
}

const char **WMaxMsgRegReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgRegReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgRegReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgRegReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgRegReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgRegReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgRegReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgRegReqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgRegReqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgRegReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegReq *pp = (WMaxMsgRegReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgRegReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegReq *pp = (WMaxMsgRegReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgRegReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegReq *pp = (WMaxMsgRegReq *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgRegReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegReq *pp = (WMaxMsgRegReq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgRegReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgRegReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegReq *pp = (WMaxMsgRegReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgRegRsp)

WMaxMsgRegRsp::WMaxMsgRegRsp(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgRegRsp::WMaxMsgRegRsp(const WMaxMsgRegRsp& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgRegRsp::~WMaxMsgRegRsp()
{
}

WMaxMsgRegRsp& WMaxMsgRegRsp::operator=(const WMaxMsgRegRsp& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgRegRsp::copy(const WMaxMsgRegRsp& other)
{
}

void WMaxMsgRegRsp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgRegRsp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgRegRspDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgRegRspDescriptor();
    virtual ~WMaxMsgRegRspDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgRegRspDescriptor)

WMaxMsgRegRspDescriptor::WMaxMsgRegRspDescriptor() : omnetpp::cClassDescriptor("WMaxMsgRegRsp", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgRegRspDescriptor::~WMaxMsgRegRspDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgRegRspDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgRegRsp *>(obj)!=nullptr;
}

const char **WMaxMsgRegRspDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgRegRspDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgRegRspDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgRegRspDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgRegRspDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgRegRspDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgRegRspDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgRegRspDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgRegRspDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgRegRspDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegRsp *pp = (WMaxMsgRegRsp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgRegRspDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegRsp *pp = (WMaxMsgRegRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgRegRspDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegRsp *pp = (WMaxMsgRegRsp *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgRegRspDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegRsp *pp = (WMaxMsgRegRsp *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgRegRspDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgRegRspDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgRegRsp *pp = (WMaxMsgRegRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgMobScnReq)

WMaxMsgMobScnReq::WMaxMsgMobScnReq(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgMobScnReq::WMaxMsgMobScnReq(const WMaxMsgMobScnReq& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgMobScnReq::~WMaxMsgMobScnReq()
{
}

WMaxMsgMobScnReq& WMaxMsgMobScnReq::operator=(const WMaxMsgMobScnReq& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgMobScnReq::copy(const WMaxMsgMobScnReq& other)
{
}

void WMaxMsgMobScnReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgMobScnReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgMobScnReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgMobScnReqDescriptor();
    virtual ~WMaxMsgMobScnReqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgMobScnReqDescriptor)

WMaxMsgMobScnReqDescriptor::WMaxMsgMobScnReqDescriptor() : omnetpp::cClassDescriptor("WMaxMsgMobScnReq", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgMobScnReqDescriptor::~WMaxMsgMobScnReqDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgMobScnReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgMobScnReq *>(obj)!=nullptr;
}

const char **WMaxMsgMobScnReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgMobScnReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgMobScnReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgMobScnReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgMobScnReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgMobScnReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgMobScnReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgMobScnReqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgMobScnReqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgMobScnReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnReq *pp = (WMaxMsgMobScnReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgMobScnReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnReq *pp = (WMaxMsgMobScnReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgMobScnReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnReq *pp = (WMaxMsgMobScnReq *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgMobScnReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnReq *pp = (WMaxMsgMobScnReq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgMobScnReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgMobScnReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnReq *pp = (WMaxMsgMobScnReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgMobScnRsp)

WMaxMsgMobScnRsp::WMaxMsgMobScnRsp(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgMobScnRsp::WMaxMsgMobScnRsp(const WMaxMsgMobScnRsp& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgMobScnRsp::~WMaxMsgMobScnRsp()
{
}

WMaxMsgMobScnRsp& WMaxMsgMobScnRsp::operator=(const WMaxMsgMobScnRsp& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgMobScnRsp::copy(const WMaxMsgMobScnRsp& other)
{
}

void WMaxMsgMobScnRsp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgMobScnRsp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgMobScnRspDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgMobScnRspDescriptor();
    virtual ~WMaxMsgMobScnRspDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgMobScnRspDescriptor)

WMaxMsgMobScnRspDescriptor::WMaxMsgMobScnRspDescriptor() : omnetpp::cClassDescriptor("WMaxMsgMobScnRsp", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgMobScnRspDescriptor::~WMaxMsgMobScnRspDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgMobScnRspDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgMobScnRsp *>(obj)!=nullptr;
}

const char **WMaxMsgMobScnRspDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgMobScnRspDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgMobScnRspDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgMobScnRspDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgMobScnRspDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgMobScnRspDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgMobScnRspDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgMobScnRspDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgMobScnRspDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgMobScnRspDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnRsp *pp = (WMaxMsgMobScnRsp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgMobScnRspDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnRsp *pp = (WMaxMsgMobScnRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgMobScnRspDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnRsp *pp = (WMaxMsgMobScnRsp *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgMobScnRspDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnRsp *pp = (WMaxMsgMobScnRsp *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgMobScnRspDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgMobScnRspDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMobScnRsp *pp = (WMaxMsgMobScnRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgMSHOREQ)

WMaxMsgMSHOREQ::WMaxMsgMSHOREQ(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    BSFull_arraysize = 0;
    this->BSFull = 0;
}

WMaxMsgMSHOREQ::WMaxMsgMSHOREQ(const WMaxMsgMSHOREQ& other) : ::omnetpp::cPacket(other)
{
    BSFull_arraysize = 0;
    this->BSFull = 0;
    copy(other);
}

WMaxMsgMSHOREQ::~WMaxMsgMSHOREQ()
{
    delete [] this->BSFull;
}

WMaxMsgMSHOREQ& WMaxMsgMSHOREQ::operator=(const WMaxMsgMSHOREQ& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgMSHOREQ::copy(const WMaxMsgMSHOREQ& other)
{
    delete [] this->BSFull;
    this->BSFull = (other.BSFull_arraysize==0) ? nullptr : new WMaxBSFull[other.BSFull_arraysize];
    BSFull_arraysize = other.BSFull_arraysize;
    for (unsigned int i=0; i<BSFull_arraysize; i++)
        this->BSFull[i] = other.BSFull[i];
}

void WMaxMsgMSHOREQ::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    b->pack(BSFull_arraysize);
    doParsimArrayPacking(b,this->BSFull,BSFull_arraysize);
}

void WMaxMsgMSHOREQ::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    delete [] this->BSFull;
    b->unpack(BSFull_arraysize);
    if (BSFull_arraysize==0) {
        this->BSFull = 0;
    } else {
        this->BSFull = new WMaxBSFull[BSFull_arraysize];
        doParsimArrayUnpacking(b,this->BSFull,BSFull_arraysize);
    }
}

void WMaxMsgMSHOREQ::setBSFullArraySize(unsigned int size)
{
    WMaxBSFull *BSFull2 = (size==0) ? nullptr : new WMaxBSFull[size];
    unsigned int sz = BSFull_arraysize < size ? BSFull_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        BSFull2[i] = this->BSFull[i];
    BSFull_arraysize = size;
    delete [] this->BSFull;
    this->BSFull = BSFull2;
}

unsigned int WMaxMsgMSHOREQ::getBSFullArraySize() const
{
    return BSFull_arraysize;
}

WMaxBSFull& WMaxMsgMSHOREQ::getBSFull(unsigned int k)
{
    if (k>=BSFull_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", BSFull_arraysize, k);
    return this->BSFull[k];
}

void WMaxMsgMSHOREQ::setBSFull(unsigned int k, const WMaxBSFull& BSFull)
{
    if (k>=BSFull_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", BSFull_arraysize, k);
    this->BSFull[k] = BSFull;
}

class WMaxMsgMSHOREQDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgMSHOREQDescriptor();
    virtual ~WMaxMsgMSHOREQDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgMSHOREQDescriptor)

WMaxMsgMSHOREQDescriptor::WMaxMsgMSHOREQDescriptor() : omnetpp::cClassDescriptor("WMaxMsgMSHOREQ", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgMSHOREQDescriptor::~WMaxMsgMSHOREQDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgMSHOREQDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgMSHOREQ *>(obj)!=nullptr;
}

const char **WMaxMsgMSHOREQDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgMSHOREQDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgMSHOREQDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgMSHOREQDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgMSHOREQDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "BSFull",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgMSHOREQDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSFull")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgMSHOREQDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WMaxBSFull",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgMSHOREQDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgMSHOREQDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgMSHOREQDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMSHOREQ *pp = (WMaxMsgMSHOREQ *)object; (void)pp;
    switch (field) {
        case 0: return pp->getBSFullArraySize();
        default: return 0;
    }
}

const char *WMaxMsgMSHOREQDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMSHOREQ *pp = (WMaxMsgMSHOREQ *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgMSHOREQDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMSHOREQ *pp = (WMaxMsgMSHOREQ *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getBSFull(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgMSHOREQDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMSHOREQ *pp = (WMaxMsgMSHOREQ *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgMSHOREQDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WMaxBSFull));
        default: return nullptr;
    };
}

void *WMaxMsgMSHOREQDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgMSHOREQ *pp = (WMaxMsgMSHOREQ *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getBSFull(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgBSHORSP)

WMaxMsgBSHORSP::WMaxMsgBSHORSP(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    BSFull_arraysize = 0;
    this->BSFull = 0;
}

WMaxMsgBSHORSP::WMaxMsgBSHORSP(const WMaxMsgBSHORSP& other) : ::omnetpp::cPacket(other)
{
    BSFull_arraysize = 0;
    this->BSFull = 0;
    copy(other);
}

WMaxMsgBSHORSP::~WMaxMsgBSHORSP()
{
    delete [] this->BSFull;
}

WMaxMsgBSHORSP& WMaxMsgBSHORSP::operator=(const WMaxMsgBSHORSP& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgBSHORSP::copy(const WMaxMsgBSHORSP& other)
{
    delete [] this->BSFull;
    this->BSFull = (other.BSFull_arraysize==0) ? nullptr : new WMaxBSFull[other.BSFull_arraysize];
    BSFull_arraysize = other.BSFull_arraysize;
    for (unsigned int i=0; i<BSFull_arraysize; i++)
        this->BSFull[i] = other.BSFull[i];
}

void WMaxMsgBSHORSP::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    b->pack(BSFull_arraysize);
    doParsimArrayPacking(b,this->BSFull,BSFull_arraysize);
}

void WMaxMsgBSHORSP::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    delete [] this->BSFull;
    b->unpack(BSFull_arraysize);
    if (BSFull_arraysize==0) {
        this->BSFull = 0;
    } else {
        this->BSFull = new WMaxBSFull[BSFull_arraysize];
        doParsimArrayUnpacking(b,this->BSFull,BSFull_arraysize);
    }
}

void WMaxMsgBSHORSP::setBSFullArraySize(unsigned int size)
{
    WMaxBSFull *BSFull2 = (size==0) ? nullptr : new WMaxBSFull[size];
    unsigned int sz = BSFull_arraysize < size ? BSFull_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        BSFull2[i] = this->BSFull[i];
    BSFull_arraysize = size;
    delete [] this->BSFull;
    this->BSFull = BSFull2;
}

unsigned int WMaxMsgBSHORSP::getBSFullArraySize() const
{
    return BSFull_arraysize;
}

WMaxBSFull& WMaxMsgBSHORSP::getBSFull(unsigned int k)
{
    if (k>=BSFull_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", BSFull_arraysize, k);
    return this->BSFull[k];
}

void WMaxMsgBSHORSP::setBSFull(unsigned int k, const WMaxBSFull& BSFull)
{
    if (k>=BSFull_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", BSFull_arraysize, k);
    this->BSFull[k] = BSFull;
}

class WMaxMsgBSHORSPDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgBSHORSPDescriptor();
    virtual ~WMaxMsgBSHORSPDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgBSHORSPDescriptor)

WMaxMsgBSHORSPDescriptor::WMaxMsgBSHORSPDescriptor() : omnetpp::cClassDescriptor("WMaxMsgBSHORSP", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgBSHORSPDescriptor::~WMaxMsgBSHORSPDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgBSHORSPDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgBSHORSP *>(obj)!=nullptr;
}

const char **WMaxMsgBSHORSPDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgBSHORSPDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgBSHORSPDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMsgBSHORSPDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgBSHORSPDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "BSFull",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMsgBSHORSPDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSFull")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgBSHORSPDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WMaxBSFull",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgBSHORSPDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgBSHORSPDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgBSHORSPDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBSHORSP *pp = (WMaxMsgBSHORSP *)object; (void)pp;
    switch (field) {
        case 0: return pp->getBSFullArraySize();
        default: return 0;
    }
}

const char *WMaxMsgBSHORSPDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBSHORSP *pp = (WMaxMsgBSHORSP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgBSHORSPDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBSHORSP *pp = (WMaxMsgBSHORSP *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getBSFull(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgBSHORSPDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBSHORSP *pp = (WMaxMsgBSHORSP *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgBSHORSPDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WMaxBSFull));
        default: return nullptr;
    };
}

void *WMaxMsgBSHORSPDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBSHORSP *pp = (WMaxMsgBSHORSP *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getBSFull(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgHOIND)

WMaxMsgHOIND::WMaxMsgHOIND(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->status = 0;
}

WMaxMsgHOIND::WMaxMsgHOIND(const WMaxMsgHOIND& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgHOIND::~WMaxMsgHOIND()
{
}

WMaxMsgHOIND& WMaxMsgHOIND::operator=(const WMaxMsgHOIND& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgHOIND::copy(const WMaxMsgHOIND& other)
{
    this->status = other.status;
    this->target = other.target;
}

void WMaxMsgHOIND::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->target);
}

void WMaxMsgHOIND::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->target);
}

int WMaxMsgHOIND::getStatus() const
{
    return this->status;
}

void WMaxMsgHOIND::setStatus(int status)
{
    this->status = status;
}

WMaxBSFull& WMaxMsgHOIND::getTarget()
{
    return this->target;
}

void WMaxMsgHOIND::setTarget(const WMaxBSFull& target)
{
    this->target = target;
}

class WMaxMsgHOINDDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgHOINDDescriptor();
    virtual ~WMaxMsgHOINDDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgHOINDDescriptor)

WMaxMsgHOINDDescriptor::WMaxMsgHOINDDescriptor() : omnetpp::cClassDescriptor("WMaxMsgHOIND", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgHOINDDescriptor::~WMaxMsgHOINDDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgHOINDDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgHOIND *>(obj)!=nullptr;
}

const char **WMaxMsgHOINDDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgHOINDDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgHOINDDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int WMaxMsgHOINDDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgHOINDDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "status",
        "target",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int WMaxMsgHOINDDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "target")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgHOINDDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "WMaxBSFull",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgHOINDDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgHOINDDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgHOINDDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgHOIND *pp = (WMaxMsgHOIND *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgHOINDDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgHOIND *pp = (WMaxMsgHOIND *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgHOINDDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgHOIND *pp = (WMaxMsgHOIND *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getStatus());
        case 1: {std::stringstream out; out << pp->getTarget(); return out.str();}
        default: return "";
    }
}

bool WMaxMsgHOINDDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgHOIND *pp = (WMaxMsgHOIND *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgHOINDDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(WMaxBSFull));
        default: return nullptr;
    };
}

void *WMaxMsgHOINDDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgHOIND *pp = (WMaxMsgHOIND *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getTarget()); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgCDMA)

WMaxMsgCDMA::WMaxMsgCDMA(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->code = 0;
    this->purpose = 0;
}

WMaxMsgCDMA::WMaxMsgCDMA(const WMaxMsgCDMA& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgCDMA::~WMaxMsgCDMA()
{
}

WMaxMsgCDMA& WMaxMsgCDMA::operator=(const WMaxMsgCDMA& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgCDMA::copy(const WMaxMsgCDMA& other)
{
    this->code = other.code;
    this->purpose = other.purpose;
}

void WMaxMsgCDMA::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->code);
    doParsimPacking(b,this->purpose);
}

void WMaxMsgCDMA::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->code);
    doParsimUnpacking(b,this->purpose);
}

int WMaxMsgCDMA::getCode() const
{
    return this->code;
}

void WMaxMsgCDMA::setCode(int code)
{
    this->code = code;
}

int WMaxMsgCDMA::getPurpose() const
{
    return this->purpose;
}

void WMaxMsgCDMA::setPurpose(int purpose)
{
    this->purpose = purpose;
}

class WMaxMsgCDMADescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgCDMADescriptor();
    virtual ~WMaxMsgCDMADescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgCDMADescriptor)

WMaxMsgCDMADescriptor::WMaxMsgCDMADescriptor() : omnetpp::cClassDescriptor("WMaxMsgCDMA", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgCDMADescriptor::~WMaxMsgCDMADescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgCDMADescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgCDMA *>(obj)!=nullptr;
}

const char **WMaxMsgCDMADescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgCDMADescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgCDMADescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int WMaxMsgCDMADescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgCDMADescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "code",
        "purpose",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int WMaxMsgCDMADescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "code")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "purpose")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgCDMADescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgCDMADescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgCDMADescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgCDMADescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgCDMA *pp = (WMaxMsgCDMA *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgCDMADescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgCDMA *pp = (WMaxMsgCDMA *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgCDMADescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgCDMA *pp = (WMaxMsgCDMA *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCode());
        case 1: return long2string(pp->getPurpose());
        default: return "";
    }
}

bool WMaxMsgCDMADescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgCDMA *pp = (WMaxMsgCDMA *)object; (void)pp;
    switch (field) {
        case 0: pp->setCode(string2long(value)); return true;
        case 1: pp->setPurpose(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgCDMADescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgCDMADescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgCDMA *pp = (WMaxMsgCDMA *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgBWR)

WMaxMsgBWR::WMaxMsgBWR(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMsgBWR::WMaxMsgBWR(const WMaxMsgBWR& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgBWR::~WMaxMsgBWR()
{
}

WMaxMsgBWR& WMaxMsgBWR::operator=(const WMaxMsgBWR& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgBWR::copy(const WMaxMsgBWR& other)
{
}

void WMaxMsgBWR::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMsgBWR::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMsgBWRDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgBWRDescriptor();
    virtual ~WMaxMsgBWRDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgBWRDescriptor)

WMaxMsgBWRDescriptor::WMaxMsgBWRDescriptor() : omnetpp::cClassDescriptor("WMaxMsgBWR", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgBWRDescriptor::~WMaxMsgBWRDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgBWRDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgBWR *>(obj)!=nullptr;
}

const char **WMaxMsgBWRDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgBWRDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgBWRDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMsgBWRDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMsgBWRDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMsgBWRDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgBWRDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMsgBWRDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgBWRDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgBWRDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBWR *pp = (WMaxMsgBWR *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgBWRDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBWR *pp = (WMaxMsgBWR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgBWRDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBWR *pp = (WMaxMsgBWR *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMsgBWRDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBWR *pp = (WMaxMsgBWR *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMsgBWRDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMsgBWRDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgBWR *pp = (WMaxMsgBWR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDsaReq)

WMaxMsgDsaReq::WMaxMsgDsaReq(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->transactionID = 0;
    qos_arraysize = 0;
    this->qos = 0;
}

WMaxMsgDsaReq::WMaxMsgDsaReq(const WMaxMsgDsaReq& other) : ::omnetpp::cPacket(other)
{
    qos_arraysize = 0;
    this->qos = 0;
    copy(other);
}

WMaxMsgDsaReq::~WMaxMsgDsaReq()
{
    delete [] this->qos;
}

WMaxMsgDsaReq& WMaxMsgDsaReq::operator=(const WMaxMsgDsaReq& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDsaReq::copy(const WMaxMsgDsaReq& other)
{
    this->transactionID = other.transactionID;
    delete [] this->qos;
    this->qos = (other.qos_arraysize==0) ? nullptr : new WMaxQos[other.qos_arraysize];
    qos_arraysize = other.qos_arraysize;
    for (unsigned int i=0; i<qos_arraysize; i++)
        this->qos[i] = other.qos[i];
}

void WMaxMsgDsaReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->transactionID);
    b->pack(qos_arraysize);
    doParsimArrayPacking(b,this->qos,qos_arraysize);
}

void WMaxMsgDsaReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->transactionID);
    delete [] this->qos;
    b->unpack(qos_arraysize);
    if (qos_arraysize==0) {
        this->qos = 0;
    } else {
        this->qos = new WMaxQos[qos_arraysize];
        doParsimArrayUnpacking(b,this->qos,qos_arraysize);
    }
}

int WMaxMsgDsaReq::getTransactionID() const
{
    return this->transactionID;
}

void WMaxMsgDsaReq::setTransactionID(int transactionID)
{
    this->transactionID = transactionID;
}

void WMaxMsgDsaReq::setQosArraySize(unsigned int size)
{
    WMaxQos *qos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = qos_arraysize < size ? qos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        qos2[i] = this->qos[i];
    qos_arraysize = size;
    delete [] this->qos;
    this->qos = qos2;
}

unsigned int WMaxMsgDsaReq::getQosArraySize() const
{
    return qos_arraysize;
}

WMaxQos& WMaxMsgDsaReq::getQos(unsigned int k)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    return this->qos[k];
}

void WMaxMsgDsaReq::setQos(unsigned int k, const WMaxQos& qos)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    this->qos[k] = qos;
}

class WMaxMsgDsaReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDsaReqDescriptor();
    virtual ~WMaxMsgDsaReqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDsaReqDescriptor)

WMaxMsgDsaReqDescriptor::WMaxMsgDsaReqDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDsaReq", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDsaReqDescriptor::~WMaxMsgDsaReqDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDsaReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDsaReq *>(obj)!=nullptr;
}

const char **WMaxMsgDsaReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDsaReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDsaReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int WMaxMsgDsaReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDsaReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transactionID",
        "qos",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int WMaxMsgDsaReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transactionID")==0) return base+0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qos")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDsaReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "WMaxQos",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDsaReqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDsaReqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDsaReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaReq *pp = (WMaxMsgDsaReq *)object; (void)pp;
    switch (field) {
        case 1: return pp->getQosArraySize();
        default: return 0;
    }
}

const char *WMaxMsgDsaReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaReq *pp = (WMaxMsgDsaReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDsaReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaReq *pp = (WMaxMsgDsaReq *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTransactionID());
        case 1: {std::stringstream out; out << pp->getQos(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgDsaReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaReq *pp = (WMaxMsgDsaReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setTransactionID(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgDsaReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(WMaxQos));
        default: return nullptr;
    };
}

void *WMaxMsgDsaReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaReq *pp = (WMaxMsgDsaReq *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getQos(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDsxRvd)

WMaxMsgDsxRvd::WMaxMsgDsxRvd(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->transactionID = 0;
    this->confirmationCode = 0;
}

WMaxMsgDsxRvd::WMaxMsgDsxRvd(const WMaxMsgDsxRvd& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMsgDsxRvd::~WMaxMsgDsxRvd()
{
}

WMaxMsgDsxRvd& WMaxMsgDsxRvd::operator=(const WMaxMsgDsxRvd& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDsxRvd::copy(const WMaxMsgDsxRvd& other)
{
    this->transactionID = other.transactionID;
    this->confirmationCode = other.confirmationCode;
}

void WMaxMsgDsxRvd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->transactionID);
    doParsimPacking(b,this->confirmationCode);
}

void WMaxMsgDsxRvd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->transactionID);
    doParsimUnpacking(b,this->confirmationCode);
}

int WMaxMsgDsxRvd::getTransactionID() const
{
    return this->transactionID;
}

void WMaxMsgDsxRvd::setTransactionID(int transactionID)
{
    this->transactionID = transactionID;
}

int WMaxMsgDsxRvd::getConfirmationCode() const
{
    return this->confirmationCode;
}

void WMaxMsgDsxRvd::setConfirmationCode(int confirmationCode)
{
    this->confirmationCode = confirmationCode;
}

class WMaxMsgDsxRvdDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDsxRvdDescriptor();
    virtual ~WMaxMsgDsxRvdDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDsxRvdDescriptor)

WMaxMsgDsxRvdDescriptor::WMaxMsgDsxRvdDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDsxRvd", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDsxRvdDescriptor::~WMaxMsgDsxRvdDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDsxRvdDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDsxRvd *>(obj)!=nullptr;
}

const char **WMaxMsgDsxRvdDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDsxRvdDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDsxRvdDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int WMaxMsgDsxRvdDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDsxRvdDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transactionID",
        "confirmationCode",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int WMaxMsgDsxRvdDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transactionID")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "confirmationCode")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDsxRvdDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDsxRvdDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDsxRvdDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDsxRvdDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsxRvd *pp = (WMaxMsgDsxRvd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMsgDsxRvdDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsxRvd *pp = (WMaxMsgDsxRvd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDsxRvdDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsxRvd *pp = (WMaxMsgDsxRvd *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTransactionID());
        case 1: return long2string(pp->getConfirmationCode());
        default: return "";
    }
}

bool WMaxMsgDsxRvdDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsxRvd *pp = (WMaxMsgDsxRvd *)object; (void)pp;
    switch (field) {
        case 0: pp->setTransactionID(string2long(value)); return true;
        case 1: pp->setConfirmationCode(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgDsxRvdDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMsgDsxRvdDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsxRvd *pp = (WMaxMsgDsxRvd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDsaRsp)

WMaxMsgDsaRsp::WMaxMsgDsaRsp(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->transactionID = 0;
    this->confirmationCode = 0;
    qos_arraysize = 0;
    this->qos = 0;
    this->cid = 0;
}

WMaxMsgDsaRsp::WMaxMsgDsaRsp(const WMaxMsgDsaRsp& other) : ::omnetpp::cPacket(other)
{
    qos_arraysize = 0;
    this->qos = 0;
    copy(other);
}

WMaxMsgDsaRsp::~WMaxMsgDsaRsp()
{
    delete [] this->qos;
}

WMaxMsgDsaRsp& WMaxMsgDsaRsp::operator=(const WMaxMsgDsaRsp& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDsaRsp::copy(const WMaxMsgDsaRsp& other)
{
    this->transactionID = other.transactionID;
    this->confirmationCode = other.confirmationCode;
    delete [] this->qos;
    this->qos = (other.qos_arraysize==0) ? nullptr : new WMaxQos[other.qos_arraysize];
    qos_arraysize = other.qos_arraysize;
    for (unsigned int i=0; i<qos_arraysize; i++)
        this->qos[i] = other.qos[i];
    this->cid = other.cid;
}

void WMaxMsgDsaRsp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->transactionID);
    doParsimPacking(b,this->confirmationCode);
    b->pack(qos_arraysize);
    doParsimArrayPacking(b,this->qos,qos_arraysize);
    doParsimPacking(b,this->cid);
}

void WMaxMsgDsaRsp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->transactionID);
    doParsimUnpacking(b,this->confirmationCode);
    delete [] this->qos;
    b->unpack(qos_arraysize);
    if (qos_arraysize==0) {
        this->qos = 0;
    } else {
        this->qos = new WMaxQos[qos_arraysize];
        doParsimArrayUnpacking(b,this->qos,qos_arraysize);
    }
    doParsimUnpacking(b,this->cid);
}

int WMaxMsgDsaRsp::getTransactionID() const
{
    return this->transactionID;
}

void WMaxMsgDsaRsp::setTransactionID(int transactionID)
{
    this->transactionID = transactionID;
}

int WMaxMsgDsaRsp::getConfirmationCode() const
{
    return this->confirmationCode;
}

void WMaxMsgDsaRsp::setConfirmationCode(int confirmationCode)
{
    this->confirmationCode = confirmationCode;
}

void WMaxMsgDsaRsp::setQosArraySize(unsigned int size)
{
    WMaxQos *qos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = qos_arraysize < size ? qos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        qos2[i] = this->qos[i];
    qos_arraysize = size;
    delete [] this->qos;
    this->qos = qos2;
}

unsigned int WMaxMsgDsaRsp::getQosArraySize() const
{
    return qos_arraysize;
}

WMaxQos& WMaxMsgDsaRsp::getQos(unsigned int k)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    return this->qos[k];
}

void WMaxMsgDsaRsp::setQos(unsigned int k, const WMaxQos& qos)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    this->qos[k] = qos;
}

int WMaxMsgDsaRsp::getCid() const
{
    return this->cid;
}

void WMaxMsgDsaRsp::setCid(int cid)
{
    this->cid = cid;
}

class WMaxMsgDsaRspDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDsaRspDescriptor();
    virtual ~WMaxMsgDsaRspDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDsaRspDescriptor)

WMaxMsgDsaRspDescriptor::WMaxMsgDsaRspDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDsaRsp", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDsaRspDescriptor::~WMaxMsgDsaRspDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDsaRspDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDsaRsp *>(obj)!=nullptr;
}

const char **WMaxMsgDsaRspDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDsaRspDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDsaRspDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int WMaxMsgDsaRspDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDsaRspDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transactionID",
        "confirmationCode",
        "qos",
        "cid",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int WMaxMsgDsaRspDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transactionID")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "confirmationCode")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "qos")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "cid")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDsaRspDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "WMaxQos",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDsaRspDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDsaRspDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDsaRspDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaRsp *pp = (WMaxMsgDsaRsp *)object; (void)pp;
    switch (field) {
        case 2: return pp->getQosArraySize();
        default: return 0;
    }
}

const char *WMaxMsgDsaRspDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaRsp *pp = (WMaxMsgDsaRsp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDsaRspDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaRsp *pp = (WMaxMsgDsaRsp *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTransactionID());
        case 1: return long2string(pp->getConfirmationCode());
        case 2: {std::stringstream out; out << pp->getQos(i); return out.str();}
        case 3: return long2string(pp->getCid());
        default: return "";
    }
}

bool WMaxMsgDsaRspDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaRsp *pp = (WMaxMsgDsaRsp *)object; (void)pp;
    switch (field) {
        case 0: pp->setTransactionID(string2long(value)); return true;
        case 1: pp->setConfirmationCode(string2long(value)); return true;
        case 3: pp->setCid(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgDsaRspDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(WMaxQos));
        default: return nullptr;
    };
}

void *WMaxMsgDsaRspDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaRsp *pp = (WMaxMsgDsaRsp *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getQos(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMsgDsaAck)

WMaxMsgDsaAck::WMaxMsgDsaAck(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->transactionID = 0;
    this->confirmationCode = 0;
    qos_arraysize = 0;
    this->qos = 0;
}

WMaxMsgDsaAck::WMaxMsgDsaAck(const WMaxMsgDsaAck& other) : ::omnetpp::cPacket(other)
{
    qos_arraysize = 0;
    this->qos = 0;
    copy(other);
}

WMaxMsgDsaAck::~WMaxMsgDsaAck()
{
    delete [] this->qos;
}

WMaxMsgDsaAck& WMaxMsgDsaAck::operator=(const WMaxMsgDsaAck& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMsgDsaAck::copy(const WMaxMsgDsaAck& other)
{
    this->transactionID = other.transactionID;
    this->confirmationCode = other.confirmationCode;
    delete [] this->qos;
    this->qos = (other.qos_arraysize==0) ? nullptr : new WMaxQos[other.qos_arraysize];
    qos_arraysize = other.qos_arraysize;
    for (unsigned int i=0; i<qos_arraysize; i++)
        this->qos[i] = other.qos[i];
}

void WMaxMsgDsaAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->transactionID);
    doParsimPacking(b,this->confirmationCode);
    b->pack(qos_arraysize);
    doParsimArrayPacking(b,this->qos,qos_arraysize);
}

void WMaxMsgDsaAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->transactionID);
    doParsimUnpacking(b,this->confirmationCode);
    delete [] this->qos;
    b->unpack(qos_arraysize);
    if (qos_arraysize==0) {
        this->qos = 0;
    } else {
        this->qos = new WMaxQos[qos_arraysize];
        doParsimArrayUnpacking(b,this->qos,qos_arraysize);
    }
}

int WMaxMsgDsaAck::getTransactionID() const
{
    return this->transactionID;
}

void WMaxMsgDsaAck::setTransactionID(int transactionID)
{
    this->transactionID = transactionID;
}

int WMaxMsgDsaAck::getConfirmationCode() const
{
    return this->confirmationCode;
}

void WMaxMsgDsaAck::setConfirmationCode(int confirmationCode)
{
    this->confirmationCode = confirmationCode;
}

void WMaxMsgDsaAck::setQosArraySize(unsigned int size)
{
    WMaxQos *qos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = qos_arraysize < size ? qos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        qos2[i] = this->qos[i];
    qos_arraysize = size;
    delete [] this->qos;
    this->qos = qos2;
}

unsigned int WMaxMsgDsaAck::getQosArraySize() const
{
    return qos_arraysize;
}

WMaxQos& WMaxMsgDsaAck::getQos(unsigned int k)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    return this->qos[k];
}

void WMaxMsgDsaAck::setQos(unsigned int k, const WMaxQos& qos)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    this->qos[k] = qos;
}

class WMaxMsgDsaAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMsgDsaAckDescriptor();
    virtual ~WMaxMsgDsaAckDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMsgDsaAckDescriptor)

WMaxMsgDsaAckDescriptor::WMaxMsgDsaAckDescriptor() : omnetpp::cClassDescriptor("WMaxMsgDsaAck", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMsgDsaAckDescriptor::~WMaxMsgDsaAckDescriptor()
{
    delete[] propertynames;
}

bool WMaxMsgDsaAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMsgDsaAck *>(obj)!=nullptr;
}

const char **WMaxMsgDsaAckDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMsgDsaAckDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMsgDsaAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WMaxMsgDsaAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMsgDsaAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transactionID",
        "confirmationCode",
        "qos",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int WMaxMsgDsaAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transactionID")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "confirmationCode")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "qos")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMsgDsaAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "WMaxQos",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMsgDsaAckDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMsgDsaAckDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMsgDsaAckDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaAck *pp = (WMaxMsgDsaAck *)object; (void)pp;
    switch (field) {
        case 2: return pp->getQosArraySize();
        default: return 0;
    }
}

const char *WMaxMsgDsaAckDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaAck *pp = (WMaxMsgDsaAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMsgDsaAckDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaAck *pp = (WMaxMsgDsaAck *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTransactionID());
        case 1: return long2string(pp->getConfirmationCode());
        case 2: {std::stringstream out; out << pp->getQos(i); return out.str();}
        default: return "";
    }
}

bool WMaxMsgDsaAckDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaAck *pp = (WMaxMsgDsaAck *)object; (void)pp;
    switch (field) {
        case 0: pp->setTransactionID(string2long(value)); return true;
        case 1: pp->setConfirmationCode(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMsgDsaAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(WMaxQos));
        default: return nullptr;
    };
}

void *WMaxMsgDsaAckDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMsgDsaAck *pp = (WMaxMsgDsaAck *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getQos(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxPhyDummyFrameStart)

WMaxPhyDummyFrameStart::WMaxPhyDummyFrameStart(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxPhyDummyFrameStart::WMaxPhyDummyFrameStart(const WMaxPhyDummyFrameStart& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxPhyDummyFrameStart::~WMaxPhyDummyFrameStart()
{
}

WMaxPhyDummyFrameStart& WMaxPhyDummyFrameStart::operator=(const WMaxPhyDummyFrameStart& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxPhyDummyFrameStart::copy(const WMaxPhyDummyFrameStart& other)
{
}

void WMaxPhyDummyFrameStart::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxPhyDummyFrameStart::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxPhyDummyFrameStartDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxPhyDummyFrameStartDescriptor();
    virtual ~WMaxPhyDummyFrameStartDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxPhyDummyFrameStartDescriptor)

WMaxPhyDummyFrameStartDescriptor::WMaxPhyDummyFrameStartDescriptor() : omnetpp::cClassDescriptor("WMaxPhyDummyFrameStart", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxPhyDummyFrameStartDescriptor::~WMaxPhyDummyFrameStartDescriptor()
{
    delete[] propertynames;
}

bool WMaxPhyDummyFrameStartDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxPhyDummyFrameStart *>(obj)!=nullptr;
}

const char **WMaxPhyDummyFrameStartDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxPhyDummyFrameStartDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxPhyDummyFrameStartDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxPhyDummyFrameStartDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxPhyDummyFrameStartDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxPhyDummyFrameStartDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxPhyDummyFrameStartDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxPhyDummyFrameStartDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxPhyDummyFrameStartDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxPhyDummyFrameStartDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxPhyDummyFrameStart *pp = (WMaxPhyDummyFrameStart *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxPhyDummyFrameStartDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxPhyDummyFrameStart *pp = (WMaxPhyDummyFrameStart *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxPhyDummyFrameStartDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxPhyDummyFrameStart *pp = (WMaxPhyDummyFrameStart *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxPhyDummyFrameStartDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxPhyDummyFrameStart *pp = (WMaxPhyDummyFrameStart *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxPhyDummyFrameStartDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxPhyDummyFrameStartDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxPhyDummyFrameStart *pp = (WMaxPhyDummyFrameStart *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxEvent_FlowCreationStart)

WMaxEvent_FlowCreationStart::WMaxEvent_FlowCreationStart(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->skipDSA = 0;
    this->gateIndex = 0;
    qos_arraysize = 0;
    this->qos = 0;
}

WMaxEvent_FlowCreationStart::WMaxEvent_FlowCreationStart(const WMaxEvent_FlowCreationStart& other) : ::omnetpp::cPacket(other)
{
    qos_arraysize = 0;
    this->qos = 0;
    copy(other);
}

WMaxEvent_FlowCreationStart::~WMaxEvent_FlowCreationStart()
{
    delete [] this->qos;
}

WMaxEvent_FlowCreationStart& WMaxEvent_FlowCreationStart::operator=(const WMaxEvent_FlowCreationStart& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxEvent_FlowCreationStart::copy(const WMaxEvent_FlowCreationStart& other)
{
    this->skipDSA = other.skipDSA;
    this->gateIndex = other.gateIndex;
    delete [] this->qos;
    this->qos = (other.qos_arraysize==0) ? nullptr : new WMaxQos[other.qos_arraysize];
    qos_arraysize = other.qos_arraysize;
    for (unsigned int i=0; i<qos_arraysize; i++)
        this->qos[i] = other.qos[i];
}

void WMaxEvent_FlowCreationStart::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->skipDSA);
    doParsimPacking(b,this->gateIndex);
    b->pack(qos_arraysize);
    doParsimArrayPacking(b,this->qos,qos_arraysize);
}

void WMaxEvent_FlowCreationStart::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->skipDSA);
    doParsimUnpacking(b,this->gateIndex);
    delete [] this->qos;
    b->unpack(qos_arraysize);
    if (qos_arraysize==0) {
        this->qos = 0;
    } else {
        this->qos = new WMaxQos[qos_arraysize];
        doParsimArrayUnpacking(b,this->qos,qos_arraysize);
    }
}

int WMaxEvent_FlowCreationStart::getSkipDSA() const
{
    return this->skipDSA;
}

void WMaxEvent_FlowCreationStart::setSkipDSA(int skipDSA)
{
    this->skipDSA = skipDSA;
}

int WMaxEvent_FlowCreationStart::getGateIndex() const
{
    return this->gateIndex;
}

void WMaxEvent_FlowCreationStart::setGateIndex(int gateIndex)
{
    this->gateIndex = gateIndex;
}

void WMaxEvent_FlowCreationStart::setQosArraySize(unsigned int size)
{
    WMaxQos *qos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = qos_arraysize < size ? qos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        qos2[i] = this->qos[i];
    qos_arraysize = size;
    delete [] this->qos;
    this->qos = qos2;
}

unsigned int WMaxEvent_FlowCreationStart::getQosArraySize() const
{
    return qos_arraysize;
}

WMaxQos& WMaxEvent_FlowCreationStart::getQos(unsigned int k)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    return this->qos[k];
}

void WMaxEvent_FlowCreationStart::setQos(unsigned int k, const WMaxQos& qos)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    this->qos[k] = qos;
}

class WMaxEvent_FlowCreationStartDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxEvent_FlowCreationStartDescriptor();
    virtual ~WMaxEvent_FlowCreationStartDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxEvent_FlowCreationStartDescriptor)

WMaxEvent_FlowCreationStartDescriptor::WMaxEvent_FlowCreationStartDescriptor() : omnetpp::cClassDescriptor("WMaxEvent_FlowCreationStart", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxEvent_FlowCreationStartDescriptor::~WMaxEvent_FlowCreationStartDescriptor()
{
    delete[] propertynames;
}

bool WMaxEvent_FlowCreationStartDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxEvent_FlowCreationStart *>(obj)!=nullptr;
}

const char **WMaxEvent_FlowCreationStartDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxEvent_FlowCreationStartDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxEvent_FlowCreationStartDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WMaxEvent_FlowCreationStartDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WMaxEvent_FlowCreationStartDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "skipDSA",
        "gateIndex",
        "qos",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int WMaxEvent_FlowCreationStartDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "skipDSA")==0) return base+0;
    if (fieldName[0]=='g' && strcmp(fieldName, "gateIndex")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "qos")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxEvent_FlowCreationStartDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "WMaxQos",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxEvent_FlowCreationStartDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxEvent_FlowCreationStartDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxEvent_FlowCreationStartDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowCreationStart *pp = (WMaxEvent_FlowCreationStart *)object; (void)pp;
    switch (field) {
        case 2: return pp->getQosArraySize();
        default: return 0;
    }
}

const char *WMaxEvent_FlowCreationStartDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowCreationStart *pp = (WMaxEvent_FlowCreationStart *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxEvent_FlowCreationStartDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowCreationStart *pp = (WMaxEvent_FlowCreationStart *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSkipDSA());
        case 1: return long2string(pp->getGateIndex());
        case 2: {std::stringstream out; out << pp->getQos(i); return out.str();}
        default: return "";
    }
}

bool WMaxEvent_FlowCreationStartDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowCreationStart *pp = (WMaxEvent_FlowCreationStart *)object; (void)pp;
    switch (field) {
        case 0: pp->setSkipDSA(string2long(value)); return true;
        case 1: pp->setGateIndex(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxEvent_FlowCreationStartDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(WMaxQos));
        default: return nullptr;
    };
}

void *WMaxEvent_FlowCreationStartDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowCreationStart *pp = (WMaxEvent_FlowCreationStart *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getQos(i)); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMacAddConn)

WMaxMacAddConn::WMaxMacAddConn(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->gateIndex = 0;
    this->cid = 0;
    qos_arraysize = 0;
    this->qos = 0;
    this->macAddr = 0;
}

WMaxMacAddConn::WMaxMacAddConn(const WMaxMacAddConn& other) : ::omnetpp::cPacket(other)
{
    qos_arraysize = 0;
    this->qos = 0;
    copy(other);
}

WMaxMacAddConn::~WMaxMacAddConn()
{
    delete [] this->qos;
}

WMaxMacAddConn& WMaxMacAddConn::operator=(const WMaxMacAddConn& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMacAddConn::copy(const WMaxMacAddConn& other)
{
    this->gateIndex = other.gateIndex;
    this->cid = other.cid;
    delete [] this->qos;
    this->qos = (other.qos_arraysize==0) ? nullptr : new WMaxQos[other.qos_arraysize];
    qos_arraysize = other.qos_arraysize;
    for (unsigned int i=0; i<qos_arraysize; i++)
        this->qos[i] = other.qos[i];
    this->dstAddr = other.dstAddr;
    this->macAddr = other.macAddr;
}

void WMaxMacAddConn::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->gateIndex);
    doParsimPacking(b,this->cid);
    b->pack(qos_arraysize);
    doParsimArrayPacking(b,this->qos,qos_arraysize);
    doParsimPacking(b,this->dstAddr);
    doParsimPacking(b,this->macAddr);
}

void WMaxMacAddConn::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->gateIndex);
    doParsimUnpacking(b,this->cid);
    delete [] this->qos;
    b->unpack(qos_arraysize);
    if (qos_arraysize==0) {
        this->qos = 0;
    } else {
        this->qos = new WMaxQos[qos_arraysize];
        doParsimArrayUnpacking(b,this->qos,qos_arraysize);
    }
    doParsimUnpacking(b,this->dstAddr);
    doParsimUnpacking(b,this->macAddr);
}

int WMaxMacAddConn::getGateIndex() const
{
    return this->gateIndex;
}

void WMaxMacAddConn::setGateIndex(int gateIndex)
{
    this->gateIndex = gateIndex;
}

int WMaxMacAddConn::getCid() const
{
    return this->cid;
}

void WMaxMacAddConn::setCid(int cid)
{
    this->cid = cid;
}

void WMaxMacAddConn::setQosArraySize(unsigned int size)
{
    WMaxQos *qos2 = (size==0) ? nullptr : new WMaxQos[size];
    unsigned int sz = qos_arraysize < size ? qos_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        qos2[i] = this->qos[i];
    qos_arraysize = size;
    delete [] this->qos;
    this->qos = qos2;
}

unsigned int WMaxMacAddConn::getQosArraySize() const
{
    return qos_arraysize;
}

WMaxQos& WMaxMacAddConn::getQos(unsigned int k)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    return this->qos[k];
}

void WMaxMacAddConn::setQos(unsigned int k, const WMaxQos& qos)
{
    if (k>=qos_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", qos_arraysize, k);
    this->qos[k] = qos;
}

IPv6Address& WMaxMacAddConn::getDstAddr()
{
    return this->dstAddr;
}

void WMaxMacAddConn::setDstAddr(const IPv6Address& dstAddr)
{
    this->dstAddr = dstAddr;
}

uint64_t WMaxMacAddConn::getMacAddr() const
{
    return this->macAddr;
}

void WMaxMacAddConn::setMacAddr(uint64_t macAddr)
{
    this->macAddr = macAddr;
}

class WMaxMacAddConnDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMacAddConnDescriptor();
    virtual ~WMaxMacAddConnDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMacAddConnDescriptor)

WMaxMacAddConnDescriptor::WMaxMacAddConnDescriptor() : omnetpp::cClassDescriptor("WMaxMacAddConn", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMacAddConnDescriptor::~WMaxMacAddConnDescriptor()
{
    delete[] propertynames;
}

bool WMaxMacAddConnDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMacAddConn *>(obj)!=nullptr;
}

const char **WMaxMacAddConnDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMacAddConnDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMacAddConnDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int WMaxMacAddConnDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMacAddConnDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "gateIndex",
        "cid",
        "qos",
        "dstAddr",
        "macAddr",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int WMaxMacAddConnDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "gateIndex")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cid")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "qos")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstAddr")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "macAddr")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMacAddConnDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "WMaxQos",
        "IPv6Address",
        "uint64_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMacAddConnDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMacAddConnDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMacAddConnDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddConn *pp = (WMaxMacAddConn *)object; (void)pp;
    switch (field) {
        case 2: return pp->getQosArraySize();
        default: return 0;
    }
}

const char *WMaxMacAddConnDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddConn *pp = (WMaxMacAddConn *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMacAddConnDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddConn *pp = (WMaxMacAddConn *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getGateIndex());
        case 1: return long2string(pp->getCid());
        case 2: {std::stringstream out; out << pp->getQos(i); return out.str();}
        case 3: {std::stringstream out; out << pp->getDstAddr(); return out.str();}
        case 4: return uint642string(pp->getMacAddr());
        default: return "";
    }
}

bool WMaxMacAddConnDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddConn *pp = (WMaxMacAddConn *)object; (void)pp;
    switch (field) {
        case 0: pp->setGateIndex(string2long(value)); return true;
        case 1: pp->setCid(string2long(value)); return true;
        case 4: pp->setMacAddr(string2uint64(value)); return true;
        default: return false;
    }
}

const char *WMaxMacAddConnDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(WMaxQos));
        case 3: return omnetpp::opp_typename(typeid(IPv6Address));
        default: return nullptr;
    };
}

void *WMaxMacAddConnDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddConn *pp = (WMaxMacAddConn *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getQos(i)); break;
        case 3: return (void *)(&pp->getDstAddr()); break;
        default: return nullptr;
    }
}

Register_Class(WMaxMacAddMngmntConn)

WMaxMacAddMngmntConn::WMaxMacAddMngmntConn(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->cid = 0;
}

WMaxMacAddMngmntConn::WMaxMacAddMngmntConn(const WMaxMacAddMngmntConn& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMacAddMngmntConn::~WMaxMacAddMngmntConn()
{
}

WMaxMacAddMngmntConn& WMaxMacAddMngmntConn::operator=(const WMaxMacAddMngmntConn& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMacAddMngmntConn::copy(const WMaxMacAddMngmntConn& other)
{
    this->cid = other.cid;
}

void WMaxMacAddMngmntConn::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->cid);
}

void WMaxMacAddMngmntConn::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->cid);
}

int WMaxMacAddMngmntConn::getCid() const
{
    return this->cid;
}

void WMaxMacAddMngmntConn::setCid(int cid)
{
    this->cid = cid;
}

class WMaxMacAddMngmntConnDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMacAddMngmntConnDescriptor();
    virtual ~WMaxMacAddMngmntConnDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMacAddMngmntConnDescriptor)

WMaxMacAddMngmntConnDescriptor::WMaxMacAddMngmntConnDescriptor() : omnetpp::cClassDescriptor("WMaxMacAddMngmntConn", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMacAddMngmntConnDescriptor::~WMaxMacAddMngmntConnDescriptor()
{
    delete[] propertynames;
}

bool WMaxMacAddMngmntConnDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMacAddMngmntConn *>(obj)!=nullptr;
}

const char **WMaxMacAddMngmntConnDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMacAddMngmntConnDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMacAddMngmntConnDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxMacAddMngmntConnDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxMacAddMngmntConnDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cid",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxMacAddMngmntConnDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cid")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMacAddMngmntConnDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxMacAddMngmntConnDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMacAddMngmntConnDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMacAddMngmntConnDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddMngmntConn *pp = (WMaxMacAddMngmntConn *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMacAddMngmntConnDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddMngmntConn *pp = (WMaxMacAddMngmntConn *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMacAddMngmntConnDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddMngmntConn *pp = (WMaxMacAddMngmntConn *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCid());
        default: return "";
    }
}

bool WMaxMacAddMngmntConnDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddMngmntConn *pp = (WMaxMacAddMngmntConn *)object; (void)pp;
    switch (field) {
        case 0: pp->setCid(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxMacAddMngmntConnDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxMacAddMngmntConnDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacAddMngmntConn *pp = (WMaxMacAddMngmntConn *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxEvent_DelConn)

WMaxEvent_DelConn::WMaxEvent_DelConn(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->cid = 0;
    this->isBasic = false;
}

WMaxEvent_DelConn::WMaxEvent_DelConn(const WMaxEvent_DelConn& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxEvent_DelConn::~WMaxEvent_DelConn()
{
}

WMaxEvent_DelConn& WMaxEvent_DelConn::operator=(const WMaxEvent_DelConn& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxEvent_DelConn::copy(const WMaxEvent_DelConn& other)
{
    this->cid = other.cid;
    this->isBasic = other.isBasic;
}

void WMaxEvent_DelConn::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->cid);
    doParsimPacking(b,this->isBasic);
}

void WMaxEvent_DelConn::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->cid);
    doParsimUnpacking(b,this->isBasic);
}

int WMaxEvent_DelConn::getCid() const
{
    return this->cid;
}

void WMaxEvent_DelConn::setCid(int cid)
{
    this->cid = cid;
}

bool WMaxEvent_DelConn::getIsBasic() const
{
    return this->isBasic;
}

void WMaxEvent_DelConn::setIsBasic(bool isBasic)
{
    this->isBasic = isBasic;
}

class WMaxEvent_DelConnDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxEvent_DelConnDescriptor();
    virtual ~WMaxEvent_DelConnDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxEvent_DelConnDescriptor)

WMaxEvent_DelConnDescriptor::WMaxEvent_DelConnDescriptor() : omnetpp::cClassDescriptor("WMaxEvent_DelConn", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxEvent_DelConnDescriptor::~WMaxEvent_DelConnDescriptor()
{
    delete[] propertynames;
}

bool WMaxEvent_DelConnDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxEvent_DelConn *>(obj)!=nullptr;
}

const char **WMaxEvent_DelConnDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxEvent_DelConnDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxEvent_DelConnDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int WMaxEvent_DelConnDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *WMaxEvent_DelConnDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cid",
        "isBasic",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int WMaxEvent_DelConnDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cid")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isBasic")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxEvent_DelConnDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxEvent_DelConnDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxEvent_DelConnDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxEvent_DelConnDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_DelConn *pp = (WMaxEvent_DelConn *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxEvent_DelConnDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_DelConn *pp = (WMaxEvent_DelConn *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxEvent_DelConnDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_DelConn *pp = (WMaxEvent_DelConn *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCid());
        case 1: return bool2string(pp->getIsBasic());
        default: return "";
    }
}

bool WMaxEvent_DelConnDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_DelConn *pp = (WMaxEvent_DelConn *)object; (void)pp;
    switch (field) {
        case 0: pp->setCid(string2long(value)); return true;
        case 1: pp->setIsBasic(string2bool(value)); return true;
        default: return false;
    }
}

const char *WMaxEvent_DelConnDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxEvent_DelConnDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_DelConn *pp = (WMaxEvent_DelConn *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxEvent_FlowEnable)

WMaxEvent_FlowEnable::WMaxEvent_FlowEnable(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxEvent_FlowEnable::WMaxEvent_FlowEnable(const WMaxEvent_FlowEnable& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxEvent_FlowEnable::~WMaxEvent_FlowEnable()
{
}

WMaxEvent_FlowEnable& WMaxEvent_FlowEnable::operator=(const WMaxEvent_FlowEnable& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxEvent_FlowEnable::copy(const WMaxEvent_FlowEnable& other)
{
}

void WMaxEvent_FlowEnable::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxEvent_FlowEnable::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxEvent_FlowEnableDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxEvent_FlowEnableDescriptor();
    virtual ~WMaxEvent_FlowEnableDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxEvent_FlowEnableDescriptor)

WMaxEvent_FlowEnableDescriptor::WMaxEvent_FlowEnableDescriptor() : omnetpp::cClassDescriptor("WMaxEvent_FlowEnable", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxEvent_FlowEnableDescriptor::~WMaxEvent_FlowEnableDescriptor()
{
    delete[] propertynames;
}

bool WMaxEvent_FlowEnableDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxEvent_FlowEnable *>(obj)!=nullptr;
}

const char **WMaxEvent_FlowEnableDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxEvent_FlowEnableDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxEvent_FlowEnableDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxEvent_FlowEnableDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxEvent_FlowEnableDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxEvent_FlowEnableDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxEvent_FlowEnableDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxEvent_FlowEnableDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxEvent_FlowEnableDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxEvent_FlowEnableDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowEnable *pp = (WMaxEvent_FlowEnable *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxEvent_FlowEnableDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowEnable *pp = (WMaxEvent_FlowEnable *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxEvent_FlowEnableDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowEnable *pp = (WMaxEvent_FlowEnable *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxEvent_FlowEnableDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowEnable *pp = (WMaxEvent_FlowEnable *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxEvent_FlowEnableDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxEvent_FlowEnableDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowEnable *pp = (WMaxEvent_FlowEnable *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxEvent_FlowDisable)

WMaxEvent_FlowDisable::WMaxEvent_FlowDisable(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxEvent_FlowDisable::WMaxEvent_FlowDisable(const WMaxEvent_FlowDisable& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxEvent_FlowDisable::~WMaxEvent_FlowDisable()
{
}

WMaxEvent_FlowDisable& WMaxEvent_FlowDisable::operator=(const WMaxEvent_FlowDisable& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxEvent_FlowDisable::copy(const WMaxEvent_FlowDisable& other)
{
}

void WMaxEvent_FlowDisable::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxEvent_FlowDisable::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxEvent_FlowDisableDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxEvent_FlowDisableDescriptor();
    virtual ~WMaxEvent_FlowDisableDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxEvent_FlowDisableDescriptor)

WMaxEvent_FlowDisableDescriptor::WMaxEvent_FlowDisableDescriptor() : omnetpp::cClassDescriptor("WMaxEvent_FlowDisable", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxEvent_FlowDisableDescriptor::~WMaxEvent_FlowDisableDescriptor()
{
    delete[] propertynames;
}

bool WMaxEvent_FlowDisableDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxEvent_FlowDisable *>(obj)!=nullptr;
}

const char **WMaxEvent_FlowDisableDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxEvent_FlowDisableDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxEvent_FlowDisableDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxEvent_FlowDisableDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxEvent_FlowDisableDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxEvent_FlowDisableDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxEvent_FlowDisableDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxEvent_FlowDisableDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxEvent_FlowDisableDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxEvent_FlowDisableDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowDisable *pp = (WMaxEvent_FlowDisable *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxEvent_FlowDisableDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowDisable *pp = (WMaxEvent_FlowDisable *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxEvent_FlowDisableDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowDisable *pp = (WMaxEvent_FlowDisable *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxEvent_FlowDisableDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowDisable *pp = (WMaxEvent_FlowDisable *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxEvent_FlowDisableDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxEvent_FlowDisableDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxEvent_FlowDisable *pp = (WMaxEvent_FlowDisable *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxMacTerminateAllConns)

WMaxMacTerminateAllConns::WMaxMacTerminateAllConns(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxMacTerminateAllConns::WMaxMacTerminateAllConns(const WMaxMacTerminateAllConns& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxMacTerminateAllConns::~WMaxMacTerminateAllConns()
{
}

WMaxMacTerminateAllConns& WMaxMacTerminateAllConns::operator=(const WMaxMacTerminateAllConns& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxMacTerminateAllConns::copy(const WMaxMacTerminateAllConns& other)
{
}

void WMaxMacTerminateAllConns::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxMacTerminateAllConns::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxMacTerminateAllConnsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxMacTerminateAllConnsDescriptor();
    virtual ~WMaxMacTerminateAllConnsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxMacTerminateAllConnsDescriptor)

WMaxMacTerminateAllConnsDescriptor::WMaxMacTerminateAllConnsDescriptor() : omnetpp::cClassDescriptor("WMaxMacTerminateAllConns", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxMacTerminateAllConnsDescriptor::~WMaxMacTerminateAllConnsDescriptor()
{
    delete[] propertynames;
}

bool WMaxMacTerminateAllConnsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxMacTerminateAllConns *>(obj)!=nullptr;
}

const char **WMaxMacTerminateAllConnsDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxMacTerminateAllConnsDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxMacTerminateAllConnsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxMacTerminateAllConnsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxMacTerminateAllConnsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxMacTerminateAllConnsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxMacTerminateAllConnsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxMacTerminateAllConnsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxMacTerminateAllConnsDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxMacTerminateAllConnsDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxMacTerminateAllConns *pp = (WMaxMacTerminateAllConns *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxMacTerminateAllConnsDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacTerminateAllConns *pp = (WMaxMacTerminateAllConns *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxMacTerminateAllConnsDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacTerminateAllConns *pp = (WMaxMacTerminateAllConns *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxMacTerminateAllConnsDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxMacTerminateAllConns *pp = (WMaxMacTerminateAllConns *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxMacTerminateAllConnsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxMacTerminateAllConnsDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxMacTerminateAllConns *pp = (WMaxMacTerminateAllConns *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxHandoverNotify)

WMaxHandoverNotify::WMaxHandoverNotify(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->BS_index = 0;
}

WMaxHandoverNotify::WMaxHandoverNotify(const WMaxHandoverNotify& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxHandoverNotify::~WMaxHandoverNotify()
{
}

WMaxHandoverNotify& WMaxHandoverNotify::operator=(const WMaxHandoverNotify& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxHandoverNotify::copy(const WMaxHandoverNotify& other)
{
    this->BS_index = other.BS_index;
}

void WMaxHandoverNotify::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->BS_index);
}

void WMaxHandoverNotify::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->BS_index);
}

int WMaxHandoverNotify::getBS_index() const
{
    return this->BS_index;
}

void WMaxHandoverNotify::setBS_index(int BS_index)
{
    this->BS_index = BS_index;
}

class WMaxHandoverNotifyDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxHandoverNotifyDescriptor();
    virtual ~WMaxHandoverNotifyDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxHandoverNotifyDescriptor)

WMaxHandoverNotifyDescriptor::WMaxHandoverNotifyDescriptor() : omnetpp::cClassDescriptor("WMaxHandoverNotify", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxHandoverNotifyDescriptor::~WMaxHandoverNotifyDescriptor()
{
    delete[] propertynames;
}

bool WMaxHandoverNotifyDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxHandoverNotify *>(obj)!=nullptr;
}

const char **WMaxHandoverNotifyDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxHandoverNotifyDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxHandoverNotifyDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WMaxHandoverNotifyDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WMaxHandoverNotifyDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "BS_index",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WMaxHandoverNotifyDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='B' && strcmp(fieldName, "BS_index")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxHandoverNotifyDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WMaxHandoverNotifyDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxHandoverNotifyDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxHandoverNotifyDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotify *pp = (WMaxHandoverNotify *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxHandoverNotifyDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotify *pp = (WMaxHandoverNotify *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxHandoverNotifyDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotify *pp = (WMaxHandoverNotify *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getBS_index());
        default: return "";
    }
}

bool WMaxHandoverNotifyDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotify *pp = (WMaxHandoverNotify *)object; (void)pp;
    switch (field) {
        case 0: pp->setBS_index(string2long(value)); return true;
        default: return false;
    }
}

const char *WMaxHandoverNotifyDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WMaxHandoverNotifyDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotify *pp = (WMaxHandoverNotify *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WMaxHandoverNotifyAcknowledge)

WMaxHandoverNotifyAcknowledge::WMaxHandoverNotifyAcknowledge(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

WMaxHandoverNotifyAcknowledge::WMaxHandoverNotifyAcknowledge(const WMaxHandoverNotifyAcknowledge& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WMaxHandoverNotifyAcknowledge::~WMaxHandoverNotifyAcknowledge()
{
}

WMaxHandoverNotifyAcknowledge& WMaxHandoverNotifyAcknowledge::operator=(const WMaxHandoverNotifyAcknowledge& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WMaxHandoverNotifyAcknowledge::copy(const WMaxHandoverNotifyAcknowledge& other)
{
}

void WMaxHandoverNotifyAcknowledge::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void WMaxHandoverNotifyAcknowledge::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class WMaxHandoverNotifyAcknowledgeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WMaxHandoverNotifyAcknowledgeDescriptor();
    virtual ~WMaxHandoverNotifyAcknowledgeDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WMaxHandoverNotifyAcknowledgeDescriptor)

WMaxHandoverNotifyAcknowledgeDescriptor::WMaxHandoverNotifyAcknowledgeDescriptor() : omnetpp::cClassDescriptor("WMaxHandoverNotifyAcknowledge", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WMaxHandoverNotifyAcknowledgeDescriptor::~WMaxHandoverNotifyAcknowledgeDescriptor()
{
    delete[] propertynames;
}

bool WMaxHandoverNotifyAcknowledgeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WMaxHandoverNotifyAcknowledge *>(obj)!=nullptr;
}

const char **WMaxHandoverNotifyAcknowledgeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WMaxHandoverNotifyAcknowledgeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int WMaxHandoverNotifyAcknowledgeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int WMaxHandoverNotifyAcknowledgeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **WMaxHandoverNotifyAcknowledgeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WMaxHandoverNotifyAcknowledgeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotifyAcknowledge *pp = (WMaxHandoverNotifyAcknowledge *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotifyAcknowledge *pp = (WMaxHandoverNotifyAcknowledge *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WMaxHandoverNotifyAcknowledgeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotifyAcknowledge *pp = (WMaxHandoverNotifyAcknowledge *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool WMaxHandoverNotifyAcknowledgeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotifyAcknowledge *pp = (WMaxHandoverNotifyAcknowledge *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *WMaxHandoverNotifyAcknowledgeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WMaxHandoverNotifyAcknowledge *pp = (WMaxHandoverNotifyAcknowledge *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


