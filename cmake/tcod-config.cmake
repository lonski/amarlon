#
# Copyright (c) 2014, Lukasz Gromanowski <lgromanowski@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
#  and/or other materials provided with the distribution.
#
# * Neither the name of [project] nor the names of its
#  contributors may be used to endorse or promote products derived from
#  this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#####
#
#  Try to find libtcod, once done this will define:
#
#  TCOD_FOUND - system has libtcod
#  TCOD_INCLUDE_DIRS - the libtcod include directory
#  TCOD_LIBRARIES - Link these to use libtcod
#
##
if(TCOD_LIBRARIES AND TCOD_INCLUDE_DIRS)
    # it's in cache already
    set(TCOD_FOUND TRUE)
else(TCOD_LIBRARIES AND TCOD_INCLUDE_DIRS)
    find_path(TCOD_INCLUDE_DIR
	NAMES libtcod/libtcod.h
	PATHS
	    /usr/include
	    /usr/local/include
	    /opt/local/include
	    "${CMAKE_CURRENT_SOURCE_DIR}/include"
	    "${PROJECT_SOURCE_DIR}/include"
    )
    set(TCOD_INCLUDE_DIRS ${TCOD_INCLUDE_DIR} "${TCOD_INCLUDE_DIR}/libtcod")

    find_library(TCOD_C_LIBRARY
	NAMES
	    tcod
	PATHS
	    /usr/lib
	    /usr/local/lib
	    /opt/local/lib
	    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	    "${PROJECT_SOURCE_DIR}/lib"
    )
    find_library(TCOD_CXX_LIBRARY
	NAMES
	    tcodxx
		libtcod
		libtcod-mingw
	PATHS
	    /usr/lib
	    /usr/local/lib
	    /opt/local/lib
	    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	    "${PROJECT_SOURCE_DIR}/lib"
    )

    set(TCOD_LIBRARIES ${TCOD_LIBRARIES} ${TCOD_C_LIBRARY} ${TCOD_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libtcod DEFAULT_MSG TCOD_LIBRARIES TCOD_INCLUDE_DIRS)

    # show the TCOD_INCLUDE_DIRS and TCOD_LIBRARIES variables only in the advanced view
    mark_as_advanced(TCOD_INCLUDE_DIRS TCOD_LIBRARIES)

endif(TCOD_LIBRARIES AND TCOD_INCLUDE_DIRS)
