# - Try to find libpugixml

find_path(LIBPUGIXML_INCLUDE_DIR pugixml.hpp PATH_SUFFIXES pugixml)
find_library(LIBPUGIXML_LIBRARY NAMES pugixml libpugixml)

set(LIBPUGIXML_INCLUDE_DIRS ${LIBPUGIXML_INCLUDE_DIR})
set(LIBPUGIXML_LIBRARIES ${LIBPUGIXML_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libpugixml DEFAULT_MSG
    LIBPUGIXML_LIBRARY LIBPUGIXML_INCLUDE_DIR)
