FIND_PATH(PYTHIA8_INCLUDE_DIR Pythia.h /usr/include/ /usr/include/pythia /usr/local/include/ $ENV{PYTHIADIR}/include)

FIND_LIBRARY(PYTHIA8_LIBRARY NAMES pythia8 PATHS /usr/lib /usr/lib/pythia /usr/local/lib $ENV{PYTHIADIR}/lib/archive/)

IF (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIBRARY)
   SET(PYTHIA8_FOUND TRUE)
ENDIF (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIBRARY)


IF (PYTHIA8_FOUND)
   IF (NOT Pythia8_FIND_QUIETLY)
      MESSAGE(STATUS "Found Pythia8: ${PYTHIA8_LIBRARY}")
      MESSAGE(STATUS "Found Pythia8 include: ${PYTHIA8_INCLUDE_DIR}")
   ENDIF (NOT Pythia8_FIND_QUIETLY)
ELSE (PYTHIA8_FOUND)
   IF (Pythia8_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Pythia8. We search first in the normal library paths, then in $PYTHIADIR")
   ELSE(Pythia8_FIND_REQUIRED)
      IF(NOT Pythia8_FIND_QUIETLY)
	 MESSAGE(STATUS "Could not find Pythia8.  We search first in the normal library paths, then in $PYTHIADIR")
      ENDIF(NOT Pythia8_FIND_QUIETLY)
   ENDIF (Pythia8_FIND_REQUIRED)
   
ENDIF (PYTHIA8_FOUND)

