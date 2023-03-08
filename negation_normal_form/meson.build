inc_dir = include_directories('.')

nnf_src = files(
  'NNFPattern.cpp',
  'NNForm.cpp',
)

nnf_dep = declare_dependency(
  include_directories : inc_dir,
  sources : nnf_src,
  dependencies : [ libft_ast_dep ],
)

test_source = nnf_src + 'test_nnf.cpp'

test_nnf_exe = executable('test_nnf',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libft_ast_dep,
    catch2_with_main_dep,
  ],
)

test('negation_normal_form_tests', test_nnf_exe)
