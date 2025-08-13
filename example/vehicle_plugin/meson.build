vehicle_plugin_inc = include_directories('.')

interface_dep = declare_dependency(sources: intergen_generate.process('simplugin.hpp'))

vehicle_plugin = shared_library(
    'vehicle_plugin',
    sources: ['simplugin.cpp', 'simplugin.hpp', 'vehicle_plugin.cpp', 'ifc/engine.h', 'ifc/js/engine.h'],
    include_directories: [anteworld_inc, vehicle_plugin_inc],
    link_with: [ot_lib, comm_lib],
    dependencies: [interface_dep, c5e_dep]
)