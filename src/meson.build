qalc_defines = []
if readline.found()
  qalc_defines += '-DHAVE_LIBREADLINE'
endif

qalc_sources = files([
  'qalc.cc',
])

qalc = executable('qalc',
  sources : qalc_sources,
  # For the #include "support.h"
  include_directories : [incdir_libqalculate],
  cpp_args : qalc_defines + [
    '-DVERSION="@ver@"',
  ],
  dependencies : [libqalculate, libcurl, libxml, icu_uc, readline, gettext, iconv],
  install : true)

defs2doc = executable('defs2doc',
  sources : ['defs2doc.cc'],
  # For the #include "support.h"
  include_directories : [incdir_libqalculate],
  dependencies: [libqalculate, libxml, libcurl, icu_uc, gettext, iconv])

tests = executable('tests',
  sources : ['test.cc'],
  # For the #include "support.h"
  include_directories : [incdir_libqalculate],
  dependencies : [libqalculate, libxml, libcurl, icu_uc, gettext, iconv])

test('tests', tests)

unittest = executable('unittest',
  sources : ['unittest.cc'])

# TODO unittest.cc hardcodes paths for in-source build
#test('unit tests', unittest, workdir : meson.source_root())
