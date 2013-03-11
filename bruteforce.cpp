// O(n^2) runtime

#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//-- Auxillary stuff --//

#define DEBUG cerr

struct RuntimeError {};

typedef vector< int > Ints;
typedef vector< string > Lines;

// Convert a line into multiple ints
Ints toInt( const string &line, int n ) {
    stringstream ss( line );
    Ints ints;

    for( int i = 0; i < n; ++i ) {
        int c;
        if( ss >> c ) {
            ints.push_back( c );
        }
        else {
            throw RuntimeError();
        }
    }

    return ints;
}


class Point {
public:
    Point( int x, int y )
    : x_( x ), y_( y ) {}

    Point( const string &line ) {
        Ints ints = toInt( line, 2 );
        x_ = ints[0];
        y_ = ints[1];
    }

    int x() { return x_; }
    int y() { return y_; }

private:
    int x_;
    int y_;
};

class Block {
public:
    Block( int x1, int y1, int x2, int y2 )
    : x1_( x1 ), y1_( y1 ), x2_( x2 ), y2_( y2 ) {}

    Block( const string &line ) {
        Ints ints = toInt( line, 4 );
        x1_ = ints[0];
        x2_ = ints[1];
        y1_ = ints[2];
        y2_ = ints[3];
    }

    int x1() { return x1_; }
    int y1() { return y1_; }
    int x2() { return x2_; }
    int y2() { return y2_; }

    bool contains( Point *p ) {
        return p->x() >= x1_ &&
               p->y() >= y1_ &&
               p->x() <= x2_ &&
               p->y() <= y2_;
    }

private:
    int x1_;
    int y1_;
    int x2_;
    int y2_;
};

typedef vector< Block > Blocks;
typedef vector< Point > Points;

typedef vector< Block* > BlocksRef;
typedef vector< Point* > PointsRef;

// Convert lines into Blocks/Points
template< typename T >
vector< T > toContainer( const Lines &lines ) {
    typedef vector< T > Container;

    unsigned int size = lines.size();
    Container container;

    for( unsigned int i = 0; i < size; ++i ) {
        container.push_back( T( lines[i] ) );
    }

    return container;
}

// Read in n number of lines
Lines getInput( int n ) {
    Lines input;

    for( int i = 0; i < n; ++i ) {
        string in;
        getline( cin, in );

        //DEBUG << in << endl;

        input.push_back( in );
    }

    return input;
}

// self-implemented copy_if
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator loc_copy_if( InputIterator first, InputIterator last,
                            OutputIterator result, Predicate pred ) {
    while( first!=last ) {
        if( pred( *first ) ) {
            *result++ = *first;
        }
        ++first;
    }

    return result;
}

void printBlocksRef( BlocksRef &blocks ) {
    for( unsigned int i = 0; i < blocks.size(); ++i ) {
        DEBUG << "x1 = "  << blocks[i]->x1()
              << " y1 = " << blocks[i]->y1()
              << " x2 = " << blocks[i]->x2()
              << " y2 = " << blocks[i]->y2() << endl;
    }
}

void printPointsRef( PointsRef &points ) {
    for( unsigned int i = 0; i < points.size(); ++i ) {
        DEBUG << "x = "  << points[i]->x()
              << " y = " << points[i]->y() << endl;
    }
}

//-- Main Logic --//

int pointsInBlocks( BlocksRef &blocks, PointsRef &points ) {
    int k = 0;
    for (unsigned i = 0; i < blocks.size(); ++i) {
        for (unsigned j = 0; j < points.size(); ++j) {
            if (blocks[i]->contains(points[j])) {
                ++k;
            }
        }
    }

    return k;
}

int main() {
    Lines blocks_input;
    Lines points_input;

    int nb;
    int np;

    cin >> nb;
    cin >> np;

    if( !nb || !np ) {
        cout << 0 << endl;
    }

    // skip to next line
    cin.ignore( numeric_limits< streamsize >::max(), '\n' );

    blocks_input = getInput( nb );
    points_input = getInput( np );

    Blocks blocks = toContainer< Block >( blocks_input );
    Points points = toContainer< Point >( points_input );

    BlocksRef b_ref;
    PointsRef p_ref;

    for( unsigned int i = 0; i < blocks.size(); ++i ) {
        b_ref.push_back( &blocks[i] );
    }

    for( unsigned int i = 0; i < points.size(); ++i ) {
        p_ref.push_back( &points[i] );
    }

    int num = pointsInBlocks( b_ref, p_ref );

    cout << num << endl;

    return 0;
}
