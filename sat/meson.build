inc_dir = include_directories('.')

sat_src = files(
  'sat.cpp',
)

sat_dep = declare_dependency(
  include_directories : inc_dir,
  sources : sat_src,
  dependencies : [ truth_table_dep ],
)

test_source = sat_src + 'test_sat.cpp'

test_sat_exe = executable('test_sat',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    truth_table_dep,
    catch2_with_main_dep,
  ],
)

test('sat_tests', test_sat_exe)
