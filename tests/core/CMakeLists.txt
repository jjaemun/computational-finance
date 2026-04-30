# --testing.
set(
    directories
    approx
    num 
    #ptr
)

foreach(directory ${directories})
    
    # --mirroring.
    
    add_subdirectory(${directory})
endforeach()
