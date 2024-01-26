#include "PathMan.hpp"
#include <catch2/catch_test_macros.hpp>


TEST_CASE( "PathMan-Tests" )
{
    PathMan pathMan = {};

    auto added = pathMan.addSearchPath( "Test/test" );
    REQUIRE( added );

    added = pathMan.addSearchPath( "Test/test1/" );
    REQUIRE( added );
    added = pathMan.addSearchPath( "Test/test2/" );
    REQUIRE( added );
    added = pathMan.addSearchPath( "Test/test4/" );
    REQUIRE( added );

    added = pathMan.addSearchPath( "Test/test/" );
    REQUIRE_FALSE( added );

    added = pathMan.addSearchPath( "Test/test2/" );
    REQUIRE_FALSE( added );

    auto hasCreatedDirs = pathMan.makeSearchPaths();


    REQUIRE( hasCreatedDirs ); // Could have failed due to permission.
    REQUIRE( std::filesystem::exists( pathMan.currentSearchPaths()[0] ) );


    SECTION( "ResolveSetup" ) {
        PathMan::Path test_dir = "Test/test/test2";
        auto asbtest_dir       = absolute( test_dir );

        std::filesystem::create_directories( asbtest_dir );


        SECTION( "Find Path" ) {
            bool isFound = pathMan.isFound( "test2" );
            REQUIRE( isFound );
        }


        SECTION( "GetFullPath" ) {
            auto absPath = pathMan.getFullPath( "test2" );

            REQUIRE( absPath.is_absolute() );
            REQUIRE( std::filesystem::exists( absPath ) );
        }


        SECTION( "isIncluded" ) {
            PathMan::Path test_dir = "Test/test2/test5/";
            auto asbtest_dir       = absolute( test_dir );
            bool isIncluded        = pathMan.isIncluded( asbtest_dir );
            REQUIRE( isIncluded );

            test_dir    = "Test/test1/test/5/";
            asbtest_dir = absolute( test_dir );
            isIncluded  = pathMan.isIncluded( asbtest_dir );
            REQUIRE( isIncluded );
        }
    }


}
