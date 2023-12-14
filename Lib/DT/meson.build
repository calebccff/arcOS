srcs = files(
    'Core.cc'
)

# Build the kernel as a shared module, then extract the objects from it
# to link them with our startup code.
lib_dt = build_target('LibDT',
    srcs,
    target_type : 'shared_module',
    include_directories : arc_includes,

# FIXME: should do the extract_objects step in the main meson.build
).extract_objects(srcs)

arc_objs += [
    lib_dt,
]
