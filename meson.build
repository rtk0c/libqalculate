project('qalculate', 'cpp', version : '4.9.0')
ver = meson.project_version()
ver_arr = ver.split('.')
qalculate_major = ver_arr[0]
qalculate_revision = ver_arr[1]
qalculate_age = ver_arr[2]

thread_dep = dependency('threads')
libxml = dependency('libxml2')
gmp = dependency('gmp')
mpfr = dependency('mpfr')

libcurl = dependency('libcurl', required : get_option('with-libcurl'))
icu_uc = dependency('icu-uc', required : get_option('with-icu'))
iconv = dependency('iconv', required : false)
gettext = dependency('intl', required : false)
readline = dependency('readline', required : get_option('with-readline'))

datadir = get_option('datadir')
localedir = get_option('localedir')

incdir = include_directories('.')

subdir('libqalculate')
subdir('src')
