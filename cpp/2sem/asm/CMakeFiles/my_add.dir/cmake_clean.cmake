FILE(REMOVE_RECURSE
  "CMakeFiles/my_add.dir/my_add.asm.o"
  "my_add.pdb"
  "my_add"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang ASM)
  INCLUDE(CMakeFiles/my_add.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
