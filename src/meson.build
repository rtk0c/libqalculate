# defs2doc_sources = files([
#   'defs2doc.cc',
# ])
# defs2doc = executable('defs2doc', defs2doc_sources,
#   # TODO curl
#   dependencies: [libxml])

qalc_defines = []
if readline.found()
  qalc_defines += '-DHAVE_LIBREADLINE'
endif

qalc_sources = files([
  'qalc.cc',
])
qalc = executable('qalc', qalc_sources,
  # For the #include "support.h"
  include_directories : [incdir_libqalculate],
  cpp_args : qalc_defines + [
    '-DVERSION="@ver@"',
  ],
  dependencies : [libqalculate, libcurl, libxml, icu_uc, readline, gettext, iconv])
