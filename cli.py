import os
from argparse import ArgumentParser
import pathlib
import subprocess
from sys import platform

SHADER_DIR: str = "./shaders/"
SHADER_BUILD_DIR: str = "./shaders/build/"
VULKAN_GLSLC: str = pathlib.Path("C:/VulkanSDK/1.3.236.0/Bin/glslc.exe") if platform == 'win32' else pathlib.Path("/Users/georgiesantiago/VulkanSDK/1.3.243.0/macOS/bin/glslc")

def main(args):
    if args.command == 'build':
        compile_shaders()
        run("bazel build //:all --sandbox_debug --test_env=VULKAN_SDK=/Users/georgiesantiago/VulkanSDK/1.3.243.0")
    if args.command == 'build:shaders':
        compile_shaders()
    if args.command == 'build:dependency_graph':
        run('bazel query "deps(//:all)" --noimplicit_deps --output graph >> graph.in && dot -Tpng < graph.in > graph.png')
    if args.command == 'test':
        run('bazel test --test_output=all //:all')
    if args.command == 'run:console':
        run(pathlib.Path('bazel-bin/nyx_console.exe'))

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
            run(cmd)

def run(cmd: str):
    subprocess.run(cmd, shell=True if platform != 'win32' else False)

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
        ])

    main(args.parse_args())