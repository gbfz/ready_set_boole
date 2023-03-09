inc_dir = include_directories('.')

eval_set_src = files(
  'eval_set.cpp',
)

eval_set_dep = declare_dependency(
  include_directories : inc_dir,
  sources : eval_set_src,
  dependencies : [ cnf_dep ],
)

test_source = eval_set_src + 'test_eval_set.cpp'

test_eval_set_exe = executable('test_eval_set',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    cnf_dep,
    catch2_with_main_dep,
  ],
)

test('eval_set_tests', test_eval_set_exe)
