## Memchecker :
valgrind-3.25.1

---

## Compiler:
gcc (GCC) 15.2.1 20250813

---

## Text Editor: 
NVIM v0.11.5 <br>
LuaJIT 2.1.1763148144

---

## Project Structure
<pre>
  .
  ├── makefile                  -- Bash script 
  ├── objects.c
  ├── objects.h
  ├── README.md
  ├── stack.c
  ├── stack.h
  ├── test_cycles.c             -- File testing cycle handling.
  ├── test_mark_trace.c         -- File testing the GC handle mark root and indirectly referenced objects.
  ├── test_multiple_refs.c      -- File that tests if GC is able to handle objects in different frames.
  ├── test_usual.c              -- File that tests if the GC can handle objects in a single frame.
  ├── vm.c
  └── vm.h
</pre>
1 directory, 12 files

