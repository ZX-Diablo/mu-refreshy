# - Try to find fakeit

find_path(FAKEIT_INCLUDE_DIR fakeit.hpp ${PROJECT_SOURCE_DIR}/FakeIt/single_header/boost)

set(FAKEIT_INCLUDE_DIRS ${FAKEIT_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FakeIt DEFAULT_MSG
    FAKEIT_INCLUDE_DIR)
