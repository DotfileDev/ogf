project(
    'ogf',
    ['cpp', 'c'],
    default_options: [
        'cpp_std=c++1z',
        'warning_level=3'
    ]
)

sdl2_dep = dependency('sdl2')
subdir('libraries')

sources = []
subdir('source')

libogf = library(
    'ogf',
    sources,
    include_directories: include_directories('include', 'source'),
    dependencies: [
        glad_dep,
        sdl2_dep,
        stb_dep,
        tinyobjloader_dep
    ]
)

ogf_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: libogf
)

if get_option('build_tests')
    subdir('tests')
endif

if get_option('build_examples')
    subdir('examples')
endif
