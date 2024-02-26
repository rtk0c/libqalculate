# TODO this whole thing is broken:
#      I have no idea how upstream updates the .po and .pot files here, my best guess is that they are running the same autotools target from <root>/po/ and pointing the workdir to here
#      In any case, most likely this meson buildsystem will just use the .po files provided by upstreams as-is, so having proper gettext update targets isn't that necessary anyways

# i18n.gettext('libqalculate-data',
#   # TODO how to make meson not build into .mo files either? we don't need them, since they are only being used to localize /data/*.xml.in
#   install: false,
#   # TODO hardcoding this path is broken, how not to?
#   args: ['--from-code=UTF-8', '--its=/usr/share/gettext/its/appdata.its'])

# executable('remove-untranslated', 'remove-untranslated.cc')
