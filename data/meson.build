intltool_merge = find_program('intltool-merge')

data_files = files([
  'eurofxref-daily.xml',
  'rates.json',
])
foreach f : ['currencies.xml.in', 'datasets.xml.in', 'elements.xml.in',
             'functions.xml.in', 'planets.xml.in', 'prefixes.xml.in',
             'units.xml.in', 'variables.xml.in']
  f_out = f.replace('.in', '')
  data_files += custom_target(
    f_out,
    input : f,
    output : f_out,
    command : [intltool_merge, '-x', '-u', '-c', '.intltool-merge-cache', 'fixed', '@INPUT@', '@OUTPUT@'])
endforeach

if get_option('compiled_definitions')
  add_languages('c')

  data_definitions_c = custom_target(
    'definitions.c',
    input : [data_files],
    output : 'definitions.c',
    command : [python, files('meson.gen-defs.py'), '--output=@OUTPUT@', '@INPUT@'])
endif
