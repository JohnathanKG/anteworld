gameob_inc = include_directories('.')

example_gameob = shared_library(
    'wind_turbine_plugin',
    sources: ['wind_turbine.cpp'],
    include_directories: [anteworld_inc, gameob_inc],
    link_with: [ot_lib, comm_lib]
)
