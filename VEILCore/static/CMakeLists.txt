#	Copyright (c) 2018, TecSec, Inc.
#
#	Redistribution and use in source and binary forms, with or without
#	modification, are permitted provided that the following conditions are met:
#	
#		* Redistributions of source code must retain the above copyright
#		  notice, this list of conditions and the following disclaimer.
#		* Redistributions in binary form must reproduce the above copyright
#		  notice, this list of conditions and the following disclaimer in the
#		  documentation and/or other materials provided with the distribution.
#		* Neither the name of TecSec nor the names of the contributors may be
#		  used to endorse or promote products derived from this software 
#		  without specific prior written permission.
#		 
#	ALTERNATIVELY, provided that this notice is retained in full, this product
#	may be distributed under the terms of the GNU General Public License (GPL),
#	in which case the provisions of the GPL apply INSTEAD OF those given above.
#		 
#	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#	DISCLAIMED.  IN NO EVENT SHALL TECSEC BE LIABLE FOR ANY 
#	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#	LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Written by Roger Butler

if(MSVC)
	set(CMAKE_C_FLAGS_DEBUG         "${CMAKE_C_FLAGS_DEBUGSTATIC}")
	set(CMAKE_C_FLAGS_RELEASE       "${CMAKE_C_FLAGS_RELEASESTATIC}")
	set(CMAKE_CXX_FLAGS_DEBUG       "${CMAKE_CXX_FLAGS_DEBUGSTATIC}")
	set(CMAKE_CXX_FLAGS_RELEASE     "${CMAKE_CXX_FLAGS_RELEASESTATIC}")
endif(MSVC)

add_library(VEILCore_s STATIC
    ${VEILCoreSource}
	stdafx.h
	stdafx.cpp
)
add_dependencies(VEILCore_s VEILCore)
set_source_files_properties(
    ${GEN_SOURCE_XASN}
	${GEN_EXPORTS_XASN}
	${GEN_HEADERS_XASN}
    PROPERTIES GENERATED TRUE
    )
target_include_directories(VEILCore_s INTERFACE $<BUILD_INTERFACE:${PUBLIC_SOURCE_TOP_DIR}/include> $<INSTALL_INTERFACE:${TS_MODULE}/include>)

# if(ANDROID)
    set_target_properties(VEILCore_s PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
# endif()
if(WIN32)
    add_precompiled_header(VEILCore_s stdafx.h FORCEINCLUDE SOURCE_CXX stdafx.cpp)
else()
    # add_precompiled_header(VEILCore_s include/stdafx.h FORCEINCLUDE SOURCE_CXX stdafx.cpp)
endif(WIN32)

set_target_properties(VEILCore_s PROPERTIES FOLDER "Modules/Static" COMPILE_DEFINITIONS "VEILCORE_STATIC;_STATIC_CYBERVEIL")

if(APPLE)
else()
    install(TARGETS VEILCore_s ARCHIVE DESTINATION ${LIB_DIR} LIBRARY DESTINATION ${SHLIB_DIR} RUNTIME DESTINATION ${BIN_DIR} )
endif()
