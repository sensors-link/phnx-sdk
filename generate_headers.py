Import('env')
from os.path import join

curDir = Dir('.').srcnode().abspath

src_filter = []
cpp_path = []
sub_dir = ''

if env['BOARD'] == 'fdv32s301':
    sub_dir = "FDV32S301"

elif env['BOARD'] == 'fdv32s302':
    sub_dir = "FDV32S302"

elif env['BOARD'] == 'fdv32f003':
    sub_dir = "FDV32F003"

ldscript = join(curDir, sub_dir, "env", "flash.lds")
upload_script = join(curDir, sub_dir, "env", "phoenix.cfg")

src_filter.append("+<" + join(curDir, sub_dir, "drivers", "*.c") + ">")
src_filter.append("+<" + join(curDir, sub_dir, "stubs", "*.c") + ">")
src_filter.append("+<" + join(curDir, sub_dir, "env", "*.c") + ">")
src_filter.append("+<" + join(curDir, sub_dir, "env", "*.S") + ">")

cpp_path.append(join(curDir, sub_dir, "drivers"))
cpp_path.append(join(curDir, sub_dir, "env"))
cpp_path.append(join(curDir, sub_dir, "include"))
cpp_path.append(join(curDir, sub_dir, "stubs"))

openocd_args = [
    "-f", '"' + upload_script + '"',
    "-c", "init; halt;", "-c", "program {$SOURCE}; ","-c softreset;exit 0;"
]

env.Append(
    SRC_FILTER=src_filter,
    CPPPATH=cpp_path
)

env.Replace(
    LDSCRIPT_PATH=ldscript,
    UPLOADERFLAGS=openocd_args
)
