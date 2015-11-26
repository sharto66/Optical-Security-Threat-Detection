#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/InputImage.o \
	${OBJECTDIR}/ProcessingMethods.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/opencv/debug/lib -L/C/opencv/release/lib -lopencv_calib3d300d.dll -lopencv_calib3d_pch_dephelpd -lopencv_core300d.dll -lopencv_core_pch_dephelpd -lopencv_features2d300d.dll -lopencv_features2d_pch_dephelpd -lopencv_flann300d.dll -lopencv_flann_pch_dephelpd -lopencv_hal300d -lopencv_hal_pch_dephelpd -lopencv_highgui_pch_dephelpd -lopencv_imgcodecs300d.dll -lopencv_imgcodecs_pch_dephelpd -lopencv_imgproc300d.dll -lopencv_imgproc_pch_dephelpd -lopencv_ml300d.dll -lopencv_ml_pch_dephelpd -lopencv_objdetect300d.dll -lopencv_objdetect_pch_dephelpd -lopencv_photo300d.dll -lopencv_photo_pch_dephelpd -lopencv_shape300d.dll -lopencv_shape_pch_dephelpd -lopencv_stitching300d.dll -lopencv_stitching_pch_dephelpd -lopencv_superres300d.dll -lopencv_superres_pch_dephelpd -lopencv_ts_pch_dephelpd -lopencv_video300d.dll -lopencv_video_pch_dephelpd -lopencv_videoio_pch_dephelpd -lopencv_videostab300d.dll -lopencv_videostab_pch_dephelpd -lopencv_videoio300.dll -lopencv_videoio_pch_dephelp -lopencv_calib3d300d.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/InputImage.o: InputImage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InputImage.o InputImage.cpp

${OBJECTDIR}/ProcessingMethods.o: ProcessingMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProcessingMethods.o ProcessingMethods.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
