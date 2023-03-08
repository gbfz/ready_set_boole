inc_dir = include_directories('.')

ast_sources = [
  'Node.cpp',
  'Parser.cpp',
]

libft_ast = static_library('libft_ast',
  ast_sources,
  include_directories : inc_dir,
)

libft_ast_dep = declare_dependency(
  include_directories : inc_dir,
  link_with : libft_ast,
)
