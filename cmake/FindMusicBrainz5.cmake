# - Try to find libmusicbrainz5

find_path(LIBMUSICBRAINZ5_INCLUDE_DIR Query.h PATH_SUFFIXES musicbrainz5)
find_library(LIBMUSICBRAINZ5_LIBRARY NAMES musicbrainz5 libmusicbrainz5)

set(LIBMUSICBRAINZ5_INCLUDE_DIRS ${LIBMUSICBRAINZ5_INCLUDE_DIR})
set(LIBMUSICBRAINZ5_LIBRARIES ${LIBMUSICBRAINZ5_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libmusicbrainz5 DEFAULT_MSG
    LIBMUSICBRAINZ5_LIBRARY LIBMUSICBRAINZ5_INCLUDE_DIR)
