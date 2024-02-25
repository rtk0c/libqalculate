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

# TODO finish and put behind a flag
# libqalc_def_files = [
#   'data/currencies.xml',
#   'data/datasets.xml',
#   'data/elements.xml',
#   'data/eurofxref-daily.xml',
#   'data/functions.xml',
#   'data/planets.xml',
#   'data/prefixes.xml',
#   'data/units.xml',
#   'data/variables.xml',
#   'data/rates.json',
# ]
# gen_defs_sh = find_program('meson.gen-defs.sh')
# definitions_c = custom_target(
#   'definitions.c',
#   input : [libqalc_def_files],
#   output : ['definitions.c']
#   command : [gen_defs_sh, '@INPUT@'])

# TODO implement po files

# For stuff in src/, the need to use #include "support.h" which resides in <root>/libqalculate/
incdir_libqalculate = include_directories('.')

# Use <root>/
# Allow includes like <libqalculate/includes.h>
libqalc_inc = [incdir]

libqalc_defines = [
  # Realistically people using meson are not going to use a gcc version without <unordered_map>, so let's just skip the feature test altogether
  '-DHAVE_UNORDERED_MAP',
]

# Required deps
libqalc_deps = [thread_dep, gmp, mpfr, libxml]

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
  # TODO The autotools does a test for "AIX 5.1 bug"
  #libqalc_defines += '-DICONV_CONST=const'
  libqalc_defines += '-DICONV_CONST='
  libqalc_deps += iconv
endif
if gettext.found()
  libqalc_deps += gettext
  # TODO I'm not sure if this is correct, the original autotools buildsystem just straight up does not check whether gettext is found
  #   (probably because it's shipped by gcc by default)
  #   and just uses gettext unconditionally if use-nls is true
  if get_option('use-nls')
    libqalc_defines += '-DENABLE_NLS'
    libqalc_defines += '-DGETTEXT_PACKAGE="libqalculate"'
  endif
endif
if get_option('with-gnuplot-call') == 'yes'
  libqalc_defines += '-DHAVE_GNUPLOT_CALL'
elif get_option('with-gnuplot-call') == 'byo'
  libqalc_defines += '-DHAVE_BYO_GNUPLOT'
endif

libqalc_lib = library('qalculate', libqalc_sources,
  include_directories : libqalc_inc,
  cpp_args : libqalc_defines + [
    f'-DPACKAGE_DATA_DIR="@datadir@"',
    f'-DPACKAGE_LOCALE_DIR="@localedir@"',
    f'-DVERSION="@ver@"',
  ],
  link_args : [
    # I honsetly have no idea what is this supposed to do in the autotools
    # f'-Wl,-version-info @qalculate_major@:@qalculate_revision@:@qalculate_age@',
    '-Wl,--no-undefined',
  ],
  dependencies : libqalc_deps)

libqalculate = declare_dependency(
  compile_args : libqalc_defines,
  include_directories : libqalc_inc,
  link_with : libqalc_lib)
