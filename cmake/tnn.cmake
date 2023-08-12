
include(ExternalProject)
# message(STATUS "ENABLE_NNDEPLOY_INFERENCE_TNN: ${ENABLE_NNDEPLOY_INFERENCE_TNN}")

if (ENABLE_NNDEPLOY_INFERENCE_TNN STREQUAL "OFF")
elseif (ENABLE_NNDEPLOY_INFERENCE_TNN STREQUAL "ON")
else()
  include_directories(${ENABLE_NNDEPLOY_INFERENCE_TNN}/include)
  set(LIB_PATH ${ENABLE_NNDEPLOY_INFERENCE_TNN}/lib)
  set(LIBS "TNN")
  foreach(LIB ${LIBS})
    set(LIB_NAME ${NNDEPLOY_LIB_PREFIX}${LIB}${NNDEPLOY_LIB_SUFFIX})
    set(FULL_LIB_NAME ${LIB_PATH}/${LIB_NAME})
    set(NNDEPLOY_THIRD_PARTY_LIBRARY ${NNDEPLOY_THIRD_PARTY_LIBRARY} ${FULL_LIB_NAME})    
  endforeach()
  file(GLOB_RECURSE INSTALL_LIBS "${LIB_PATH}/*")
  foreach(INSTALL_LIB ${INSTALL_LIBS})
    install(FILES ${INSTALL_LIB} DESTINATION ${NNDEPLOY_INSTALL_PATH})
  endforeach()
endif()