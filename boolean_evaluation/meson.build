inc_dir = include_directories('.')

eval_formula_src = files(
  'eval_formula.cpp'
)

eval_formula_dep = declare_dependency(
  include_directories : inc_dir,
  sources : eval_formula_src,
  dependencies : [ libft_ast_dep ],
)

test_source = eval_formula_src + 'test_eval_formula.cpp'

test_eval_formula_exe = executable('test_eval_formula',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libft_ast_dep,
    catch2_with_main_dep,
  ],
)

test('eval_formula_tests', test_eval_formula_exe)
