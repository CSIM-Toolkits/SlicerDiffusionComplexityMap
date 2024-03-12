cmake_minimum_required(VERSION 3.16.3...3.27 FATAL_ERROR)

project(DiffusionComplexityMap)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "https://www.slicer.org/wiki/Documentation/Nightly/Extensions/DiffusionComplexityMap")
set(EXTENSION_CATEGORY "Diffusion")
set(EXTENSION_CONTRIBUTORS "Antonio Carlos Senra Filho (University of Campinas, Brazil), Andre M. Paschoal (University of Campinas, Brazil), Luiz Otavio Murta Junior (University of Sao Paulo, Brazil)")
set(EXTENSION_DESCRIPTION "This extension provides the Diffusion Complexity map based for diffusion imaging sequences (assuming DTI imaging protocol). This algorithm results in an diffusion scalar mapping based on the LMC complexity metric, infering micro-structural tissue complexity measurement.")
set(EXTENSION_ICONURL "https://www.example.com/Slicer/Extensions/DiffusionComplexityMap.png")
set(EXTENSION_SCREENSHOTURLS "https://www.example.com/Slicer/Extensions/DiffusionComplexityMap/Screenshots/1.png")
set(EXTENSION_DEPENDS "NA") # Specified as a list or "NA" if no dependencies

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(DiffusionComplexityMap)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_GENERATE_CONFIG})
include(${Slicer_EXTENSION_CPACK})
