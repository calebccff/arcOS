srcs = files(
    'Init.cc',
    'Alloc.cc',
    'Printk.cc',
)

# Build the kernel as a shared module, then extract the objects from it
# to link them with our startup code.
kernel = build_target('Kernel',
    srcs,
    target_type : 'shared_module',
    include_directories : arc_includes,
).extract_objects(srcs)

arc_objs += [
    kernel,
    asm_gen.process('Startup.S'),
    #    asm_gen.process('Exception.S'),
]
