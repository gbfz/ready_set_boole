project('ready-set-boole',
        'cpp',
        default_options : [
          'cpp_std=c++20', 'warning_level=3'
        ],
)

catch2_with_main_dep = subproject('catch2').get_variable('catch2_with_main_dep')

subdir('ast/')
subdir('adder/')
subdir('multiplier/')
subdir('gray_code/')
subdir('boolean_evaluation/')
subdir('truth_table/')
subdir('negation_normal_form/')
subdir('conjunctive_normal_form/')
subdir('sat/')
subdir('powerset/')
