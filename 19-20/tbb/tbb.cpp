#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "/share/installs/tbb/include/tbb/parallel_for.h"
#include "/share/installs/tbb/include/tbb/blocked_range.h"
using namespace tbb;

float Foo(float) {
  //do nothing
  return 0;
}
class ApplyFoo {
    float *const my_a;
public:
    void operator()( const blocked_range<size_t>& r ) const {
        float *a = my_a;
        for( size_t i=r.begin(); i!=r.end(); ++i ) 
           Foo(a[i]);
    }
    ApplyFoo( float a[] ) :
        my_a(a)
    {}
};

int main (void) {

  return 0;
}
