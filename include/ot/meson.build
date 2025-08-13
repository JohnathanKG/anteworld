ot_inc = include_directories('.')
ot_lib = library(
    'ot',
    sources: ['action_cfg.h', 'aircraft.h', 'aircraft_physics.h', 'animation.h', 'animation_stack.h', 'blend_tree.h', 'canvas.h', 'coal.h', 'cubeface.cpp', 'cubeface.h', 'dynamic_object.h', 'env.h', 'environment.h', 'explosions.h', 'explosion_params.h', 'fb.h', 'gameob.h', 'geomob.h', 'geom_types.h', 'igc.h', 'igc_data.h', 'jsb.h', 'light_cfg.h', 'location_cfg.h', 'object.h', 'object_cfg.h', 'pkgview.h', 'sdm_types.h', 'sndgrp.h', 'sound_cfg.h', 'static_object.h', 'tracker.h', 'tracker_arm.h', 'vehicle.h', 'vehicle_cfg.h', 'vehicle_physics.h', 'video_recorder.h', 'weapon_cfg.h', 'glm/coal.h', 'glm/glm_bt.h', 'glm/glm_ext.h', 'glm/glm_meta.h', 'glm/glm_meta_v8.h', 'glm/glm_types.h'],
    include_directories: [anteworld_inc, ot_inc],
    link_with: [glm_lib, comm_lib]
)