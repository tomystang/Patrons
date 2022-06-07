cmake_minimum_required(VERSION 3.10.2)

project(patrons)

add_library(
  patrons
  SHARED
  patrons_core.c
  xhook/xh_core.c
  xhook/xh_elf.c
  xhook/xh_log.c
  xhook/xh_util.c
  xhook/xh_version.c
  xhook/xhook.c
  xlog_stub/xlog.c
)

target_compile_options(
  patrons
  PRIVATE -O3 -fvisibility=hidden -fdata-sections -ffunction-sections
  PRIVATE -D__PATRONS_API_VERSION=${GRADLE_PATRONS_VERSION}
)

find_library(log-lib log)

target_link_libraries(
  patrons
  PRIVATE ${log-lib}
  PRIVATE z
  PRIVATE -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/patrons-native.ver -Wl,--gc-sections
)