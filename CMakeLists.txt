cmake_minimum_required(VERSION 3.16.3...3.27 FATAL_ERROR)

project(DiffusionComplexityMap)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "https://slicerdiffusioncomplexitymap.readthedocs.io/en/latest/")
set(EXTENSION_CATEGORY "Diffusion")
set(EXTENSION_CONTRIBUTORS "Antonio Carlos Senra Filho (University of Campinas, Brazil), Andre M. Paschoal (University of Campinas, Brazil), Luiz Otavio Murta Junior (University of Sao Paulo, Brazil)")
set(EXTENSION_DESCRIPTION "This extension provides the Diffusion Complexity map based for diffusion imaging sequences (assuming DTI imaging protocol). This algorithm results in an diffusion scalar mapping based on the LMC complexity metric, infering micro-structural tissue complexity measurement.")
set(EXTENSION_ICONURL "https://raw.githubusercontent.com/CSIM-Toolkits/SlicerDiffusionComplexityMap/main/DiffusionComplexityMap.png")
set(EXTENSION_SCREENSHOTURLS
  "https://raw.githubusercontent.com/CSIM-Toolkits/SlicerDiffusionComplexityMap/refs/heads/main/docs/assets/FA_diff_example.png"
  "https://raw.githubusercontent.com/CSIM-Toolkits/SlicerDiffusionComplexityMap/refs/heads/main/docs/assets/ADC_diff_example.png"
  "https://raw.githubusercontent.com/CSIM-Toolkits/SlicerDiffusionComplexityMap/refs/heads/main/docs/assets/DC_diff_example.png"
)
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
