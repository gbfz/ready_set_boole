inc_dir = include_directories('.')

gray_code_source = files(
  'gray_code.cpp',
)

gray_code_dep = declare_dependency(
  include_directories : inc_dir,
  sources : gray_code_source,
)

test_source = gray_code_source + 'test_gray_code.cpp'

test_gray_code_exe = executable('test_gray_code',
  test_source,
  include_directories : inc_dir,
  dependencies : [ catch2_with_main_dep ],
)

test('gray_code_tests', test_gray_code_exe)
