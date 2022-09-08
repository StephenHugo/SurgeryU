get_target_property(COCOS2D_X_VERSION cocos2d VERSION)

if (COCOS2D_X_VERSION VERSION_GREATER_EQUAL 4.0)
	set(SPINE_COCOS_X_VERSION_DIR "v4")
else()
	set(SPINE_COCOS_X_VERSION_DIR "v3")
endif()

set(SPINE_COCOS2DX_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/AttachmentVertices.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SkeletonAnimation.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SkeletonRenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/spine-cocos2dx.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/${SPINE_COCOS_X_VERSION_DIR}/SkeletonBatch.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/${SPINE_COCOS_X_VERSION_DIR}/SkeletonTwoColorBatch.h
   )

set(SPINE_COCOS2DX_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/AttachmentVertices.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SkeletonAnimation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SkeletonRenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/spine-cocos2dx.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/${SPINE_COCOS_X_VERSION_DIR}/SkeletonBatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/${SPINE_COCOS_X_VERSION_DIR}/SkeletonTwoColorBatch.cpp
  )


list(APPEND SPINE_COCOS2DX_SRC ${SPINE_COCOS2DX_HEADER})

add_library(spine-cocos2dx-static STATIC ${SPINE_COCOS2DX_SRC})

set_target_properties(spine-cocos2dx-static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

add_dependencies(spine-cocos2dx-static spine-static cocos2d)

target_link_libraries(spine-cocos2dx-static 
	PUBLIC spine-static 
	PRIVATE cocos2d
)
target_include_directories(spine-cocos2dx-static 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${SPINE_COCOS_X_VERSION_DIR}/src
    )
