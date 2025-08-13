igc_plugin_inc = include_directories('.')


interface_dep = declare_dependency(sources: intergen_generate.process('plugin.hpp'))

igc_plugin_lib = shared_library(
    'igc_plugin',
    sources: ['plugin.cpp', 'plugin.hpp', 'igc_plugin.cpp', 'ifc/plugin_interface.h', 'ifc/js/plugin_interface.h'],
    include_directories: [anteworld_inc, igc_plugin_inc],
    link_with: [ot_lib, comm_lib],
    dependencies: [interface_dep, c5e_dep]
)

