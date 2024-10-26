/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Record_Red_png;
    const int            Record_Red_pngSize = 1742;

    extern const char*   Stop_png;
    const int            Stop_pngSize = 1390;

    extern const char*   Record_png;
    const int            Record_pngSize = 1732;

    extern const char*   Play_png;
    const int            Play_pngSize = 1109;

    extern const char*   down_png;
    const int            down_pngSize = 2006;

    extern const char*   matrix_png;
    const int            matrix_pngSize = 759;

    extern const char*   up_png;
    const int            up_pngSize = 1975;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
