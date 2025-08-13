v8_inc = include_directories('.')

v8_lib = static_library(
    'v8',
    [
        'libplatform.h',
        'v8-inspector-protocol.h',
        'v8-inspector.h',
        'v8-platform.h',
        'v8-profiler.h',
        'v8-testing.h',
        'v8-util.h',
        'v8-value-serializer-version.h',
        'v8-version-string.h',
        'v8-version.h',
        'v8.h',
        'v8config.h',
        'libplatform/libplatform-export.h',
        'libplatform/v8-tracing.h',
    ],
    include_directories: [anteworld_inc, v8_inc],
)