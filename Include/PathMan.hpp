#pragma once
#include <vector>
#include <filesystem>
#include <algorithm>

class PathMan
{


public:
    using Path = std::filesystem::path;
    bool addSearchPath( const Path& directory );
    bool removeSearchPath( const Path& directory );


    bool makeSearchPaths();

    bool isFound( const Path& path ) const;

    [[nodiscard]] bool isIncluded( const Path& absPath ) const;


    [[nodiscard]] Path getFullPath( const Path& relativePath ) const;


    const std::vector<Path>& currentSearchPaths() const { return searchPaths; }

private:
    std::vector<Path> searchPaths;
};
