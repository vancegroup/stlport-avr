// -*- C++ -*- Time-stamp: <09/06/06 00:28:50 ptr>

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

#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include <cassert>

#include <misc/opts.h>

using namespace std;

int option_base::_count = 0;

string option_base::_parname( const char* def ) const
{
  string::size_type p[2];

  p[0] = desc.find( '<' );

  if ( p[0] != string::npos ) {
    p[1] = desc.find( '>', p[0] );
  }

  string sample( def );

  if ( (p[0] != string::npos) && (p[1] != string::npos) ) {
    sample = desc.substr( p[0], p[1] - p[0] + 1 );
  }

  return sample;
}

std::ostream& option<string>::_describe( std::ostream& out ) const
{
  string sample( option_base::_parname( "<string>" ) );

  if ( option_base::shortname != 0 ) {
    out << '-' << option_base::shortname << ' ' << sample;
    if ( !option_base::longname.empty() ) {
      out << ", ";
    }
  }
        
  if ( !option_base::longname.empty() ) {
    out << "--" << option_base::longname << '=' << sample;
  }

  return out << '\t' << option_base::desc << " [" <<  default_arg << ']';
}

std::ostream& option<char*>::_describe( std::ostream& out ) const
{
  string sample( option_base::_parname( "<string>" ) );

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

std::ostream& option<void>::_describe( std::ostream& out ) const
{
  if ( option_base::shortname != 0 ) {
    out << '-' << option_base::shortname;
    if ( !option_base::longname.empty() ) {
      out << ", ";
    }
  }
        
  if ( !option_base::longname.empty() ) {
    out << "--" << option_base::longname << '\t';
  }

  return out << option_base::desc;
}

string Opts::get_pname() const { return pname; }

bool Opts::is_opt_name(const string& s)
{
  return (s.size() > 1) && (s[0] == '-') && !is_flag_group(s);
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
    options_container_type::const_iterator res = storage.end();
    string tmp = s.substr(2);
    bool ambiguous = false;

    for ( options_container_type::const_iterator i = storage.begin(); i != storage.end(); ++i ) {
      if ( (*i)->longname.find(tmp) == 0 ) {
        if ( (*i)->longname.size() == tmp.size() ) { // i.e. longname == tmp
          return i; // precise match; return it even if ambiguous
        }
        if ( res == storage.end() ) { // first match
          res = i;
        } else {
          ambiguous = true;
        }
      }
    }

    return ambiguous ? storage.end() : res;
  }
    
  return storage.end();
}

void Opts::help( ostream& out )
{
  out << "\nThis is " << pname;
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

  out << "Usage:\n\n  " << pname << " " << _usage << "\n"; // " [options] etc. etc."

  if ( !storage.empty() ) {
    out << "\nAvailable options:\n\n";

    for ( options_container_type::const_iterator i = storage.begin(); i != storage.end(); ++i) {
      out << "  ";
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

      if ( (*p)->type() != typeid(void) ) {
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
        if ( (*p)->type() != typeid(void) ) {
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
