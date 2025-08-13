project(
    'anteworld',
    'c',
    'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++20', 'default_library=static'],
)
add_project_arguments('-DGLM_ENABLE_EXPERIMENTAL', language: ['c', 'cpp'])

anteworld_inc = include_directories('include')

cpp = meson.get_compiler('cpp')
c5e_dep = cpp.find_library('c5e_lib.dll', dirs: [meson.project_source_root() / 'lib'])


subdir('include/v8')
subdir('include/glm')
subdir('include/comm')

intergen_generate = generator(intergen_exe,
    arguments: ['@INPUT@', mtg_path, '@OUTPUT0@'],
    output: ['@BASENAME@.intergen.cpp', '@BASENAME@.intergen.js.cpp']
)


subdir('include/ot')
subdir('example/vehicle_plugin')
subdir('example/igc_plugin')
subdir('example/example_gameob')