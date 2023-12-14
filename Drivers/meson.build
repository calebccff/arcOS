srcs = files(
    'Core.cc',
    'UART-PL011.cc',
)

# Build the kernel as a shared module, then extract the objects from it
# to link them with our startup code.
drivers = build_target('Drivers',
    srcs,
    target_type : 'shared_module',
    include_directories : arc_includes,
).extract_objects(srcs)

arc_objs += [
    drivers,
]
