include_guard(GLOBAL)

IF (BUILD_3RDPARTY_BINARIES)
  SET(HARFBUZZ_BUILD_UTILS_ARGUMENT -DHB_BUILD_UTILS=ON)
ELSE()
  SET(HARFBUZZ_BUILD_UTILS_ARGUMENT -DHB_BUILD_UTILS=OFF)
ENDIF ()

ExternalProjectCMake(harfbuzz
  DEPENDS cairo fontconfig freetype glib-2.0
  URL https://github.com/harfbuzz/harfbuzz/releases/download/2.6.4/harfbuzz-2.6.4.tar.xz
  URL_HASH SHA256=9413b8d96132d699687ef914ebb8c50440efc87b3f775d25856d7ec347c03c12

  CONFIGURE_ARGUMENTS 
    -DHB_HAVE_FREETYPE=ON
    -DHB_HAVE_GLIB=ON
    -DHB_HAVE_ICU=OFF

    -DHB_BUILD_TESTS=OFF

    ${HARFBUZZ_BUILD_UTILS_ARGUMENTS}
)

