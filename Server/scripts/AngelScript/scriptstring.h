#ifndef SCRIPTSTRING_H
#define SCRIPTSTRING_H

#include "angelscript.h"
#include <string>

typedef unsigned int uint;

class ScriptString
{
public:
    #ifdef FONLINE_DLL
    static ScriptString& Create( const char* str = NULL )
    {
        static int    typeId = ASEngine->GetTypeIdByDecl( "string" );
        ScriptString* scriptStr = (ScriptString*) ASEngine->CreateScriptObject( typeId );
        if( str )
            scriptStr->assign( str );
        return *scriptStr;
    }
protected:
    #endif

    ScriptString();
    ScriptString( const ScriptString& other );
    ScriptString( const char* s, uint len );
    ScriptString( const char* s );
    ScriptString( const std::string& s );

public:
    virtual ~ScriptString();

    virtual void AddRef() const;
    virtual void Release() const;

    ScriptString& operator=( const ScriptString& other )
    {
        assign( other.c_str(), other.length() );
        return *this;
    }
    ScriptString& operator+=( const ScriptString& other )
    {
        append( other.c_str(), other.length() );
        return *this;
    }
    ScriptString& operator=( const std::string& other )
    {
        assign( other.c_str(), other.length() );
        return *this;
    }
    ScriptString& operator+=( const std::string& other )
    {
        append( other.c_str(), other.length() );
        return *this;
    }
    ScriptString& operator=( const char* other )
    {
        assign( other );
        return *this;
    }
    ScriptString& operator+=( const char* other )
    {
        append( other );
        return *this;
    }

    virtual void assign( const char* buf, uint count );
    virtual void assign( const char* buf );
    virtual void append( const char* buf, uint count );
    virtual void append( const char* buf );
    virtual void reserve( uint count );
    virtual void rawResize( uint count );
    virtual uint lengthUTF8() const;
    virtual bool indexByteToUTF8( int& index, uint* length = NULL, uint offset = 0 );

    const char*        c_str()     const { return buffer.c_str(); }
    uint               length()    const { return buffer.length(); }
    uint               capacity()  const { return buffer.capacity(); }
    const std::string& c_std_str() const { return buffer; }
    int                rcount()    const { return refCount; }

    char rawGet( uint index )
    {
        return index < buffer.length() ? buffer[ index ] : 0;
    }
    void rawSet( uint index, char value )
    {
        if( index < buffer.length() )
            buffer[ index ] = value;
    }

protected:
    std::string buffer;
    mutable int refCount;
};

#ifndef FONLINE_DLL
void RegisterScriptString( asIScriptEngine* engine );
#endif

#endif // SCRIPTSTRING_H
