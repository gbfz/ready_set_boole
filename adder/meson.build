inc_dir = include_directories('.')

adder_source = files(
  'adder.cpp',
)

adder_dep = declare_dependency(
  include_directories : inc_dir,
  sources : adder_source,
)

test_source = adder_source + 'test_adder.cpp'

test_adder_exe = executable('test_adder',
  test_source,
  include_directories : inc_dir,
  dependencies : [ catch2_with_main_dep ]
)

test('adder_tests', test_adder_exe)
