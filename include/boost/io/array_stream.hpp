//  Boost io/array_stream.hpp header file  -----------------------------------//

//  (C) Copyright Daryle Walker 2003.  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears 
//  in all copies.  This software is provided "as is" without express or implied 
//  warranty, and with no claim as to its suitability for any purpose. 

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_IO_ARRAY_STREAM_HPP
#define BOOST_IO_ARRAY_STREAM_HPP

#include <boost/io_fwd.hpp>  // self include

#include <boost/config.hpp>                 // for BOOST_STATIC_CONSTANT
#include <boost/io/streambuf_wrapping.hpp>  // for basic_wrapping_istream, etc.

#include <cstddef>    // for std::size_t
#include <streambuf>  // for std::basic_streambuf
#include <string>     // for std::char_traits


namespace boost
{
namespace io
{


//  Array-using streambuf class template declaration  ------------------------//

template < std::size_t N, typename Ch, class Tr >
class basic_array_streambuf
    : public std::basic_streambuf<Ch, Tr>
{
    typedef std::basic_streambuf<Ch, Tr>   base_type;
    typedef basic_array_streambuf          self_type;

public:
    // Template arguments
    BOOST_STATIC_CONSTANT( std::size_t, array_size = N );

    typedef Ch  char_type;
    typedef Tr  traits_type;

    // Constructors
    basic_array_streambuf();
    basic_array_streambuf( self_type const &c );

    // Accessors
    char_type *  array_begin();
    char_type *  array_end();

    char_type const *  array_begin() const;
    char_type const *  array_end() const;

private:
    // Member data
    char_type  array_[ array_size ];

};  // boost::io::basic_array_streambuf


//  Array-using stream class template declarations  --------------------------//

// Macro to template the templates!
#define BOOST_PRIVATE_WRAPPER( SuffixF, SuffixB ) \
    template < std::size_t N, typename Ch, class Tr > \
    class basic_array_##SuffixF \
        : public basic_wrapping_##SuffixB< basic_array_streambuf<N, Ch, Tr> > \
    { \
    public: \
        BOOST_STATIC_CONSTANT( std::size_t, array_size = N ); \
        typedef Ch  char_type; \
        typedef Tr  traits_type; \
        char_type *  array_begin() \
            { return this->rdbuf()->array_begin(); } \
        char_type *  array_end() \
            { return this->rdbuf()->array_end(); } \
        char_type const *  array_begin() const \
            { return this->rdbuf()->array_begin(); } \
        char_type const *  array_end() const \
            { return this->rdbuf()->array_end(); } \
    }

BOOST_PRIVATE_WRAPPER( istream, istream );
BOOST_PRIVATE_WRAPPER( ostream, ostream );
BOOST_PRIVATE_WRAPPER( stream, iostream );

#undef BOOST_PRIVATE_WRAPPER


//  Array-using streambuf class template member function definitions  --------//

template < std::size_t N, typename Ch, class Tr >
inline
basic_array_streambuf<N, Ch, Tr>::basic_array_streambuf
(
)
{
    this->setg( this->array_, this->array_, this->array_
     + self_type::array_size );
    this->setp( this->array_, this->array_ + self_type::array_size );
}

template < std::size_t N, typename Ch, class Tr >
inline
basic_array_streambuf<N, Ch, Tr>::basic_array_streambuf
(
    basic_array_streambuf<N, Ch, Tr> const &  c
)
    : base_type( c )
{
    traits_type::copy( this->array_, c.array_, self_type::array_size );

    this->setg( this->array_, this->array_, this->array_
     + self_type::array_size );
    this->setp( this->array_, this->array_ + self_type::array_size );
}

template < std::size_t N, typename Ch, class Tr >
inline
typename basic_array_streambuf<N, Ch, Tr>::char_type *
basic_array_streambuf<N, Ch, Tr>::array_begin
(
)
{
    return this->array_;
}

template < std::size_t N, typename Ch, class Tr >
inline
typename basic_array_streambuf<N, Ch, Tr>::char_type *
basic_array_streambuf<N, Ch, Tr>::array_end
(
)
{
    return this->array_ + self_type::array_size;
}

template < std::size_t N, typename Ch, class Tr >
inline
typename basic_array_streambuf<N, Ch, Tr>::char_type const *
basic_array_streambuf<N, Ch, Tr>::array_begin
(
) const
{
    return this->array_;
}

template < std::size_t N, typename Ch, class Tr >
inline
typename basic_array_streambuf<N, Ch, Tr>::char_type const *
basic_array_streambuf<N, Ch, Tr>::array_end
(
) const
{
    return this->array_ + self_type::array_size;
}


}  // namespace io
}  // namespace boost


#endif  // BOOST_IO_ARRAY_STREAM_HPP
