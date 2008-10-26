// -*- C++ -*- Time-stamp: <08/10/01 10:12:43 ptr>

/*
 * Copyright (c) 2008
 * Dmitry Osmakov
 *
 * Copyright (c) 1997-1998, 2001, 2008
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include <cassert>

#include <misc/opts.h>

using namespace std;

int option_base::_count = 0;

std::ostream& option<string>::_describe( std::ostream& out ) const
{
  if ( option_base::shortname != 0 ) {
    out << '-' << option_base::shortname << " <string>";
    if ( !option_base::longname.empty() ) {
      out << ", ";
    }
  }
        
  if ( !option_base::longname.empty() ) {
    out << "--" << option_base::longname << "=<string>";
  }

  if ( option_base::has_arg ) {
    out << " [" << args.front() << "]\t";
  } else {
    out << '\t';
  }

  return out << option_base::desc;
}

std::ostream& option<char*>::_describe( std::ostream& out ) const
{
  if ( option_base::shortname != 0 ) {
    out << '-' << option_base::shortname << " <string>";
    if ( !option_base::longname.empty() ) {
      out << ", ";
    }
  }
        
  if ( !option_base::longname.empty() ) {
    out << "--" << option_base::longname << "=<string>";
  }

  if ( option_base::has_arg ) {
    out << " [" << args.front() << "]\t";
  } else {
    out << '\t';
  }

  return out << option_base::desc;
}

bool Opts::is_set( char field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,char>(), field ) );

  return ( (i == storage.end()) ? false : !(*i)->pos.empty());
}

bool Opts::is_set( const std::string& field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,std::string>(), field ) );

  return ( (i == storage.end()) ? false : !(*i)->pos.empty());
}

bool Opts::is_set( int field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,int>(), field ) );

  return ( (i == storage.end()) ? false : !(*i)->pos.empty());
}

int Opts::get_cnt( char field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,char>(), field ) );

  return ( (i == storage.end()) ? 0 : (*i)->pos.size());
}

int Opts::get_cnt( const std::string& field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,std::string>(), field ) );

  return ( (i == storage.end()) ? 0 : (*i)->pos.size());
}

int Opts::get_cnt( int field ) const
{
  options_container_type::const_iterator i = 
    std::find_if( storage.begin(), storage.end(),
                  std::bind2nd( ::detail::deref_equal<option_base*,int>(), field ) );

  return ( (i == storage.end()) ? 0 : (*i)->pos.size());
}

string Opts::get_pname() const { return pname; }

bool Opts::is_opt_name(const string& s)
{
  return (s.size() > 1) && (s[0] == '-') && !is_flag_group(s);
}

bool Opts::is_substr( const string& small, const string& big ) const
{
  if ( small.size() > big.size() ) {
    return false;
  }

  string::const_iterator i = small.begin();
  string::const_iterator j = big.begin();
  for ( ; i != small.end(); ++i, ++j ) {
    if ( *i != *j ) {
      return false;
    }
  }

  return true;
}

bool Opts::is_flag_group( const string& s )
{
  string::const_iterator i = s.begin();

  if ( s.size() > 2 && *i == '-' ) {
    while ( ++i != s.end() ) {
      if ( !isalnum( *i ) ) {
        return false;
      }
    }
    return true;
  }
  return false;
}

// this function assumes that is_opt_name(s) = true;
Opts::options_container_type::const_iterator Opts::get_opt_index( const string& s) const
{
  // assert(is_opt_name(s));
  if (s.size() == 2 && isalnum(s[1]) ) { // is short name
    options_container_type::const_iterator i = storage.begin();
    for ( ; i != storage.end(); ++i ) {
      if ( (*i)->shortname == s[1]) {
        break;
      }
    }
    return i;
  }
  
  if (s.size() > 2 && s[1] == '-') {
    options_container_type::const_iterator i;
    string tmp = s.substr(2);

    // exact match
    for ( i = storage.begin(); i != storage.end(); ++i ) {
      if ( (*i)->longname == tmp ) {
        return i;
      }
    }

    vector< options_container_type::const_iterator > matches;
    for ( i = storage.begin();i != storage.end();++i ) {
      if ( is_substr( tmp, (*i)->longname ) ) {
        matches.push_back(i);
      }
    }

    return matches.size() == 1 ? matches[0] : storage.end();
  }
    
  return storage.end();
}

void Opts::help( ostream& out )
{
  out << "This is " << pname;
  if ( !_brief.empty() ) {
    out << ", " << _brief;
  }
  out << "\n\n";

  if ( !_author.empty() ) {
    out << _author << "\n\n";
  }

  if ( !_copyright.empty() ) {
    out << _copyright << "\n\n";
  }  

  out << "Usage:\n\n" << pname << " " << _usage << "\n"; // " [options] etc. etc."

  if ( !storage.empty() ) {
    out << "\nOptions:\n\n";

    for ( options_container_type::const_iterator i = storage.begin(); i != storage.end(); ++i) {
      (*i)->_describe( out ) << '\n';
    }
  }
  out << endl;
}

void Opts::parse( int& ac, const char** av )
{
  pname = av[0];

  int i = 1;
  int j = 1;
  int q = 0;

  while ( (i < ac) && (string(av[i]) != "--") ) {
    if ( is_opt_name(av[i]) ) {
      string opt = av[i];
      string arg;
      
      string::size_type k = opt.find( "=" );

      if ( k != string::npos ) {
        arg = opt.substr( k + 1 );
        opt = opt.substr( 0, k );
      }

      options_container_type::const_iterator p = get_opt_index(opt);
      
      if ( p == storage.end() ) {
        throw unknown_option(opt);
      }

      if ( (*p)->has_arg ) {
        if ( !arg.empty() ) {
          (*p)->read(arg);
        } else {
          if ( (i + 1) >= ac ) {
            throw missing_arg(opt);
          }
          (*p)->read( av[++i] );
        }
      } else if ( !arg.empty() ) { //unexpected arg (not exactly mismatch)
        throw arg_typemismatch(opt,arg);
      }
      (*p)->pos.push_back(++q);
    } else if ( is_flag_group(av[i]) ) {
      string optgroup = av[i];
      for ( int j = 1; j < optgroup.size(); j++ ) {
        options_container_type::const_iterator p = get_opt_index(string("-") + optgroup[j]);
        if ( p == storage.end() ) {
          throw unknown_option( "-" + string(1,optgroup[j]) );
        }
        (*p)->pos.push_back(++q);
        if ( (*p)->has_arg ) {
          throw missing_arg( "-" + string(1,optgroup[j]) );
        }
      }
    } else {
      av[j++] = av[i];
    }
    i++;
  }
  
  i += ( i < ac );

  while (i < ac) {
    av[j++] = av[i++];
  }
  ac = j;
}
