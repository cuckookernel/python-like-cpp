#ifndef PY_H
#define PY_H

#include <cassert>
#include <vector> 
#include <sstream>

namespace py {

    class range {

        // kudos to Boguslaw Cyganek https://stackoverflow.com/users/9479653/boguslaw-cyganek
        // https://stackoverflow.com/questions/13152252/is-there-a-compact-equivalent-to-python-range-in-c-stl/49236228#49236228

        const long from_, to_, step_;

    public: 

        range( long from, long to, long step ) 
            : from_(from), to_(to), step_(step) { 
                assert( to_ == from_ ||  ( to_ - from_ ) * step_ > 0   );
            }

        range( long to ) 
            : from_( 0 ), to_( to ), step_( 1 ) {
                assert( to >= from_ );
            }

        range( long from, long to )
            : from_( from ), to_( to ), step_( 1  ) {
               assert( to_ >= from_ );
           }

        class _range_iter {
            long val_; 
            long step_;
            
            public: 
            _range_iter( const long v, const long step ) : val_(v), step_( step ) {}
            operator long() const { return val_; }
            operator const long &() { return val_; }
            const long operator * ( ) const { return val_; }
            const _range_iter& operator ++() {  val_ += step_; return *this; }

            bool operator == ( const _range_iter &ri ) const {
                return ! operator!=( ri );
            }
            bool operator != ( const _range_iter &ri ) const {
                return step_ > 0 ? val_ < ri.val_ : ri.val_ < val_;
            }

        }; // class _range_iter 

        _range_iter begin() { return _range_iter(from_, step_); } 
        _range_iter end() { return _range_iter(to_, step_); } 

        operator std::vector<long>()  {
            std::vector<long> ret; 

            if( step_ == 0 ) {
                return ret;
            }

            ret.reserve( (to_ - from_ ) / step_ + 1  );

            for( auto i : (*this) ) {
                ret.push_back( i );
            } 

            return ret;
        } 

    }; // class range


    std::vector<std::string> str_split( std::string a_str, char sep ) {
        std::stringstream ss( a_str ); 
        std::vector<std::string> result;

        while( ss.good() )  {
            std::string substr;
            getline( ss, substr, sep );
            // printf( "substr=%s", substr.c_str() );
            result.push_back( substr );
        }

        return result;
    }

    template<typename T>
    std::string str_join( std::vector<T> pieces, std::string sep )  {
        std::stringstream ret; 
        
        std::size_t i = 0;
        for( auto p : pieces ) {
            ret << p;            
            if( i++ < pieces.size() - 1 ) {
                ret << sep;
            }
        }

        return ret.str();
    }

    class Str {


        public : 
            const std::string str_;

        Str(std::string s) : str_(s) {}

        template<typename T>
        std::string join(std::vector<T> vec) {
            return str_join( vec, str_ );
        }
    };

    template< typename T >
    class enumerate {
        private: 
        T& iterable_;

        typedef decltype( iterable_.begin()) Iter;
        typedef decltype(*iterable_.begin()) V; 
        typedef std::pair<long, V> Pair; 

        public:
            enumerate( T& iterable ) : iterable_( iterable ) {}

        class iterator {
            private: 
                long i_;
                Iter it_;

            public: 
                iterator( Iter it ) : i_(0L), it_(it) {}

                Pair get() const { return Pair(i_, *it_); }

                operator Pair() const { return get(); }
                operator const Pair&() { return get(); }
                const Pair operator*() const { return get(); }
                const iterator& operator++() {  it_++; i_++; return *this; }
                
                bool operator!=( const iterator& rhs ) { return it_ != rhs.it_; }
                bool operator==( const iterator& rhs ) { return !operator!=(rhs); }

        };

        iterator begin() { return iterator( iterable_.begin()); }
        iterator end()   { return iterator( iterable_.end()); }

    };

} // namespace py 

#endif /* ifdef PY_H */