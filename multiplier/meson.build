inc_dir = include_directories('.')

multiplier_source = files(
  'multiplier.cpp',
)

multiplier_dep = declare_dependency(
  include_directories : inc_dir,
  sources : multiplier_source,
  dependencies : [ adder_dep ],
)

test_source = multiplier_source + 'test_multiplier.cpp'

test_multiplier_exe = executable('test_multiplier',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    adder_dep,
    catch2_with_main_dep,
  ],
)

test('multiplier_tests', test_multiplier_exe)
