#include <catch2/catch_session.hpp>


int main( int argc, char** argv )
{
    auto session = Catch::Session();
    return session.run( argc, argv );
}
