#include "PathMan.hpp"

bool PathMan::addSearchPath( const Path& directory )
{
    if (directory.empty()) return false;
    auto dir = directory;
    if (!is_directory( dir )) { if (dir.has_extension()) dir = dir.remove_filename(); }

    dir = directory.lexically_normal();
    if (!dir.empty() && dir.generic_string().back() != '/') dir += '/';

    if (!dir.is_absolute()) {
        std::error_code code;

        dir = absolute( dir, code );

        if (code) { return false; }
    }
    dir.make_preferred();

    if (std::find_if( searchPaths.begin(), searchPaths.end(),
                      [dir]( const Path& path ) { return dir.string() == path; } )
        != searchPaths.end())
        return false;

    searchPaths.push_back( dir );
    return true;
}

bool PathMan::removeSearchPath( const Path& directory )
{
    auto dir = directory;

    if (!is_directory( dir )) { return false; }

    if (!dir.is_absolute()) { return false; }

    for (auto it = searchPaths.begin(); it != searchPaths.end(); ++it) {
        if (*it == dir) {
            searchPaths.erase( it );
            return true;
        }
    }

    return false;
}

bool PathMan::makeSearchPaths()
{
    bool hasCreatedDirs = true;

    for (auto dir : searchPaths) {
        if (!std::filesystem::exists( dir )) {
            std::error_code error_code = {};
            dir.make_preferred();
            hasCreatedDirs &= !std::filesystem::create_directories( dir, error_code );

            hasCreatedDirs = hasCreatedDirs && !error_code;
        }
    }

    return hasCreatedDirs;
}

bool PathMan::isFound( const Path& path ) const
{
    if (path.is_absolute()) return isIncluded( path ) && std::filesystem::exists( path );


    for (const auto& dir : searchPaths) {
        Path absPath = dir / path;
        absPath  = absPath.lexically_normal();
        absPath.make_preferred();
        if (std::filesystem::exists( absPath )) return true;
    }

    return false; // return empty path if not found;
}

bool PathMan::isIncluded( const Path& absPath ) const
{
    if (!absPath.is_absolute()) { return false; }

    Path lAbsPath = absPath.lexically_normal();


    for (const auto& dir : searchPaths) {
        if (absPath.string().find_first_of( dir.string() ) != std::string::npos) { return true; }
    }


    return true; // return empty path if not found;
}

PathMan::Path PathMan::getFullPath( const Path& relativePath ) const
{
    if (relativePath.is_absolute()) return relativePath;


    for (const auto& dir : searchPaths) {
        Path fpath = dir / relativePath;

        if (std::filesystem::exists( fpath )) return fpath;
    }

    return {}; // return empty path if not found;
}
