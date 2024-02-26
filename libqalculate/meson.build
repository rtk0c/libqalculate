# For stuff in src/, the need to use #include "support.h" which resides in <root>/libqalculate/
incdir_libqalculate = include_directories('.')

libqalc_headers = files([
  'Function.h', 'Calculator.h', 'DataSet.h', 'Variable.h',
  'ExpressionItem.h', 'Number.h', 'MathStructure.h', 'Prefix.h',
  'util.h', 'includes.h', 'Unit.h', 'BuiltinFunctions.h',
  'QalculateDateTime.h', 'qalculate.h',
])
libqalc_private_headers = files([
  'MathStructure-support.h', 'Calculator_p.h','ExpressionItem_p.h', 'MathStructure_p.h',
  'bernoulli_numbers.h', 'primes.h',
])
libqalc_sources = files([
  'Function.cc', 'Calculator.cc', 'Calculator-plot.cc', 'Calculator-parse.cc',
  'Calculator-definitions.cc', 'Calculator-calculate.cc', 'Calculator-convert.cc',
  'DataSet.cc', 'Variable.cc', 'ExpressionItem.cc', 'Number.cc', 'MathStructure.cc',
  'Prefix.cc', 'util.cc', 'Unit.cc', 'QalculateDateTime.cc',
  'BuiltinFunctions-util.cc', 'BuiltinFunctions-trigonometry.cc', 'BuiltinFunctions-matrixvector.cc',
  'BuiltinFunctions-datetime.cc', 'BuiltinFunctions-statistics.cc',
  'BuiltinFunctions-explog.cc', 'BuiltinFunctions-special.cc', 'BuiltinFunctions-algebra.cc',
  'BuiltinFunctions-calculus.cc', 'BuiltinFunctions-number.cc',
  'BuiltinFunctions-combinatorics.cc', 'BuiltinFunctions-logical.cc',
  'MathStructure-factor.cc', 'MathStructure-gcd.cc', 'MathStructure-integrate.cc',
  'MathStructure-isolatex.cc', 'MathStructure-polynomial.cc',
  'MathStructure-matrixvector.cc', 'MathStructure-print.cc',
  'MathStructure-differentiate.cc', 'MathStructure-calculate.cc', 'MathStructure-eval.cc',
  'MathStructure-convert.cc', 'MathStructure-decompose.cc', 'MathStructure-limit.cc',
])

# Use <root>/
# Allow includes like <libqalculate/includes.h>
libqalc_inc = [incdir]
libqalc_defines = []

# Realistically people using meson are not going to use a gcc version without <unordered_map> -- but I guess the autotools does it
if cpp_compiler.compiles('''
#include <unordered_map>
int main() {}
''')
  libqalc_defines += '-DHAVE_UNORDERED_MAP'
endif

# Required deps
libqalc_deps = [thread_dep, gmp, mpfr, libxml]

if get_option('compiled_definitions')
  libqalc_sources += data_definitions_c
  libqalc_defines += '-DCOMPILED_DEFINITIONS'
endif

if libcurl.found()
  libqalc_defines += '-DHAVE_LIBCURL'
  libqalc_deps += libcurl
endif
if icu_uc.found()
  libqalc_defines += '-DHAVE_ICU'
  libqalc_deps += icu_uc
endif
if iconv.found()
  libqalc_defines += '-DHAVE_ICONV'
  if c_compiler.compiles('''
#include <iconv.h>
int main(void) { iconv_t cd; const char **c; iconv(cd, c, NULL, NULL); return 0; }
''')
    libqalc_defines += '-DICONV_CONST=const'
  else
    libqalc_defines += '-DICONV_CONST='
  endif
  libqalc_deps += iconv
endif
if gettext.found()
  libqalc_deps += gettext
  # The original autotools buildsystem just straight up does not check whether gettext is found
  # It just uses gettext unconditionally if use-nls is true (probably because gettext is shipped by glibc by default)
  # This is technically the correct thing to do, even though doing so diverges from the autotool's behavior
  if get_option('use_nls')
    libqalc_defines += '-DENABLE_NLS'
  endif
endif
if get_option('with_gnuplot_call') == 'yes'
  libqalc_defines += '-DHAVE_GNUPLOT_CALL'
elif get_option('with_gnuplot_call') == 'byo'
  libqalc_defines += '-DHAVE_BYO_GNUPLOT'
endif

install_headers(
  libqalc_headers,
  subdir: 'libqalculate')

libqalc_lib = library('qalculate',
  sources: libqalc_sources,
  include_directories: libqalc_inc,
  cpp_args: libqalc_defines + [
    f'-DPACKAGE_DATA_DIR="@datadir@"',
    f'-DPACKAGE_LOCALE_DIR="@localedir@"',
    f'-DVERSION="@ver@"',
  ],
  # Translated from:
  #   libqalculate_la_LDFLAGS = -version-info $(QALCULATE_CURRENT):$(QALCULATE_REVISION):$(QALCULATE_AGE) -no-undefined
  link_args: [
    # I honsetly have no idea what is this supposed to do in the autotools
    # -version-info is absolutely not a valid ld flag
#    f'-Wl,-version-info @qalculate_major@:@qalculate_revision@:@qalculate_age@',
    # Ensure our shared library has no undefined symbols, as a sanity check
    '-Wl,--no-undefined',
  ],
  dependencies: libqalc_deps,
  install: true)

libqalculate = declare_dependency(
  compile_args: libqalc_defines,
  include_directories: libqalc_inc,
  link_with: libqalc_lib)
