project(
    'anteworld',
    'c',
    'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++20', 'default_library=static'],
)
add_project_arguments('-DGLM_ENABLE_EXPERIMENTAL', language: ['c', 'cpp'])


anteworld_inc = include_directories('include')
subdir('include/glm')
subdir('include/comm')
subdir('include/ot')
subdir('example/vehicle_plugin')