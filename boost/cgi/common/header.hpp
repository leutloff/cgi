//                   -- header.hpp --
//
//           Copyright (c) Darren Garvey 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_HEADER_HPP_INCLUDED__
#define CGI_HEADER_HPP_INCLUDED__

#include <string>
#include <boost/lexical_cast.hpp>

namespace cgi {
 namespace common {

  // **FIXME** (could include response_fwd.hpp really)...
  template<typename CharT> class basic_response;

  template<typename CharT>
  struct basic_header
  {
    typedef CharT                             char_type;
    typedef typename std::basic_string<CharT> string_type;
    
    basic_header()
      : content()
    {
    }

    basic_header(const string_type& _content)
      : content(_content)
    {
    }

    basic_header(const string_type& name, const string_type& val)
      : content(name + ": " + val)
    {
    }

    /// Construct an header from a cookie.
    basic_header(const basic_cookie<char_type>& ck)
      : content("Set-cookie: " + ck.to_string())
    {
    }

    string_type content;
  };

/*
  template<typename StringT>
  header<StringT>
    make_header(const StringT& name, const StringT& val)
  {
    return basic_header<StringT>(name, val);
  }* /

  template<typename T, typename StringT>
  T make_header(const StringT& name, const StringT& val)
  {
    return basic_header<StringT>(name, val);
  }*/


  //{ Some shortcuts, to cut down on typing errors.
  template<typename CharT, typename StringT> basic_header<CharT>
    content_type(StringT const& str)
  {
    return basic_header<CharT>("Content-type", str);
  }

  template<typename CharT> basic_header<CharT>
    content_type(const CharT* str)
  {
    return basic_header<CharT>("Content-type", str);
  }

  template<typename CharT> basic_header<CharT>
    content_encoding(std::basic_string<CharT> const& str)
  {
    return basic_header<CharT>("Content-encoding", str);
  }

  template<typename CharT, typename T> basic_header<CharT>
    content_length(const T& t)
  {
    return basic_header<CharT>("Content-length",
             boost::lexical_cast<std::basic_string<CharT> >(t));
  }

  template<typename CharT, typename T> basic_header<CharT>
    content_length(T t)
  {
    return basic_header<CharT>("Content-length",
             boost::lexical_cast<std::basic_string<CharT> >(t));
  }

  template<typename CharT> basic_header<CharT>
    content_length(std::basic_string<CharT> const& str)
  {
    return basic_header<CharT>("Content-length", str);
  }

  template<typename CharT> basic_header<CharT>
    content_length(basic_response<CharT>& resp)
  {
    return basic_header<CharT>("Content-length",
               boost::lexical_cast<std::string>(resp.content_length()));
  }

  template<typename CharT> basic_header<CharT>
    location(const CharT* url)
  {
    return basic_header<CharT>("Location", url);
  }

  template<typename CharT> basic_header<CharT>
    location(std::basic_string<CharT> const& url)
  {
    return basic_header<CharT>("Location", url);
  }

  template<typename CharT, typename U> basic_header<CharT>
    location(U const& url)
  {
    return basic_header<CharT>("Location", url);
  }
  //}

  // typedefs for typical usage
  typedef basic_header<char>    header;
  typedef basic_header<wchar_t> wheader;

 } // namespace common
} // namespace cgi

#endif // CGI_HEADER_HPP_INCLUDED__

