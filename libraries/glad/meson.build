if target_machine.system() == 'windows'
    libglad = library(
        'glad',
        ['source/glad.c'],
        include_directories: include_directories('include')
    )
else
    dl_dep = meson.get_compiler('c').find_library('dl')
    libglad = library(
        'glad',
        ['source/glad.c'],
        include_directories: include_directories('include'),
        dependencies: dl_dep
    )
endif
glad_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: libglad
)
