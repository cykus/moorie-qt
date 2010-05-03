set(LIBMOORIE_SRCS     decoder.cpp
                       libmoorie.cpp
                       cmstats.cpp  
                       cmtransfer.cpp
                       cmdownload.cpp  
                       cmupload.cpp
                       cmtools.cpp 
                       emailheader.cpp
                       hash.cpp
                       hashmanager.cpp
                       hashutils.cpp
                       log.cpp
                       mailbox.cpp
                       mailboxfactory.cpp
                       moorhunthash.cpp
                       stringutils.cpp
                       tools.cpp
                       mailboxes/googleappsmailbox.cpp)

set(LIBMOORIE_MOC_HDRS cmtransfer.h
                       log.h
                       mailbox.h
                       mailboxes/googleappsmailbox.h)

set(QT_USE_QTNETWORK TRUE)

qt4_wrap_cpp( LIBMOORIE_MOC_SRCS ${LIBMOORIE_MOC_HDRS} )
qt4_automoc(  ${LIBMOORIE_MOC_HDRS})

include(${QT_USE_FILE})

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${MOORIE_SOURCE_DIR}/src/lib
    ${QT_INCLUDE_DIR}
)

add_library (moor SHARED ${LIBMOORIE_SRCS} ${LIBMOORIE_MOC_SRCS})

if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm") 
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm") 
    SET(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -lm")
    target_link_libraries (moor ${PROJECT_SOURCE_DIR}/libs/libmoorhunt64.a)
    
elseif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "i686" OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86" OR ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i586")
    target_link_libraries (moor ${PROJECT_SOURCE_DIR}/libs/libmoorhunt.a)
endif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
# 
set_property(TARGET moor PROPERTY LINK_INTERFACE_LIBRARIES "")
install (TARGETS moor DESTINATION lib${LIB_SUFFIX})
