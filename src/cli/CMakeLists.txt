set(MOORIE_SRCS main.cpp
                anyoption.cpp
                moorie.cpp)

set(MOORIE_MOC_HDRS moorie.h)

set(QT_USE_QTNETWORK TRUE)

qt4_wrap_cpp( MOORIE_MOC_SRCS ${MOORIE_MOC_HDRS} )
qt4_automoc(  ${MOORIE_MOC_HDRS})

include( ${QT_USE_FILE} )

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${MOORIE_SOURCE_DIR}/src/lib
    ${QT_INCLUDE_DIR}
)

link_directories(
    ${CMAKE_BINARY_DIR}
    ${MOORIE_BINARY_DIR}/src/lib
)

add_definitions( -O2 -w -D_REENTRANT $(QT_DEFINITIONS) )

add_executable (moorie ${MOORIE_SRCS} ${MOORIE_MOC_SRCS} )

target_link_libraries (moorie moor
    ${MCRYPT_LIBRARIES}
    ${MHASH_LIBRARIES}
    ${CURL_LIBRARIES} 
    ${OPENSSL_LIBRARIES} 
    ${Boost_REGEX_LIBRARY} 
    ${QT_LIBRARIES})
install (TARGETS moorie DESTINATION bin)
