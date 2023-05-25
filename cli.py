import os
import pathlib
import subprocess
from argparse import ArgumentParser

SHADER_DIR: str = "shaders/"
SHADER_BUILD_DIR: str = "shaders/build/"
VULKAN_GLSLC: str = pathlib.Path("C:/VulkanSDK/1.3.236.0/Bin/glslc.exe")

def main(args):
    if (args.clean and args.command != 'clean'):
        subprocess.call('bazel clean --expunge')
    if args.command == 'build':
        compiler = '--compiler=' + args.compiler if args.compiler else ''
        debug = '--sandbox_debug' if args.debug else '' 
        compile_shaders()
        if args.debug:
            print("Running: " + "bazel build //:all --color=yes {0} {1}".format(
            compiler,
            debug
        ))
        subprocess.call("bazel build //:all --color=yes {0} {1}".format(
            compiler,
            debug
        ))
    if args.command == 'build:shaders':
        compile_shaders()
    if args.command == 'build:dependency_graph':
        subprocess.call('bazel query "deps(//:all)" --noimplicit_deps --output graph >> graph.in && dot -Tpng < graph.in > graph.png')
    if args.command == 'test':
        subprocess.call('bazel test --test_output=all //:all')
    if args.command == 'clean':
        subprocess.call('bazel clean --expunge')
    if args.command == 'run:console':
        subprocess.call(pathlib.Path('bazel-bin/nyx_console.exe'))
    if args.command == 'query:toolchain':
        subprocess.call('bazel query @local_config_cc//:toolchain --output=build')
'''
@description walks the shader directory and auto compiles shaders
'''
def compile_shaders():
    for file in os.listdir(SHADER_DIR):
        if ".vert" in file or ".frag" in file:
            shader_path = pathlib.Path("{0}{1}".format(SHADER_DIR, file))
            shader_out_path = pathlib.Path("{0}{1}{2}".format(SHADER_BUILD_DIR, file, '.spv'))
            cmd: str = '{0} "{1}" -o "{2}"'.format(
                VULKAN_GLSLC,
                shader_path,
                shader_out_path
            )
            subprocess.call(cmd)

if __name__ == '__main__':
    args = ArgumentParser(
        prog='Nyx Engine Script Utilities',
        description='',
        epilog='Text at the bottom of help'    
    )

    args.add_argument("command", choices=[
            'run:console',
            'build',
            'build:shaders',
            'build:dependency_graph',
            'test',
            'clean',
            'query:toolchain'
        ])
    args.add_argument('--compiler', type=str)
    args.add_argument('--debug', type=bool, default=False)
    args.add_argument('--clean', type=bool, default=False)
    main(args.parse_args())