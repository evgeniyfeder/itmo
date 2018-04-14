FILE(REMOVE_RECURSE
  "CMakeFiles/sub.dir/sub.asm.o"
  "sub.pdb"
  "sub"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang ASM)
  INCLUDE(CMakeFiles/sub.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
