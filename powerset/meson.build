inc_dir = include_directories('.')

powerset_src = files(
  'powerset.cpp',
)

powerset_dep = declare_dependency(
  include_directories : inc_dir,
  sources : powerset_src,
  dependencies : [ truth_table_dep ],
)

test_source = powerset_src + 'test_powerset.cpp'

test_powerset_exe = executable('test_powerset',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    truth_table_dep,
    catch2_with_main_dep,
  ],
)

test('powerset_tests', test_powerset_exe)
