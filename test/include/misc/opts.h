// -*- C++ -*- Time-stamp: <09/01/12 00:33:30 ptr>

/*
 * Copyright (c) 2008, 2009
 * Dmitry Osmakov
 *
 * Copyright (c) 1997-1998, 2001, 2008, 2009
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __OPTS_H__
#define __OPTS_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <typeinfo>
#include <cctype>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>

class option_base
{
  public:

    option_base( const char* _description, char _short_var, const char* _long_var ) :
        shortname( _short_var ),
        longname( _long_var ),
        desc( _description ),
        token( _count++ )
      { }

    option_base( const char* _description, char _short_var ) :
        shortname( _short_var ),
        longname(),
        desc( _description ),
        token( _count++ )
      { }

    option_base( const char* _description, const char* _long_var ) :
        shortname( 0 ),
        longname( _long_var ),
        desc( _description ),
        token( _count++ )
      { }

    virtual ~option_base()
      { }

    bool operator ==( const std::string& _longname ) const
      { return longname == _longname; }
    bool operator ==( char _shortname ) const
      { return shortname == _shortname; }
    bool operator ==( int _token ) const
      { return token == _token; } 

    virtual const std::type_info& type() const = 0;

    template <class T>
    bool assign( T& v ) const
      {
        if ( this->type() != typeid(T) ) {
          throw std::invalid_argument( "types mismatch" );
        }
        return _assign( static_cast<void*>(&v) );
      }

  protected:
    virtual void read( const char* str ) = 0;
    virtual void read( const std::string& str ) = 0;
    virtual bool _assign( void* ) const = 0;
    virtual std::ostream& _describe( std::ostream& ) const = 0;

    std::string _parname( const char* ) const;

    char shortname;
    std::string longname;
    std::string desc;
    int token;

  protected:    
    std::vector<int> pos;

    friend class Opts;

  private:
    static int _count;
};

namespace detail {

template <class P, class V>
class deref_equal :
    public std::binary_function<P,V,bool>
{
  public:
    bool operator()(const P& __x, const V& __y) const
      { return *__x == __y; }
};

inline void option_base_destroyer( option_base* p )
{ delete p; }

} // namespace detail

template <class T>
class option :
    public option_base
{
  public:
    option( const char* _description, char _short_var, const char* _long_var ) :
        option_base( _description, _short_var, _long_var )
      { 
        args.push_back(T());
        default_arg = T();
      }

    option( const char* _description, char _short_var ) :
        option_base( _description, _short_var )
      { 
        args.push_back(T());
        default_arg = T();
      }

    option( const char* _description, const char* _long_var ) :
        option_base( _description, _long_var )
      { 
        args.push_back(T());
        default_arg = T();
      }

    virtual const std::type_info& type() const
      { return typeid( T ); }

    option<T>& operator []( const T& val )
      { 
        args.push_back(val);
        default_arg = val;
        return *this;
      }

    template <class BackInstertIterator>
    void get( BackInstertIterator bi ) const
      { std::copy( args.begin(), args.end(), bi ); }

  protected:
    virtual std::ostream& _describe( std::ostream& o ) const;

    virtual bool _assign( void* v ) const
      {
        *reinterpret_cast<T*>(v) = args.back();
        
        return !pos.empty();
      }

  private:
    std::list<T> args;
    T default_arg;

    void read( const char *str ) throw (std::invalid_argument)
      {
        std::istringstream s( str );
        T _v;
        if ( !(s >> _v).fail() ) {
          args.push_back( _v );
        } else {
          throw std::invalid_argument( str );
        }
      }

    void read( const std::string& str ) throw (std::invalid_argument)
      {
        std::istringstream s( str );
        T _v;
        if ( !(s >> _v).fail() ) {
          args.push_back( _v );
        } else {
          throw std::invalid_argument( str );
        }
      }

    friend class Opts;
};

template <class T>
std::ostream& option<T>::_describe( std::ostream& out ) const
{
  std::string def( "<" );
  def += typeid(T).name();
  def += '>';

  std::string sample( option_base::_parname( def.c_str() ) );

  if ( option_base::shortname != 0 ) {
    out << '-' << option_base::shortname << ' ' << sample;
    if ( !option_base::longname.empty() ) {
      out << ", ";
    }
  }
        
  if ( !option_base::longname.empty() ) {
    out << "--" << option_base::longname << '=' << sample;
  }
  
  return out << '\t' << option_base::desc << " [" << default_arg << ']';
}

template <>
class option<std::string> :
    public option_base
{
  public:
    option( const char* _description, char _short_var, const char* _long_var ) :
        option_base( _description, _short_var, _long_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    option( const char* _description, char _short_var ) :
        option_base( _description, _short_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    option( const char* _description, const char* _long_var ) :
        option_base( _description, _long_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    virtual const std::type_info& type() const
      { return typeid( std::string ); }

    option<std::string>& operator []( const char* val )
      { 
        args.push_back( std::string(val) );
        default_arg = val;
        return *this;
      }

    option<std::string>& operator []( const std::string& val )
      { 
        args.push_back( val );
        default_arg = val;
        return *this;
      }

    template <class BackInstertIterator>
    void get( BackInstertIterator bi ) const
      { std::copy( args.begin(), args.end(), bi ); }

  protected:
    virtual std::ostream& _describe( std::ostream& o ) const;

    virtual bool _assign( void* v ) const
      {
        *reinterpret_cast<std::string*>(v) = args.back();
        
        return !pos.empty();
      }

  private:
    std::list<std::string> args;
    std::string default_arg;

    void read( const char *str )
      {
        args.push_back( std::string( str ) );
      }

    void read( const std::string& str )
      {
        args.push_back( str );
      }

    friend class Opts;
};

template <>
class option<char*> :
    public option_base
{
  public:
    option( const char* _description, char _short_var, const char* _long_var ) :
        option_base( _description, _short_var, _long_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    option( const char* _description, char _short_var ) :
        option_base( _description, _short_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    option( const char* _description, const char* _long_var ) :
        option_base( _description, _long_var )
      { 
        args.push_back( std::string() );
        default_arg = std::string();
      }

    virtual const std::type_info& type() const
      { return typeid( std::string ); }

    option<char*>& operator []( const char* val )
      { 
        args.push_back( std::string(val) );
        default_arg = val;
        return *this;
      }

    option<char*>& operator []( const std::string& val )
      { 
        args.push_back( val );
        default_arg = val;
        return *this;
      }

    template <class BackInstertIterator>
    void get( BackInstertIterator bi ) const
      { std::copy( args.begin(), args.end(), bi ); }

  protected:
    virtual std::ostream& _describe( std::ostream& o ) const;

    virtual bool _assign( void* v ) const
      {
        *reinterpret_cast<std::string*>(v) = args.back();
        
        return !pos.empty();
      }

  private:
    std::list<std::string> args;
    std::string default_arg;

    void read( const char *str )
      {
        args.push_back( std::string( str ) );
      }

    void read( const std::string& str )
      {
        args.push_back( str );
      }

    friend class Opts;
};

template <>
class option<void> :
    public option_base
{
  public:
    option( const char* _description, char _short_var, const char* _long_var ) :
        option_base( _description, _short_var, _long_var )
      { }

    option( const char* _description, char _short_var ) :
        option_base( _description, _short_var )
      { }

    option( const char* _description, const char* _long_var ) :
        option_base( _description, _long_var )
      { }

    virtual const std::type_info& type() const
      { return typeid( void ); }

  protected:
    virtual std::ostream& _describe( std::ostream& o ) const;
    
    virtual bool _assign( void* v ) const
      {
        throw std::logic_error("using option::assign for option without arguments");
      }

  private:

    void read( const char *str )
      {
        throw std::logic_error("using option::read for option without arguments");
      }

    void read( const std::string& str )
      {
        throw std::logic_error("using option::read for option without arguments");
      }

    friend class Opts;
};

class Opts
{
  private:
    typedef std::vector< option_base* > options_container_type;
    options_container_type storage;

  public:
    Opts()
      { }

    ~Opts()
      { std::for_each( storage.begin(), storage.end(), detail::option_base_destroyer ); }

    void description( const char* text )
      { _brief = text; }

    void usage( const char* text )
      { _usage = text; }

    void author( const char* text )
      { _author = text; }

    void copyright( const char* text )
      { _copyright = text; }


    template <class T>
    Opts& operator << ( const option<T>& o )
      {
        storage.push_back( new option<T>( o ) );
        return *this;
      }

    // getting option
    template <class T, class V>
    T get( const V& field );
    
    template <class T>
    T get( const char* field )
      { return get<T,std::string>(std::string(field)); };

    template <class BackInsertIterator, class V>
    void getemall( const V& field , BackInsertIterator bi );
    
    template <class BackInsertIterator>
    void getemall( const char* field , BackInsertIterator bi )
      { getemall<BackInsertIterator, std::string>( std::string(field), bi ); }
    
    template <class V>
    bool is_set( const V& field ) const;
    
    bool is_set( const char* field ) const
      { return is_set( std::string(field) ); }
      
    template <class V>
    int get_cnt( const V& field ) const;
    
    int get_cnt( const char* field ) const
      { return get_cnt( std::string(field) ); }

    template <class BackInsertIterator, class V>
    void get_pos( const V& field, BackInsertIterator bi);
    
    template <class BackInsertIterator>
    void get_pos( const char* field, BackInsertIterator bi)
      { get_pos<BackInsertIterator,std::string>(std::string(field),bi); }


    // parse
    void parse(int& ac, const char** av);

    // stuff
    void help(std::ostream& out);
    std::string get_pname() const;

    // error handling
    struct unknown_option :
        public std::invalid_argument
    {
        unknown_option( const std::string& _optname ) :
            std::invalid_argument( std::string("unknown option ").append(_optname) )
          { }
    };
  
    struct missing_arg :
        public std::invalid_argument
    {
        missing_arg( const std::string& _optname ) :
            std::invalid_argument( std::string("missing argument for option ").append(_optname) )
          { }
    };

    struct arg_typemismatch :
        public std::invalid_argument
    {
        arg_typemismatch( const std::string& _optname, const std::string& _argname) :
            std::invalid_argument(std::string("argument [").append(_argname).append("] doesn't match by type for option ").append(_optname))
          { }
    };

    int last_token() const
      { return storage.empty() ? -1 : storage.back()->token; }

  private:
    std::string pname;
    std::string _brief;
    std::string _usage;
    std::string _author;
    std::string _copyright;

    bool isterm( const std::string& s );
    bool is_opt_name( const std::string& s );
    bool is_flag_group( const std::string& s );
    options_container_type::const_iterator get_opt_index( const std::string& s ) const;
};


template < class T , class V >
T Opts::get( const V& field )
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( detail::deref_equal<option_base*,V>(), field ) );

  if ( i == storage.end() ) {
    std::stringstream ss1;
    ss1 << field;
    throw unknown_option( ss1.str() );
  }

  T res;

  (*i)->assign( res );

  return res;
}

template <class BackInsertIterator, class V>
void Opts::getemall( const V& field, BackInsertIterator bi )
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( detail::deref_equal<option_base*,V>(), field ) );

  if ( i == storage.end() ) {
    std::stringstream ss1;
    ss1 << field;
    throw unknown_option(ss1.str());
  }

  if ((*i)->type() != typeid(void)) {
    typedef typename BackInsertIterator::container_type::value_type real_type;
    
    option<real_type>* opt = dynamic_cast< option<real_type> * >( *i );
    opt->get( bi );
  } else {
    throw std::logic_error("using Opts::getemall with flag option");
  }
}

template <class V>
bool Opts::is_set( const V& field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,V>(), field ) );

  return ( (i == storage.end()) ? false : !(*i)->pos.empty());
}

template <class V>
int Opts::get_cnt( const V& field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,V>(), field ) );

  return ( (i == storage.end()) ? 0 : (*i)->pos.size());
}

template <class BackInsertIterator, class V >
void Opts::get_pos( const V& field , BackInsertIterator bi )
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( detail::deref_equal<option_base*,V>(), field ) );

  if ( i == storage.end() ) {
    std::stringstream ss1;
    ss1 << field;
    throw unknown_option(ss1.str());
  }

  std::copy( (*i)->pos.begin(), (*i)->pos.end(), bi );
}


#endif // __OPTS_H__
