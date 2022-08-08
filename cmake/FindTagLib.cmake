# - Try to find libtag

find_path(LIBTAG_INCLUDE_DIR tag.h PATH_SUFFIXES taglib)
find_library(LIBTAG_LIBRARY NAMES tag libtag)

set(LIBTAG_INCLUDE_DIRS ${LIBTAG_INCLUDE_DIR})
set(LIBTAG_LIBRARIES ${LIBTAG_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TagLib DEFAULT_MSG
    LIBTAG_LIBRARY LIBTAG_INCLUDE_DIR)
