# --testing.
set(
    directories
    num 
)

foreach(directory ${directories})
    
    # --mirroring.
    
    add_subdirectory(${directory})
endforeach()
