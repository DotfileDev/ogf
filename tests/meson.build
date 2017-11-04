test_sources = [
    'main.cxx',
    'utils/io_utils.cxx'
]

gtest_dep = dependency('gtest', main: true)

ogf_tests = executable(
    'ogf_tests',
    test_sources,
    dependencies: [gtest_dep, ogf_dep],
    include_directories: include_directories('../source'))

test('all in ogf', ogf_tests)
