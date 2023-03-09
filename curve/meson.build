inc_dir = include_directories('.')

map_src = files(
  'map.cpp',
)

map_dep = declare_dependency(
  include_directories : inc_dir,
  sources : map_src,
  dependencies : [ libmorton_dep ],
)

test_source = map_src + 'test_map.cpp'

test_map_exe = executable('test_map',
  test_source,
  include_directories : inc_dir,
  dependencies : [
    libmorton_dep,
    catch2_with_main_dep,
  ],
)

test('map_tests', test_map_exe)
