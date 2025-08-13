plugin_inc = include_directories('.')
plugin_dll = shared_library(
    'vehicle_plugin',
    sources: ['simplugin.cpp', 'simplugin.hpp', 'vehicle_plugin.cpp'],
    include_directories: [anteworld_inc, plugin_inc],
    link_with: [ot_lib, comm_lib]
)