set(HEADERS)
set(CPPS
  networking.cpp
)

if(WIN32 AND NOT UWP_BUILD)
  list(APPEND CPPS
    directplay.cpp
  )
endif()

if(WIN32)
  set(PLATFORM_LIBS ${DXGUID_LIBRARY})
endif()

add_library(networking STATIC ${HEADERS} ${CPPS})
target_link_libraries(networking PRIVATE
  ddebug
  ddio
  logger
  mem
  module
  ${PLATFORM_LIBS}
)
