verilator -cc ./rtl/*.sv --Mdir ./sim/rtl_out

mkdir -p build

(
  cd build
  cmake ../
  make
)

# link compile_commands.json for syntax highlighting
if [ ! -L "compile_commands.json" ]; then
    ln -s "build/compile_commands.json" "compile_commands.json"
fi
