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
        sdl2_dep,
        glad_dep
    ]
)

ogf_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: libogf
)
