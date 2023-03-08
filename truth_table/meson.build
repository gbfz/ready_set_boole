inc_dir = include_directories('.')

truth_table_src = files(
  'truth_table.cpp'
)

truth_table_dep = declare_dependency(
  include_directories : inc_dir,
  sources : truth_table_src,
  dependencies : [ libft_ast_dep ],
)

test_source = truth_table_src + 'test_truth_table.cpp'

test_truth_table_exe = executable('test_truth_table',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libft_ast_dep,
    catch2_with_main_dep,
  ],
)

test('truth_table_tests', test_truth_table_exe)
