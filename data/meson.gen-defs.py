# Original logic found in <root>/libqalculate/Makefile.am

# echo > $@ || (rm $@;exit 1)
# for FILE in $+; do \
#   printf "const char * " >> $@ || (rm $@;exit 1); \
#   basename -- $$FILE | sed 's/[.-]/_/g' >> $@ || (rm $@;exit 1); \
#   printf " = " >> $@ || (rm $@;exit 1); \
#   sed -e 's/^[ \t]*//' -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/^/\"/' -e 's/$$/\\n\"/' $$FILE >>$@ || (rm $@;exit 1); \
#   printf ';\n\n' >>$@ || (rm $@;exit 1); \
# done

import os
import re
import argparse

argparser = argparse.ArgumentParser(prog='gen-defs.py')
argparser.add_argument('inputs', nargs='+')
argparser.add_argument('-o', '--output', required=True)

args = argparser.parse_args()

FILE_CONTENT_CLEANERS = [
  # NOTE: this rule is implemented directly in python code as trim('\t')
  # s/^[ \t]*//
  # Clean leading tabs

  # s/\\/\\\\/g
  # Escape backslashes
  # Avoiding raw string literal because there is no way to write a single backslash, r'\' does not work. `'\\', r'\\')` just looks confusing.
  ('\\', '\\\\'),
  # s/"/\\"/g
  # Escape quotes
  (r'"', r'\"'),

  # NOTE: these two rules are implemented directly in python code below
  # s/^/\"/
  # Prepend " to every line
  # s/$$/\\n\"/
  # Append " to every line
]

def process_line(line):
  line = line.strip('\t\n')
  for (needle, replacement) in FILE_CONTENT_CLEANERS:
    line = line.replace(needle, replacement)
  return f"\"{line}\\n\""

with open(args.output, 'w') as f_out:
  for input_filename in args.inputs:
    with open(input_filename, 'r') as f_inp:
      def_name = re.sub(r'[.-]', '_', os.path.basename(input_filename))
      def_content = '\n'.join([process_line(l) for l in f_inp.readlines()])
      f_out.write(f"const char *{def_name} = {def_content};\n\n")
