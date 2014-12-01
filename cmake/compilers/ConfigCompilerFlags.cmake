include(SaveCompilerFlags)
if(ENABLE_CXX11_SUPPORT)
   include(CheckCXX11Features)
endif()   
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(CheckFortranCompilerFlag)
include(TestRestrict)

if(ENABLE_VECTORIZATION)
   include(FindBrokenIntrinsics)
   include(OptimizeForArchitecture)
   set(DEFINITIONS)
   set(CXX_ARCHITECTURE_FLAGS)
   set(C_ARCHITECTURE_FLAGS)
   set(Fortran_ARCHITECTURE_FLAGS)
   set(tmp ${CMAKE_REQUIRED_QUIET})
   set(CMAKE_REQUIRED_QUIET TRUE)
   find_broken_intrinsics()
   OptimizeForArchitecture()
   message(STATUS "Vectorization flags set:")
   message(STATUS "  CXX    : ${CXX_ARCHITECTURE_FLAGS}")
   message(STATUS "  C      : ${C_ARCHITECTURE_FLAGS}")
   message(STATUS "  Fortran: ${Fortran_ARCHITECTURE_FLAGS}")
   set(CMAKE_REQUIRED_QUIET ${tmp})
endif()	

# This is to pass the right option to the linker using -Xlinker
# might need to be modified for Windows
set(_exportdynamic "")
if(APPLE)
   set(_exportdynamic "-dynamic")
else()
   set(_exportdynamic "-export-dynamic")
endif()

test_restrict(restrict)
set(RESTRICT ${restrict})

if(CMAKE_C_COMPILER_WORKS)
    include(CFlags)
endif()

if(CMAKE_CXX_COMPILER_WORKS)
    include(CXXFlags)
endif()

if(CMAKE_Fortran_COMPILER_WORKS)
    include(FortranFlags)
endif()
