project('ArcOS', 'c', 'cpp',
    default_options : [])

# Configure linker scripts from cross file

linker_script_flags = ['-g']

linker_script = meson.get_external_property('linker_script')
assert(linker_script != '', 'No linker script specified')
linker_script_flags += '-T' + meson.project_source_root() / linker_script

#add_project_link_arguments(linker_script_flags, language: ['c', 'cpp'])

cross_compile = meson.get_external_property('cross_compile', '')

assembler = find_program('@0@as'.format(cross_compile))
linker = find_program('@0@ld'.format(cross_compile))
objcopy = find_program('@0@objcopy'.format(cross_compile))

asm_gen = generator(assembler,
    output: '@BASENAME@.o',
    arguments: [
        '-o', '@OUTPUT@',
        '-c', '@INPUT@',
    ],
)

# Global variables used by all components
arc_includes = include_directories('include')
arc_objs = []

subdir('Kernel')
subdir('Drivers')
subdir('Lib')

kernel_elf = custom_target('Arc.elf',
    input: arc_objs,
    output: 'Arc.elf',
    command: [linker, '-o', '@OUTPUT@', '@INPUT@'] + linker_script_flags,
    build_by_default: true,
)

# kernel_bin = custom_target('Arc.bin',
#     input: kernel_elf,
#     output: 'Arc.bin',
#     command: [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
#     build_by_default: true,
# )
