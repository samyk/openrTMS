# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/bin/i586-mingw32msvc-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/i586-mingw32msvc-g++)
SET(CMAKE_RC_COMPILER  /usr/bin/i586-mingw32msvc-windres)


SET(wxWidgets_CONFIG_EXECUTABLE /usr/local/i586-mingw32/bin/wx-config)
SET(wxWidgets_ROOT_DIR /usr/local/i586-mingw32)
SET(wxWidgets_LIB_DIR /usr/local/i586-mingw32/lib)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/local/i586-mingw32 /usr/local/i586-mingw32/bin)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM FIRST)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
