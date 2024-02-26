if get_option('use_nls')
  add_project_arguments('-DGETTEXT_PACKAGE="libqalculate"', language: ['c', 'cpp'])
  i18n.gettext(meson.project_name(),
    args: ['--from-code=UTF-8', '--keyword=_', '--keyword=N_', '--keyword="_n:1,2"', '--keyword="_c:1c,2"'])
endif
