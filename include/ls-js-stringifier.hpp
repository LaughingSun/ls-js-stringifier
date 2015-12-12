#ifndef LS_JS_STRINGIFIER_HPP
#define LS_JS_STRINGIFIER_HPP

/*  Copyright (c) <2015> <Erich Horn and LaughingSun>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
 */

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <exception>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace ls
{

  namespace js
  {
    
    template <class JSO>
    class Stringifier
    {

public:
      
#ifndef STRINGIFIER_LINE_WIDTH
#define STRINGIFIER_LINE_WIDTH 80
#endif  // STRINGIFIER_LINE_WIDTH

#define STRINGIFIER_INDENT_BITS 10
#define STRINGIFIER_FLAG_BITS 10

#ifndef STRINGIFIER_INDENT
#define STRINGIFIER_INDENT(a) ((((1 << STRINGIFIER_INDENT_BITS) - 1) & a) \
    | ls::js::Stringifier::flag_pretty)
#endif  // STRINGIFIER_INDENT
      
      typedef enum stringifier_flags<size_t> {
      
        f_stringifier_default         = 0
        
        // private flags
        , f_stringifier_is_list             = 0x001
        , f_stringifier_is_item             = 0x002
        , f_stringifier_is_long             = 0x004
        
        // standard parser flags
        , f_stringifier_pretty_list_items   = 0x001 << STRINGIFIER_INDENT_BITS
        , f_stringifier_pretty_if_long      = 0x002 << STRINGIFIER_INDENT_BITS
        
        , f_stringifier_break_before_item   = 0x004 << STRINGIFIER_INDENT_BITS
        , f_stringifier_break_after_item    = 0x008 << STRINGIFIER_INDENT_BITS
        , f_stringifier_break_before_list   = 0x010 << STRINGIFIER_INDENT_BITS
        , f_stringifier_break_after_list    = 0x020 << STRINGIFIER_INDENT_BITS
        
        , f_stringifier_noescape_noprint    = 0x040 << STRINGIFIER_INDENT_BITS
        , f_stringifier_escape_null         = 0x080 << STRINGIFIER_INDENT_BITS
        
        , f_stringifier_line_comments       = 0x100 << STRINGIFIER_INDENT_BITS
        , f_stringifier_block_comments      = 0x200 << STRINGIFIER_INDENT_BITS
        
        , flag_user_defined                 = 0x001 
            << (STRINGIFIER_INDENT_BITS + STRINGIFIER_FLAG_BITS)
        
      } stringifier_flags_t;
      
      Stringifier ( size_t default_flags, unsigned int line_width );
      
      std::ostream& stringify ( std::ostream& os, Stringifier* stringifier ) const;
      
      std::string stringify ( Stringifier* stringifier ) const;
      
protected:
      
    };  // class Stringifier
    
    Stringifier::Stringifier ( size_t default_flags, unsigned int line_width );
      
    std::string Stringifier::stringify ( Stringifier* stringifier ) const {
      stringstream ss;
      
      return stringify( ss, stringifier ).str( );
    }
    
  };  // namespace js

};  // namespace ls

#endif  // LS_JS_STRINGIFIER_HPP
      

