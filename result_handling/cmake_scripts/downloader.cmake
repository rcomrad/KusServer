#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8.2)
project(downloader)

#--------------------------------------------------------------------------------

include(ExternalProject)

ExternalProject_Add(downloader
    SOURCE_DIR ${TARGET_DIR}
    URL ${ARCHIVE_URL}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)

#--------------------------------------------------------------------------------
