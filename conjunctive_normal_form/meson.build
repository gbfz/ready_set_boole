inc_dir = include_directories('.')

cnf_src = files(
  'CNFPattern.cpp',
  'CNForm.cpp',
)

cnf_dep = declare_dependency(
  include_directories : inc_dir,
  sources : cnf_src,
  dependencies : [
    libft_ast_dep,
    nnf_dep,
  ],
)

test_source = cnf_src + 'test_cnf.cpp'

test_cnf_exe = executable('test_cnf',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libft_ast_dep,
    nnf_dep,
    catch2_with_main_dep,
  ],
)

test('conjunctive_normal_form_tests', test_cnf_exe)
