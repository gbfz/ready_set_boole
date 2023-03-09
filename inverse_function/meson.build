inc_dir = include_directories('.')

reverse_map_src = files(
  'reverse_map.cpp',
)

reverse_map_dep = declare_dependency(
  include_directories : inc_dir,
  sources : reverse_map_src,
  dependencies : [ libmorton_dep ],
)

test_source = reverse_map_src + 'test_reverse_map.cpp'

test_reverse_map_exe = executable('test_reverse_map',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libmorton_dep,
    catch2_with_main_dep,
  ],
)

test('reverse_map_tests', test_reverse_map_exe)
