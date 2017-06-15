## Process this file with cmake
#====================================================================
#  NeXus - Neutron & X-ray Common Data Format
#  
#  CMakeLists for building the NeXus library and applications.
#
#  Copyright (C) 2011 Stephen Rankin
#  
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
# 
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
# 
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free 
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
#  MA  02111-1307  USA
#             
#  For further information, see <http://www.nexusformat.org>
#
#
#====================================================================

find_library(GUILE_LIB NAME guile PATHS $ENV{GUILE_ROOT})

find_path(GUILE_INCLUDE NAME libguile.h PATHS $ENV{GUILE_ROOT} $ENV{GUILE_ROOT}/include)

if(GUILE_LIB AND GUILE_INCLUDE)
    set(GUILE_LINK "-lguile")
    include_directories($ENV{GUILE_INCLUDE})
endif(GUILE_LIB AND GUILE_INCLUDE)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GUILELIB DEFAULT_MSG GUILE_LIB GUILE_INCLUDE)

MARK_AS_ADVANCED(GUILE_LIB GUILE_INCLUDE)
