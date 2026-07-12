include(GenerateExportHeader)

add_library(lob
    src/Lob.cpp
    src/Order.cpp
)

generate_export_header(lob
    EXPORT_MACRO_NAME LOB_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/lob/lob_export.h
)

target_include_directories(lob
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)
