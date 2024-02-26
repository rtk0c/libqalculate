# Sync version with the QALCULATE_VERSION_* macros in libqalculate/includes.h
project('libqalculate', 'cpp', version : '4.9.0')
ver = meson.project_version()
ver_arr = ver.split('.')
qalculate_major = ver_arr[0]
qalculate_revision = ver_arr[1]
qalculate_age = ver_arr[2]

fs = import('fs')
i18n = import('i18n')

# Used for source generation
# Rationale of not using a shell script: since we are using meson anyways, Python is going to be available on the system
# might as well use that to get better compatibility on Windows without forcing the user to install msys2 or cygwin
pymod = import('python')
python = pymod.find_installation(required : get_option('compiled_definitions'))

thread_dep = dependency('threads')
libxml = dependency('libxml2')
gmp = dependency('gmp')
mpfr = dependency('mpfr')
libcurl = dependency('libcurl', required : get_option('with_libcurl'))
icu_uc = dependency('icu-uc', required : get_option('with_icu'))
iconv = dependency('iconv', required : false)
gettext = dependency('intl', required : false)
readline = dependency('readline', required : get_option('with_readline'))

datadir = get_option('datadir')
localedir = get_option('localedir')

incdir = include_directories('.')

subdir('po')
subdir('data')
subdir('libqalculate')
subdir('src')

install_man('man/qalc.1')
