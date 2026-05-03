# --testing.
set(
    directories
    approx
    num 
    ptr
    specfun
)

foreach(directory ${directories})
    
    # --mirroring.
    
    add_subdirectory(${directory})
endforeach()
